#include "fast_numerizer.h"

int main() {
    /*const char *data = "fifteen thousand";*/
    /*const char *data = "fifth";*/
    /*const char *data = "thirty-first";*/
    /*const char *data = "ninety nine thousand nine hundred ninety nine";*/
    /*const char *data = "ninety nine";*/
    /*const char *data = "one thousand";*/
    /*const char *data = "I am thirty three years old.";*/
    /*const char *data = "twentyone-thousand";*/
    const char *data = "nine hundred and ninety nine";

    ParserState state;
    state.precision = 3;

    numerize(data, &state);

    printf("RESULT: %s\n", state.result);

    sdsfree(state.result);
    return 0;
}
