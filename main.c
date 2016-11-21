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
    const char *data_one = "one two three four five";
    const char *data_two = "one hundred";
    /*const char *data_three = "two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello two hundred hello ";*/
    const char *data_three = "two hundred hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world ";
    int i = 0;

    initFastNumerizer();

    ParserState state;
    initParserState(&state);

    /*// TODO set precision by passed in value*/
    /*state.precision = 3;*/

    for (i = 0; i < 1000; i++) {
        const char *data;
        /*if (i % 3 == 0) {*/
            /*data = data_one;*/
        /*} else if (i % 3 == 1) {*/
            /*data = data_two;*/
        /*} else if (i % 3 == 2) {*/
            /*data = data_three;*/
        /*}*/
        data = data_three;

        /*printf("Input: '%s'\n", data);*/

        numerize(data, strlen(data), &state);

        /*printf("Output: '%s'\n", state.result);*/

        resetParserState(&state);
    }

    freeParserState(&state);
    freeFastNumerizer();

    return 0;
}
