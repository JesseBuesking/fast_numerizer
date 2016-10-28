#ifndef SCANNER_DEF_H
#define SCANNER_DEF_H

typedef union {
    double double_value;
} YYSTYPE;

typedef struct {
    double result;
} ParserState;

#endif // SCANNER_DEF_H
