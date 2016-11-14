#include "fast_numerizer.h"
#include "scanner.def.h"
#include "num-fmt.h"

#define TOKEN_SEPARATOR 10000

void yystypeToString(sds *s, YYSTYPE A, int precision) {
    doubleToString(s, A.double_value, precision);

    switch (A.suffix) {
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

    *s = sdsRemoveFreeSpace(*s);
}

void numerize(const char *data, ParserState *state) {
    YYSTYPE yylval;
    scanstate ss;
    scanstate_init(&ss, NULL, 0);
    readmem_attach(&ss, data, strlen(data));

    initYYSTYPEList(&state->yystypeList, 4);

    int tok;
    unsigned int start_pos = 0;
    unsigned int token_length = 0;
    void *pParser = ParseAlloc(malloc);

	// Initialize the scanner to read from this string constant.
    readmem_init_str(&ss, data);
    ss.line = 1;

#if debug
    ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

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

        // set the underlying value
        sds value = sdsnewlen(ss.token, token_length);

#if debug
        printf("token is \"%s\"\n", value);
#endif

        if (tok == TOKEN_NUMBER) {
            sscanf(value, "%lf", &yylval.double_value);
        }

        yylval.spos = start_pos;
        yylval.epos = yylval.spos + token_length;
        start_pos += token_length;

        /*printf("token is %s at %d - %d\n", value, yylval.spos, yylval.epos);*/

        if (tok != TOKEN_SEPARATOR) {
            Parse(pParser, tok, yylval, state);
        }

        sdsfree(value);
    } while (tok);

    Parse(pParser, 0, yylval, state);
    ParseFree(pParser, free);

    YYSTYPEList l = state->yystypeList;
#if debug
    printf("numbers: %d\n", l.used);
#endif

    sortYYSTYPElist(&l);

    if (l.used == 0) {
        state->result = sdsnew(data);
    } else {
        state->result = sdsempty();
        sds original = sdsnew(data);

        int lastpos = 0;
        for (int i = 0; i < l.used; ++i) {
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

            sds s;
            yystypeToString(&s, y, 3);
            state->result = sdscatsds(state->result, s);

            sdsfree(s);
        }

        sds tmp = sdsdup(original);
        sdsrange(tmp, l.values[l.used-1].epos, -1);
        state->result = sdscatsds(state->result, tmp);
        sdsfree(tmp);
        sdsfree(original);
    }

    freeYYSTYPElist(&state->yystypeList);
}
