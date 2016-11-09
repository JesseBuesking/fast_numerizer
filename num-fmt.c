#include <stdio.h>
#include <string.h>
#include "sds.h"

void nDecimals(sds *s, double d, int n) {
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
    *s = sdscatprintf(sdsempty(), "%*.*f", sz, n, d);
}

void morphNumericString(sds *s, int n) {
    char *p = strchr(*s, '.');                    // Find decimal point, if any.
    if (p != NULL) {
        int dotPosition = (p - *s);
        int endRange = dotPosition + n;
        int lastPosition = (int) sdslen(*s) - 1;

        endRange = endRange < lastPosition ? endRange : lastPosition;

        while ((*s)[endRange] == '0') {     // Remove trailing zeros.
            endRange -= 1;
        }

        if ((*s)[endRange] == '.') {        // If all decimals were zeros, remove "."
            endRange -= 1;
        }

        sdsrange(*s, 0, endRange);          // Trim the string to the range.
    }
}

void doubleToString(sds *s, double d, int precision) {
    nDecimals(s, d, precision);
    morphNumericString(s, precision);
}
