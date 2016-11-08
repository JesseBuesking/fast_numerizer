%token_prefix TOKEN_

%token_type { YYSTYPE }

%extra_argument { ParserState *state }

%include {
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "scanner.def.h"
#include "sds.h"
#include "num-fmt.h"
}

%syntax_error {
    fprintf(stderr, "Syntax error\n");
}

%parse_failure {
    fprintf(stderr,"Giving up.  Parser is hopelessly lost...\n");
}

%start_symbol program

program ::= expr(A). {
    doubleToString(&state->result, A.double_value, state->precision);

    switch (A.suffix) {
        case ST:
            state->result = sdscat(state->result, "st");
            break;
        case STS:
            state->result = sdscat(state->result, "sts");
            break;
        case ND:
            state->result = sdscat(state->result, "nd");
            break;
        case NDS:
            state->result = sdscat(state->result, "nds");
            break;
        case RD:
            state->result = sdscat(state->result, "rd");
            break;
        case RDS:
            state->result = sdscat(state->result, "rds");
            break;
        case TH:
            state->result = sdscat(state->result, "th");
            break;
        case THS:
            state->result = sdscat(state->result, "ths");
            break;
    }

    state->result = sdsRemoveFreeSpace(state->result);
}

expr(A) ::= sentence(B). { A.double_value = B.double_value; A.suffix = B.suffix; }
expr(A) ::= final_number(B). { A.double_value = B.double_value; A.suffix = B.suffix; }
expr ::= .

sentence(A) ::= identifiers final_number(B). { A.double_value = B.double_value; A.suffix = B.suffix; }
sentence(A) ::= final_number(B) identifiers. { A.double_value = B.double_value; A.suffix = B.suffix; }

final_number(A) ::= one_to_999999999999999(B) AND_A QUARTER. { A.double_value = B.double_value + 0.25; }
final_number(A) ::= one_to_999999999999999(B) QUARTERS. { A.double_value = B.double_value / 4.0; }
final_number(A) ::= one_to_999999999999999(B) AND_A HALF. { A.double_value = B.double_value + 0.5; }
final_number(A) ::= one_to_999999999999999(B) HALVES. { A.double_value = B.double_value / 2.0; }
final_number(A) ::= one_to_999999999999999(B). { A.double_value = B.double_value; }
final_number(A) ::= first_to_999th(B). { A.double_value = B.double_value; A.suffix = B.suffix; }
final_number(A) ::= ZERO. { A.double_value = 0.0; }

one_to_999999999999999(A) ::= trillions(B) one_to_999999999999(C). { A.double_value = B.double_value + C.double_value; }
one_to_999999999999999(A) ::= trillions(B). { A.double_value = B.double_value; }
one_to_999999999999999(A) ::= one_to_999999999999(B). { A.double_value = B.double_value; }

trillions(A) ::= one_to_999999999999(B) TRILLION. { A.double_value = B.double_value * 1000000000000.0; }
trillions(A) ::= NUMBER(B) TRILLION. { A.double_value = B.double_value * 1000000000000.0; }
trillions(A) ::= TRILLION. { A.double_value = 1000000000000.0; }

/* -------------------------------------- */

one_to_999999999999(A) ::= billions(B) one_to_999999999(C). { A.double_value = B.double_value + C.double_value; }
one_to_999999999999(A) ::= billions(B). { A.double_value = B.double_value; }
one_to_999999999999(A) ::= one_to_999999999(B). { A.double_value = B.double_value; }

billions(A) ::= one_to_999999999(B) BILLION. { A.double_value = B.double_value * 1000000000.0; }
billions(A) ::= NUMBER(B) BILLION. { A.double_value = B.double_value * 1000000000.0; }
billions(A) ::= BILLION. { A.double_value = 1000000000.0; }

/* -------------------------------------- */

one_to_999999999(A) ::= millions(B) one_to_999999(C). { A.double_value = B.double_value + C.double_value; }
one_to_999999999(A) ::= millions(B). { A.double_value = B.double_value; }
one_to_999999999(A) ::= one_to_999999(B). { A.double_value = B.double_value; }

millions(A) ::= one_to_999999(B) MILLION. { A.double_value = B.double_value * 1000000.0; }
millions(A) ::= NUMBER(B) MILLION. { A.double_value = B.double_value * 1000000.0; }
millions(A) ::= MILLION. { A.double_value = 1000000.0; }

/* -------------------------------------- */

one_to_999999(A) ::= thousands(B) one_to_999(C). { A.double_value = B.double_value + C.double_value; }
one_to_999999(A) ::= thousands(B). { A.double_value = B.double_value; }
one_to_999999(A) ::= one_to_999(B). { A.double_value = B.double_value; }

thousands(A) ::= one_to_999(B) THOUSAND. { A.double_value = B.double_value * 1000.0; }
thousands(A) ::= NUMBER(B) THOUSAND. { A.double_value = B.double_value * 1000.0; }
thousands(A) ::= THOUSAND. { A.double_value = 1000.0; }

/* --------------------------------------
sub thousand ordinal
-------------------------------------- */

first_to_999th(A) ::= hundredths(B) AND first_to_99th(C). { A.double_value = B.double_value + C.double_value; A.suffix = B.suffix; }
first_to_999th(A) ::= hundredths(B) first_to_99th(C). { A.double_value = B.double_value + C.double_value; A.suffix = B.suffix; }
first_to_999th(A) ::= hundredths(B). { A.double_value = B.double_value; A.suffix = B.suffix; }
first_to_999th(A) ::= AND first_to_99th(B). { A.double_value = B.double_value; A.suffix = B.suffix; }
first_to_999th(A) ::= first_to_99th(B). { A.double_value = B.double_value; A.suffix = B.suffix; }

hundredths(A) ::= one_to_99(B) HUNDREDTH. { A.double_value = B.double_value * 100.0; A.suffix = TH; }
hundredths(A) ::= one_to_99(B) HUNDREDTHS. { A.double_value = B.double_value * 100.0; A.suffix = THS; }
hundredths(A) ::= NUMBER(B) HUNDREDTH. { A.double_value = B.double_value * 100.0; A.suffix = TH; }
hundredths(A) ::= NUMBER(B) HUNDREDTHS. { A.double_value = B.double_value * 100.0; A.suffix = THS; }
hundredths(A) ::= HUNDREDTH. { A.double_value = 100.0; A.suffix = TH; }
hundredths(A) ::= HUNDREDTHS. { A.double_value = 100.0; A.suffix = THS; }

first_to_99th(A) ::= tens(B) first_to_9th(C). { A.double_value = B.double_value + C.double_value; A.suffix = B.suffix; }
first_to_99th(A) ::= tenths(B). { A.double_value = B.double_value; A.suffix = B.suffix; }
first_to_99th(A) ::= tenth_to_19th(B). { A.double_value = B.double_value; A.suffix = B.suffix; }
first_to_99th(A) ::= first_to_9th(B). { A.double_value = B.double_value; A.suffix = B.suffix; }

/* --------------------------------------
sub thousand regular
-------------------------------------- */

one_to_999(A) ::= hundreds(B) AND one_to_99(C). { A.double_value = B.double_value + C.double_value; }
one_to_999(A) ::= hundreds(B) one_to_99(C). { A.double_value = B.double_value + C.double_value; }
one_to_999(A) ::= hundreds(B). { A.double_value = B.double_value; }
one_to_999(A) ::= AND one_to_99(B). { A.double_value = B.double_value; }
one_to_999(A) ::= one_to_99(B). { A.double_value = B.double_value; }

hundreds(A) ::= one_to_99(B) HUNDRED. { A.double_value = B.double_value * 100.0; }
hundreds(A) ::= NUMBER(B) HUNDRED. { A.double_value = B.double_value * 100.0; }
hundreds(A) ::= HUNDRED. { A.double_value = 100.0; }

one_to_99(A) ::= tens(B) one_to_9(C). { A.double_value = B.double_value + C.double_value; }
one_to_99(A) ::= tens(B). { A.double_value = B.double_value; }
one_to_99(A) ::= ten_to_19(B). { A.double_value = B.double_value; }
one_to_99(A) ::= one_to_9(B). { A.double_value = B.double_value; }

/* --------------------------------------
basic terminals
-------------------------------------- */

one_to_9(A) ::= ONE. { A.double_value = 1.0; }
one_to_9(A) ::= TWO. { A.double_value = 2.0; }
one_to_9(A) ::= THREE. { A.double_value = 3.0; }
one_to_9(A) ::= FOUR. { A.double_value = 4.0; }
one_to_9(A) ::= FIVE. { A.double_value = 5.0; }
one_to_9(A) ::= SIX. { A.double_value = 6.0; }
one_to_9(A) ::= SEVEN. { A.double_value = 7.0; }
one_to_9(A) ::= EIGHT. { A.double_value = 8.0; }
one_to_9(A) ::= NINE. { A.double_value = 9.0; }

ten_to_19(A) ::= TEN. { A.double_value = 10.0; }
ten_to_19(A) ::= ELEVEN. { A.double_value = 11.0; }
ten_to_19(A) ::= TWELVE. { A.double_value = 12.0; }
ten_to_19(A) ::= THIRTEEN. { A.double_value = 13.0; }
ten_to_19(A) ::= FOURTEEN. { A.double_value = 14.0; }
ten_to_19(A) ::= FIFTEEN. { A.double_value = 15.0; }
ten_to_19(A) ::= SIXTEEN. { A.double_value = 16.0; }
ten_to_19(A) ::= SEVENTEEN. { A.double_value = 17.0; }
ten_to_19(A) ::= EIGHTEEN. { A.double_value = 18.0; }
ten_to_19(A) ::= NINETEEN. { A.double_value = 19.0; }

tens(A) ::= TWENTY. { A.double_value = 20.0; }
tens(A) ::= THIRTY. { A.double_value = 30.0; }
tens(A) ::= FORTY. { A.double_value = 40.0; }
tens(A) ::= FIFTY. { A.double_value = 50.0; }
tens(A) ::= SIXTY. { A.double_value = 60.0; }
tens(A) ::= SEVENTY. { A.double_value = 70.0; }
tens(A) ::= EIGHTY. { A.double_value = 80.0; }
tens(A) ::= NINETY. { A.double_value = 90.0; }

first_to_9th(A) ::= FIRST. { A.double_value = 1.0; A.suffix = ST; }
first_to_9th(A) ::= FIRSTS. { A.double_value = 1.0; A.suffix = STS; }
first_to_9th(A) ::= SECOND. { A.double_value = 2.0; A.suffix = ND; }
first_to_9th(A) ::= SECONDS. { A.double_value = 2.0; A.suffix = NDS; }
first_to_9th(A) ::= THIRD. { A.double_value = 3.0; A.suffix = RD; }
first_to_9th(A) ::= THIRDS. { A.double_value = 3.0; A.suffix = RDS; }
first_to_9th(A) ::= FOURTH. { A.double_value = 4.0; A.suffix = TH; }
first_to_9th(A) ::= FOURTHS. { A.double_value = 4.0; A.suffix = THS; }
first_to_9th(A) ::= FIFTH. { A.double_value = 5.0; A.suffix = TH; }
first_to_9th(A) ::= FIFTHS. { A.double_value = 5.0; A.suffix = THS; }
first_to_9th(A) ::= SIXTH. { A.double_value = 6.0; A.suffix = TH; }
first_to_9th(A) ::= SIXTHS. { A.double_value = 6.0; A.suffix = THS; }
first_to_9th(A) ::= SEVENTH. { A.double_value = 7.0; A.suffix = TH; }
first_to_9th(A) ::= SEVENTHS. { A.double_value = 7.0; A.suffix = THS; }
first_to_9th(A) ::= EIGHTH. { A.double_value = 8.0; A.suffix = TH; }
first_to_9th(A) ::= EIGHTHS. { A.double_value = 8.0; A.suffix = THS; }
first_to_9th(A) ::= NINTH. { A.double_value = 9.0; A.suffix = TH; }
first_to_9th(A) ::= NINTHS. { A.double_value = 9.0; A.suffix = THS; }

tenth_to_19th(A) ::= TENTH. { A.double_value = 10.0; A.suffix = TH; }
tenth_to_19th(A) ::= TENTHS. { A.double_value = 10.0; A.suffix = THS; }
tenth_to_19th(A) ::= ELEVENTH. { A.double_value = 11.0; A.suffix = TH; }
tenth_to_19th(A) ::= ELEVENTHS. { A.double_value = 11.0; A.suffix = THS; }
tenth_to_19th(A) ::= TWELFTH. { A.double_value = 12.0; A.suffix = TH; }
tenth_to_19th(A) ::= TWELFTHS. { A.double_value = 12.0; A.suffix = THS; }
tenth_to_19th(A) ::= THIRTEENTH. { A.double_value = 13.0; A.suffix = TH; }
tenth_to_19th(A) ::= THIRTEENTHS. { A.double_value = 13.0; A.suffix = THS; }
tenth_to_19th(A) ::= FOURTEENTH. { A.double_value = 14.0; A.suffix = TH; }
tenth_to_19th(A) ::= FOURTEENTHS. { A.double_value = 14.0; A.suffix = THS; }
tenth_to_19th(A) ::= FIFTEENTH. { A.double_value = 15.0; A.suffix = TH; }
tenth_to_19th(A) ::= FIFTEENTHS. { A.double_value = 15.0; A.suffix = THS; }
tenth_to_19th(A) ::= SIXTEENTH. { A.double_value = 16.0; A.suffix = TH; }
tenth_to_19th(A) ::= SIXTEENTHS. { A.double_value = 16.0; A.suffix = THS; }
tenth_to_19th(A) ::= SEVENTEENTH. { A.double_value = 17.0; A.suffix = TH; }
tenth_to_19th(A) ::= SEVENTEENTHS. { A.double_value = 17.0; A.suffix = THS; }
tenth_to_19th(A) ::= EIGHTEENTH. { A.double_value = 18.0; A.suffix = TH; }
tenth_to_19th(A) ::= EIGHTEENTHS. { A.double_value = 18.0; A.suffix = THS; }
tenth_to_19th(A) ::= NINETEENTH. { A.double_value = 19.0; A.suffix = TH; }
tenth_to_19th(A) ::= NINETEENTHS. { A.double_value = 19.0; A.suffix = THS; }

tenths(A) ::= TWENTIETH. { A.double_value = 20.0; A.suffix = TH; }
tenths(A) ::= TWENTIETHS. { A.double_value = 20.0; A.suffix = THS; }
tenths(A) ::= THIRTIETH. { A.double_value = 30.0; A.suffix = TH; }
tenths(A) ::= THIRTIETHS. { A.double_value = 30.0; A.suffix = THS; }
tenths(A) ::= FOURTIETH. { A.double_value = 40.0; A.suffix = TH; }
tenths(A) ::= FOURTIETHS. { A.double_value = 40.0; A.suffix = THS; }
tenths(A) ::= FIFTIETH. { A.double_value = 50.0; A.suffix = TH; }
tenths(A) ::= FIFTIETHS. { A.double_value = 50.0; A.suffix = THS; }
tenths(A) ::= SIXTIETH. { A.double_value = 60.0; A.suffix = TH; }
tenths(A) ::= SIXTIETHS. { A.double_value = 60.0; A.suffix = THS; }
tenths(A) ::= SEVENTIETH. { A.double_value = 70.0; A.suffix = TH; }
tenths(A) ::= SEVENTIETHS. { A.double_value = 70.0; A.suffix = THS; }
tenths(A) ::= EIGHTIETH. { A.double_value = 80.0; A.suffix = TH; }
tenths(A) ::= EIGHTIETHS. { A.double_value = 80.0; A.suffix = THS; }
tenths(A) ::= NINETIETH. { A.double_value = 90.0; A.suffix = TH; }
tenths(A) ::= NINETIETHS. { A.double_value = 90.0; A.suffix = THS; }

identifiers ::= identifiers CHARACTERS.
identifiers ::= CHARACTERS.
