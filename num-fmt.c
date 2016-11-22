#include <stdio.h>
#include <string.h>
#include "sds.h"
#include "fpconv.h"

/*
 * From http://stackoverflow.com/a/277810/435460, but converted to use sds.
 */

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

    /*char buf[24 + 1];*/
    /*int str_len = fpconv_dtoa(d, n, buf);*/
    /*printf("%d\n", str_len);*/
    /*buf[str_len] = '\0';*/
    /*printf("fpconv_dtoa: %s\n", buf);*/

    // Create format string then use it.
    *s = sdscatprintf(*s, "%*.*f", sz, n, d);
    /*printf("sdscatprintf: %s\n", *s);*/
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
