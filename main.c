#include "fast_numerizer.h"

int main() {
    double result;
    /*const char *data = "one quarter";*/
    const char *data = "fifteen thousand";

    result = numerize(data);

    printf("RESULT: %f\n", result);
    return 0;
}
