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
    if (A.value != NULL) {
        state->result = A.value;
    } else {
        state->result = sdsnewlen("", 1024); // TODO stop specifying buffer
        doubleToString(state->result, A.double_value, state->precision);

        state->result = sdsRemoveFreeSpace(state->result);

        if (A.has_suffix) {
            sds tmp = sdscpy(sdsempty(), state->result);
            /*sdsfree(state->result);*/
            /*state->result = sdscatsds(tmp, A.suffix);*/
            /*sdsfree(A.suffix);*/
        }

        state->result = sdsRemoveFreeSpace(state->result);
    }
}

expr(A) ::= final_number(B). { A.double_value = B.double_value; }

expr(A) ::= identifier(B) any_token(C). {
    B.value = sdscat(B.value, C.value);
    sdsfree(C.value);
    A.value = sdsempty();
    A.value = sdscat(A.value, B.value);
    sdsfree(B.value);
}

expr(A) ::= identifier(B). {
    if (B.value == NULL) {
        printf("B.value is NULL");
    } else {
        A.value = B.value;
        printf("identifer(A): %s\n", A.value);
    }
}

/*examples:*/
/*nine hundred ninety nine*/
/*hundred ninety nine*/
/*ninety nine*/

final_number(A) ::= combo(B) separator sub_hundred(C). { A.double_value = B.double_value + C.double_value; }
final_number(A) ::= sub_hundred(B). { A.double_value = B.double_value; }

/*one or more groups*/
combo(A) ::= combo(B) separator group(C). { A.double_value = B.double_value + C.double_value; printf("A is %lf\n.", A.double_value); }
combo(A) ::= group(B). { A.double_value = B.double_value; printf("A is %lf\n.", A.double_value); }

group(A) ::= sub_hundred(B) separator place(C). { A.double_value = B.double_value * C.double_value; printf("A is %lf\n.", A.double_value); }

sub_hundred(A) ::= double_digit(B). { A.double_value = B.double_value; printf("A is %lf\n.", A.double_value); }
sub_hundred(A) ::= single_digit(B). { A.double_value = B.double_value; printf("A is %lf\n.", A.double_value); }
sub_hundred(A) ::= ZERO. { A.double_value = 0.0; }

double_digit(A) ::= ten_prefix(B) separator single_num(C). { A.double_value = B.double_value + C.double_value; printf("A is %lf\n.", A.double_value); }
double_digit(A) ::= direct_num(B). { A.double_value = B.double_value; printf("A is %lf\n.", A.double_value); }
/*double_digit(A) ::= ten_prefix(B). { A.double_value = B.double_value; printf("A is %lf\n.", A.double_value); }*/

single_digit(A) ::= single_num(B). { A.double_value = B.double_value; printf("A is %lf\n.", A.double_value); }

any_token ::= single_num.
any_token ::= direct_num.
any_token ::= ten_prefix.
any_token ::= place.
any_token ::= single_ordinal.

separator ::= WHITESPACE.
separator ::= HYPHEN.
separator ::= .

single_num(A) ::= ONE(B). { A.double_value = 1.0; A.value = B.value; }
single_num(A) ::= TWO(B). { A.double_value = 2.0; A.value = B.value; }
single_num(A) ::= THREE(B). { A.double_value = 3.0; A.value = B.value; }
single_num(A) ::= FOUR(B). { A.double_value = 4.0; A.value = B.value; }
single_num(A) ::= FIVE(B). { A.double_value = 5.0; A.value = B.value; }
single_num(A) ::= SIX(B). { A.double_value = 6.0; A.value = B.value; }
single_num(A) ::= SEVEN(B). { A.double_value = 7.0; A.value = B.value; }
single_num(A) ::= EIGHT(B). { A.double_value = 8.0; A.value = B.value; }
single_num(A) ::= NINE(B). { A.double_value = 9.0; A.value = B.value; }

direct_num(A) ::= TEN(B). { A.double_value = 10.0; A.value = B.value; }
direct_num(A) ::= ELEVEN(B). { A.double_value = 11.0; A.value = B.value; }
direct_num(A) ::= TWELVE(B). { A.double_value = 12.0; A.value = B.value; }
direct_num(A) ::= THIRTEEN(B). { A.double_value = 13.0; A.value = B.value; }
direct_num(A) ::= FOURTEEN(B). { A.double_value = 14.0; A.value = B.value; }
direct_num(A) ::= FIFTEEN(B). { A.double_value = 15.0; A.value = B.value; }
direct_num(A) ::= SIXTEEN(B). { A.double_value = 16.0; A.value = B.value; }
direct_num(A) ::= SEVENTEEN(B). { A.double_value = 17.0; A.value = B.value; }
direct_num(A) ::= EIGHTEEN(B). { A.double_value = 18.0; A.value = B.value; }
direct_num(A) ::= NINETEEN(B). { A.double_value = 19.0; A.value = B.value; }

ten_prefix(A) ::= TWENTY(B). { A.double_value = 20.0; A.value = B.value; }
ten_prefix(A) ::= THIRTY(B). { A.double_value = 30.0; A.value = B.value; }
ten_prefix(A) ::= FORTY(B). { A.double_value = 40.0; A.value = B.value; }
ten_prefix(A) ::= FIFTY(B). { A.double_value = 50.0; A.value = B.value; }
ten_prefix(A) ::= SIXTY(B). { A.double_value = 60.0; A.value = B.value; }
ten_prefix(A) ::= SEVENTY(B). { A.double_value = 70.0; A.value = B.value; }
ten_prefix(A) ::= EIGHTY(B). { A.double_value = 80.0; A.value = B.value; }
ten_prefix(A) ::= NINETY(B). { A.double_value = 90.0; A.value = B.value; }

place(A) ::= HUNDRED(B). { A.double_value = 100.0; A.value = B.value; }
place(A) ::= THOUSAND(B). { A.double_value = 1000.0; A.value = B.value; }
place(A) ::= MILLION(B). { A.double_value = 1000000.0; A.value = B.value; }
place(A) ::= BILLION(B). { A.double_value = 1000000000.0; A.value = B.value; }
place(A) ::= TRILLION(B). { A.double_value = 1000000000000.0; A.value = B.value; }

single_ordinal(A) ::= FIRST(B). { A.double_value = 1.0; A.suffix = sdsnew("st"); A.has_suffix = true; A.value = B.value; }
single_ordinal(A) ::= SECOND(B). { A.double_value = 2.0; A.suffix = sdsnew("st"); A.has_suffix = true; A.value = B.value; }
single_ordinal(A) ::= THIRD(B). { A.double_value = 3.0; A.suffix = sdsnew("nd"); A.has_suffix = true; A.value = B.value; }
single_ordinal(A) ::= FOURTH(B). { A.double_value = 4.0; A.suffix = sdsnew("rd"); A.has_suffix = true; A.value = B.value; }
single_ordinal(A) ::= FIFTH(B). { A.double_value = 5.0; A.suffix = sdsnew("th"); A.has_suffix = true; A.value = B.value; }
single_ordinal(A) ::= SIXTH(B). { A.double_value = 6.0; A.suffix = sdsnew("th"); A.has_suffix = true; A.value = B.value; }
single_ordinal(A) ::= SEVENTH(B). { A.double_value = 7.0; A.suffix = sdsnew("th"); A.has_suffix = true; A.value = B.value; }
single_ordinal(A) ::= EIGHTH(B). { A.double_value = 8.0; A.suffix = sdsnew("th"); A.has_suffix = true; A.value = B.value; }
single_ordinal(A) ::= NINTH(B). { A.double_value = 9.0; A.suffix = sdsnew("th"); A.has_suffix = true; A.value = B.value; }

single_ordinal(A) ::= HALF(B). { A.double_value = 2.0; A.value = B.value; }
single_ordinal(A) ::= QUARTER(B). { A.double_value = 4.0; A.value = B.value; }

identifier(A) ::= identifier(B) CHARACTER(C). {
    B.value = sdscat(B.value, C.value);
    sdsfree(C.value);
    A.value = sdsempty();
    A.value = sdscat(A.value, B.value);
    sdsfree(B.value);
}

identifier(A) ::= CHARACTER(B). {
    A.value = B.value;
}
