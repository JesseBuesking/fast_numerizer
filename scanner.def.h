#ifndef CALC_SCANNER_DEF_H_
#define CALC_SCANNER_DEF_H_

typedef union {
    double double_value;
} YYSTYPE;

typedef struct {
    double result;
} ParserState;

#endif // CALC_SCANNER_DEF_H_
