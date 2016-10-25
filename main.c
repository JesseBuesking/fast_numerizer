#include <assert.h>
#include <stdlib.h>

#include "scanner.h"
#include "parser.c"

#include "libre2c/scan.h"
#include "libre2c/readmem.h"

int main() {
    YYSTYPE yylval;

    const char *data = "one quarter";

    scanstate ss;
    scanstate_init(&ss, NULL, 0);
    readmem_attach(&ss, data, strlen(data));

    int tok;
    void *pParser = ParseAlloc(malloc);

	// Initialize the scanner to read from this string constant.
    readmem_init_str(&ss, data);
    ss.line = 1;

    ParseTrace(stderr, (char*)"[Parser] >> ");
    ParserState state;

    do
    {
        tok = numerizer_start(&ss);
        printf("line %2d, token %d\n", ss.line, tok);
        /*printf("%2d: %-12s", ss.line, tokname[tok]);*/

        if(tok == 0) {
            printf("End of string\n");
            break;
        }

        if(tok < 0) {
            printf("Scanner returned an error: %d\n", tok);
            break;
        }

        /*printf("<<%.*s>>", token_length(&ss), token_start(&ss));*/
        printf("<<%ld %s>>\n", scan_token_length(&ss), scan_token_start(&ss));
        Parse(pParser, tok, yylval, &state);

        /*if(tok != NEWLINE) {*/
            /*// don't want to actually print the text of the newline*/
            /*// token -- it makes the output ugly.*/
            /*printf("<<%.*s>>", scan_token_length(&ss),*/
                    /*scan_token_start(&ss));*/
        /*}*/
        printf("\n");
    } while (tok);

    /*// scanner.scan return 0 when get EOF.*/
    /*while (tok = numerizer_start(in)) {*/
        /*// printf("GET TOKEN: %d\n", tok);*/
        /*Parse(pParser, tok, yylval, &state);*/
    /*}*/
    Parse(pParser, 0, yylval, &state);
    ParseFree(pParser, free);

    printf("RESULT: %f\n", state.result);
    return 0;
}
