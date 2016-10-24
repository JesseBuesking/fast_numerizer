#include <assert.h>
#include <stdlib.h>

#include "scanner.h"
#include "parser.c"

int main() {
    YYSTYPE yylval;
    input_t in;
    void *pParser = ParseAlloc(malloc);
    int tokenID;

#if 0
    ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

    ParserState state;
    // scanner.scan return 0 when get EOF.
    while (tokenID = lex(in)) {
        // printf("GET TOKEN: %d\n", tokenID);
        Parse(pParser, tokenID, yylval, &state);
    }
    Parse(pParser, 0, yylval, &state);
    ParseFree(pParser, free);

    printf("RESULT: %f\n", state.result);
    return 0;
}
