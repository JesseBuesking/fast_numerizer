#ifndef SCANNER_DEF_H
#define SCANNER_DEF_H

#include "sds.h"

typedef union {
    double double_value;
} YYSTYPE;

typedef struct {
    int precision;
    sds result;
} ParserState;

#endif // SCANNER_DEF_H
