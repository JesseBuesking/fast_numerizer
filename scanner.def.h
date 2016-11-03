#ifndef SCANNER_DEF_H
#define SCANNER_DEF_H

#include <stdbool.h>
#include "sds.h"

typedef struct {
    double double_value;
    sds value;
    bool has_suffix;
    sds suffix;
} YYSTYPE;

typedef struct {
    int precision;
    sds result;
} ParserState;

#endif // SCANNER_DEF_H
