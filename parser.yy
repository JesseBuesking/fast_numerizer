%token_prefix TOKEN_

%token_type { YYSTYPE }

%extra_argument { ParserState *state }

%include {
#include <assert.h>
#include <stdio.h>
#include "scanner.def.h"
}

%syntax_error {
    fprintf(stderr, "Syntax error\n");
}

%parse_failure {
    fprintf(stderr,"Giving up.  Parser is hopelessly lost...\n");
}

%start_symbol program

program ::= expr(A). {
    state->result = A.double_value;
}

/*expr(A) ::= direct_num(B) big_prefix(C). { A.double_value = B.double_value * C.double_value; }*/
/*expr(A) ::= single_num(B) big_prefix(C). { A.double_value = B.double_value * C.double_value; }*/

expr(A) ::= direct_num(B) single_ordinal(C). { A.double_value = B.double_value / C.double_value; }
expr(A) ::= single_num(B) single_ordinal(C). { A.double_value = B.double_value / C.double_value; }

expr(A) ::= direct_num(B). { A.double_value = B.double_value; }
expr(A) ::= single_num(B). { A.double_value = B.double_value; }

/*expr(A) ::= ten_prefix(B) single_num(C) big_prefix(D). { A.double_value = (B.double_value + C.double_value) * D.double_value; }*/

expr(A) ::= ten_prefix(B) single_num(C). { A.double_value = B.double_value + C.double_value; }
expr(A) ::= ten_prefix(B) single_ordinal(C). { A.double_value = B.double_value + C.double_value; }
expr(A) ::= ten_prefix(B). { A.double_value = B.double_value; }

expr(A) ::= big_prefix(B). { A.double_value = B.double_value; }
expr(A) ::= single_num(B) big_prefix(C). { A.double_value = B.double_value * C.double_value; }
expr(A) ::= direct_num(B) big_prefix(C). { A.double_value = B.double_value * C.double_value; }

single_num(A) ::= ONE. { A.double_value = 1.0; }
single_num(A) ::= TWO. { A.double_value = 2.0; }
single_num(A) ::= THREE. { A.double_value = 3.0; }
single_num(A) ::= FOUR. { A.double_value = 4.0; }
single_num(A) ::= FIVE. { A.double_value = 5.0; }
single_num(A) ::= SIX. { A.double_value = 6.0; }
single_num(A) ::= SEVEN. { A.double_value = 7.0; }
single_num(A) ::= EIGHT. { A.double_value = 8.0; }
single_num(A) ::= NINE. { A.double_value = 9.0; }

direct_num(A) ::= ZERO. { A.double_value = 0.0; }
direct_num(A) ::= TEN. { A.double_value = 10.0; }
direct_num(A) ::= ELEVEN. { A.double_value = 11.0; }
direct_num(A) ::= TWELVE. { A.double_value = 12.0; }
direct_num(A) ::= THIRTEEN. { A.double_value = 13.0; }
direct_num(A) ::= FOURTEEN. { A.double_value = 14.0; }
direct_num(A) ::= FIFTEEN. { A.double_value = 15.0; }
direct_num(A) ::= SIXTEEN. { A.double_value = 16.0; }
direct_num(A) ::= SEVENTEEN. { A.double_value = 17.0; }
direct_num(A) ::= EIGHTEEN. { A.double_value = 18.0; }
direct_num(A) ::= NINETEEN. { A.double_value = 19.0; }

ten_prefix(A) ::= TWENTY. { A.double_value = 20.0; }
ten_prefix(A) ::= THIRTY. { A.double_value = 30.0; }
ten_prefix(A) ::= FORTY. { A.double_value = 40.0; }
ten_prefix(A) ::= FIFTY. { A.double_value = 50.0; }
ten_prefix(A) ::= SIXTY. { A.double_value = 60.0; }
ten_prefix(A) ::= SEVENTY. { A.double_value = 70.0; }
ten_prefix(A) ::= EIGHTY. { A.double_value = 80.0; }
ten_prefix(A) ::= NINETY. { A.double_value = 90.0; }

big_prefix(A) ::= HUNDRED. { A.double_value = 100.0; }
big_prefix(A) ::= THOUSAND. { A.double_value = 1000.0; }
big_prefix(A) ::= MILLION. { A.double_value = 1000000.0; }
big_prefix(A) ::= BILLION. { A.double_value = 1000000000.0; }
big_prefix(A) ::= TRILLION. { A.double_value = 1000000000000.0; }

single_ordinal(A) ::= FIRST. { A.double_value = 1.0; }
single_ordinal(A) ::= THIRD. { A.double_value = 3.0; }
single_ordinal(A) ::= FOURTH. { A.double_value = 4.0; }
single_ordinal(A) ::= FIFTH. { A.double_value = 5.0; }
single_ordinal(A) ::= SIXTH. { A.double_value = 6.0; }
single_ordinal(A) ::= SEVENTH. { A.double_value = 7.0; }
single_ordinal(A) ::= EIGHTH. { A.double_value = 8.0; }
single_ordinal(A) ::= NINTH. { A.double_value = 9.0; }

single_ordinal(A) ::= HALF. { A.double_value = 2.0; }
single_ordinal(A) ::= QUARTER. { A.double_value = 4.0; }
