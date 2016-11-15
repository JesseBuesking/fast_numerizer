#include "fast_numerizer.h"

int main() {
    /*const char *data = "fifteen thousand";*/
    /*const char *data = "fifth";*/
    /*const char *data = "thirty-first";*/
    /*const char *data = "ninety nine thousand nine hundred ninety nine";*/
    /*const char *data = "ninety nine";*/
    /*const char *data = "one thousand";*/
    /*const char *data = "twentyone-thousand";*/
    /*const char *data = "nine hundred and ninety nine";*/
    /*const char *data = "hundredth";*/
    /*const char *data = "one eighth";*/
    /*const char *data = "I am thirty three years old, third beans.";*/
    /*const char *data = "Today is 27 Oct 2006 7:30am and I love it. One is the best.";*/
    const char *data = "one two three four five";

    ParserState state;
    state.precision = 3;

    printf("Input: '%s'\n", data);

    numerize(data, &state);

    printf("Output: '%s'\n", state.result);

    sdsfree(state.result);
    return 0;
}
