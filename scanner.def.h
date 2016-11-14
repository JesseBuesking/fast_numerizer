#ifndef SCANNER_DEF_H
#define SCANNER_DEF_H

#include "sds.h"

enum suffixValues
{
    NO_SUFFIX,
    ST,
    STS,
    ND,
    NDS,
    RD,
    RDS,
    TH,
    THS
};

enum errors {
    NO_ERROR,
    SYNTAX_ERROR,
    PARSE_FAILURE
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
    enum errors error;
    YYSTYPEList yystypeList;
} ParserState;

void initYYSTYPEList(YYSTYPEList *l, size_t initialSize);
void insertYYSTYPE(YYSTYPEList *l, YYSTYPE element);
void freeYYSTYPElist(YYSTYPEList *l);
void sortYYSTYPElist(YYSTYPEList *l);

#endif // SCANNER_DEF_H
