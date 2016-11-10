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
    YYSTYPE *values;
    size_t used;
    size_t size;
} YYSTYPEList;

typedef struct {
    int precision;
    sds result;
    YYSTYPEList yystypeList;
} ParserState;

void initYYSTYPEList(YYSTYPEList *l, size_t initialSize);
void insertYYSTYPE(YYSTYPEList *l, YYSTYPE element);
void freeYYSTYPElist(YYSTYPEList *l);

#endif // SCANNER_DEF_H
