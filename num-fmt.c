#include <stdio.h>
#include "sds.h"

void doubleToString(sds s, double d, int precision) {
    nDecimals(s, d, precision);
    morphNumericString(s, precision);
}

void nDecimals(sds s, double d, int n) {
    int sz; double d2;

    // Allow for negative.

    d2 = (d >= 0) ? d : -d;
    sz = (d >= 0) ? 0 : 1;

    // Add one for each whole digit (0.xx special case).

    if (d2 < 1) {
        sz++;
    }
    while (d2 >= 1) {
        d2 /= 10.0;
        sz++;
    }

    // Adjust for decimal point and fractionals.

    sz += 1 + n;

    // Create format string then use it.
    /*sprintf(s, "%*.*f", sz, n, d);*/
    sds tmp = sdscatprintf(sdsempty(), "%*.*f", sz, n, d);
    sdscpy(s, tmp);
    sdsfree(tmp);
}

void morphNumericString(sds s, int n) {
    char *p;
    int count;

    p = strchr(s, '.');         // Find decimal point, if any.
    if (p != NULL) {
        count = n;              // Adjust for more or less decimals.
        while (count >= 0) {    // Maximum decimals allowed.
            count--;
            if (*p == '\0')     // If there's less than desired.
                break;
            p++;                // Next character.
        }

        *p-- = '\0';            // Truncate string.
        while (*p == '0') {     // Remove trailing zeros.
            *p-- = '\0';
        }

        if (*p == '.') {        // If all decimals were zeros, remove ".".
            *p = '\0';
        }
    }
}
