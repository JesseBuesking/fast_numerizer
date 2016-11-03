#include "fast_numerizer.h"

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
#if debug
            printf("End of string\n");
#endif
            break;
        }

        if (tok < 0) {
            printf("Scanner returned an error: %d\n", tok);
            break;
        }

        // set the underlying value
        yylval.value = sdsnewlen(ss.token, scan_token_length(&ss));

#if debug
        printf("token is \"%s\"\n", yylval.value);
#endif

        Parse(pParser, tok, yylval, state);
    } while (tok);

    Parse(pParser, 0, yylval, state);
    ParseFree(pParser, free);
}
