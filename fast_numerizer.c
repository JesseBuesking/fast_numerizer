#include "fast_numerizer.h"

#define TOKEN_SEPARATOR 10000

void numerize(const char *data, ParserState *state) {
    YYSTYPE yylval;

    scanstate ss;
    scanstate_init(&ss, NULL, 0);
    readmem_attach(&ss, data, strlen(data));

    int tok;
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

        // set the underlying value
        sds value = sdsnewlen(ss.token, scan_token_length(&ss));

#if debug
        printf("token is \"%s\"\n", value);
#endif

        if (tok == TOKEN_NUMBER) {
            sscanf(value, "%lf", &yylval.double_value);
        }

        if (tok != TOKEN_SEPARATOR) {
            Parse(pParser, tok, yylval, state);
        }
    } while (tok);

    Parse(pParser, 0, yylval, state);
    ParseFree(pParser, free);
}
