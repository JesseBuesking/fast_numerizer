#ifndef SCANNER_DEF_H
#define SCANNER_DEF_H

#include "sds.h"

enum suffixValues
{
    NONE,
    ST,
    STS,
    ND,
    NDS,
    RD,
    RDS,
    TH,
    THS
};

typedef struct {
    double double_value;
    enum suffixValues suffix;
    double frac_num;
    double frac_denom;
    unsigned int is_frac;
    unsigned int spos;
    unsigned int epos;
} YYSTYPE;

typedef struct {
    int precision;
    sds result;
} ParserState;

#endif // SCANNER_DEF_H
