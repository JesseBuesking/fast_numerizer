#ifndef CALC_SCANNER_DEF_H_
#define CALC_SCANNER_DEF_H_

typedef union {
    double double_value;
} YYSTYPE;

struct ParserState {
    double result;
    ParserState() :result(0) {
    }
};

#endif // CALC_SCANNER_DEF_H_
