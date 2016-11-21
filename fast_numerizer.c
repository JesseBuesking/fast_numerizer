#include "fast_numerizer.h"
#include "scanner.def.h"
#include "num-fmt.h"

#define TOKEN_SEPARATOR 10000

void yystypeToString(sds *s, YYSTYPE A, int precision) {
    doubleToString(s, A.double_value, precision);

    switch (A.suffix) {
        case NO_SUFFIX:
            break;
        case ST:
            *s = sdscat(*s, "st");
            break;
        case STS:
            *s = sdscat(*s, "sts");
            break;
        case ND:
            *s = sdscat(*s, "nd");
            break;
        case NDS:
            *s = sdscat(*s, "nds");
            break;
        case RD:
            *s = sdscat(*s, "rd");
            break;
        case RDS:
            *s = sdscat(*s, "rds");
            break;
        case TH:
            *s = sdscat(*s, "th");
            break;
        case THS:
            *s = sdscat(*s, "ths");
            break;
    }
}

void *pParser;
sds numberHolder;

void initFastNumerizer(void) {
    numberHolder = sdsempty();
    pParser = ParseAlloc(malloc);
}

void freeFastNumerizer(void) {
    if (pParser!=NULL) {
        ParseFree(pParser, free);
    }
    sdsfree(numberHolder);
}

void numerize(const char *data, size_t data_len, ParserState *state) {
    YYSTYPE yylval;
    scanstate ss;
    scanstate_init(&ss, NULL, 0);
    readmem_attach(&ss, data, data_len);

    int tok;
    unsigned int start_pos = 0;
    unsigned int token_length = 0;

	// Initialize the scanner to read from this string constant.
    readmem_init_str(&ss, data);
    ss.line = 1;

#if debug
    ParseTrace(stderr, (char*)"[Parser] >> ");
#endif
    int last_tok = -1;

    do
    {
        tok = numerizer_start(&ss);
#if debug
        printf("line %2d, token %d\n", ss.line, tok);
#endif

        if (tok == 0) {
            break;
        }

        if (tok < 0) {
            printf("Scanner returned an error: %d\n", tok);
            break;
        }

        token_length = scan_token_length(&ss);

        if (tok == TOKEN_NUMBER) {
            sds value = sdsnewlen(ss.token, token_length);
            sscanf(value, "%lf", &yylval.double_value);
            sdsfree(value);
        }

        yylval.spos = start_pos;
        yylval.epos = yylval.spos + token_length;
        start_pos += token_length;

#if debug
        sds value = sdsnewlen(ss.token, token_length);
        printf("token is %s at %d - %d\n", value, yylval.spos, yylval.epos);
        sdsfree(value);
#endif
        if (tok == TOKEN_SECOND && (state->options & PARSE_SECOND) == 0) {
            continue;
        }

        if (tok != TOKEN_SEPARATOR && (last_tok == -1 || last_tok != TOKEN_CHARACTERS)) {
            Parse(pParser, tok, yylval, state);
        }

        last_tok = tok;
    } while (tok);

    Parse(pParser, 0, yylval, state);
    ParseReset(pParser);

    YYSTYPEList l = state->yystypeList;
#if debug
    printf("numbers: %zu\n", l.used);
#endif

    sortYYSTYPElist(&l);

    if (l.used == 0) {
        state->result = sdsnew(data);
    } else {
        state->result = sdsempty();
        sds original = sdsnew(data);

        unsigned int lastpos = 0;
        unsigned int i = 0;

        for (i = 0; i < l.used; ++i) {
            YYSTYPE y = l.values[i];
#if debug
            printf("spos: %d, epos: %d, value: %lf, suffix: %d\n", y.spos, y.epos, y.double_value, y.suffix);
#endif

            if (lastpos < y.spos) {
                sds tmp = sdsdup(original);
                sdsrange(tmp, lastpos, y.spos - 1);
                state->result = sdscatsds(state->result, tmp);
                sdsfree(tmp);
            }
            lastpos = y.epos;

            yystypeToString(&numberHolder, y, 3);
            state->result = sdscatsds(state->result, numberHolder);

            sdsclear(numberHolder);
            // in case the last string was exceptionally large, free up memory
            if (sdslen(numberHolder) > 512) {
                sdsRemoveFreeSpace(numberHolder);
            }
        }

        sds tmp = sdsdup(original);
        sdsrange(tmp, l.values[l.used-1].epos, -1);
        state->result = sdscatsds(state->result, tmp);
        sdsfree(tmp);
        sdsfree(original);
    }
}
