#ifndef CALC_SCANNER_H_
#define CALC_SCANNER_H_

#include <stdio.h>
#include <string.h>
#include "scanner.def.h"
#include "parser.h"

/* example of how to parse string at
 * https://github.com/skvadrik/re2c/blob/master/libre2c/examples/numscan-coupled/numscan.re
 */

/*!max:re2c*/

struct input_t {
    size_t len;
    char *str;
    char *mrk;

    input_t(const char *s)
        : len(strlen(s))
        , str(new char[len + YYMAXFILL])
        , mrk(0)
    {
        memcpy(str, s, len);
        memset(str + len, 'a', YYMAXFILL);
    }
    ~input_t()
    {
        delete[]str;
    }
};

int[] lex(input_t & input) {
    int res[2];
std:
    char *YYCURSOR = input.str;
    char *const YYLIMIT = input.str + input.len + YYMAXFILL;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYFILL = "return false;";
        re2c:define:YYMARKER = input.mrk;
        re2c:define:YYFILL:naked = 1;

        WS                     = [ \r\n\t\f];
        ANY_CHARACTER          = [^];
        END                    = "\x00";

        'zero' { return TOKEN_ZERO; }
        'one' { return TOKEN_ONE; }
        'two' { return TOKEN_TWO; }
        'three' { return TOKEN_THREE; }
        'four' { return TOKEN_FOUR; }
        'five' { return TOKEN_FIVE; }
        'six' { return TOKEN_SIX; }
        'seven' { return TOKEN_SEVEN; }
        'eight' { return TOKEN_EIGHT; }
        'nine' { return TOKEN_NINE; }
        'ten' { return TOKEN_TEN; }
        'eleven' { return TOKEN_ELEVEN; }
        'twelve' { return TOKEN_TWELVE; }
        'thirteen' { return TOKEN_THIRTEEN; }
        'fourteen' { return TOKEN_FOURTEEN; }
        'fifteen' { return TOKEN_FIFTEEN; }
        'sixteen' { return TOKEN_SIXTEEN; }
        'seventeen' { return TOKEN_SEVENTEEN; }
        'eighteen' { return TOKEN_EIGHTEEN; }
        'nineteen' { return TOKEN_NINETEEN; }
        'ninteen' { return TOKEN_NINETEEN; }

        'twenty' { return TOKEN_TWENTY; }
        'thirty' { return TOKEN_THIRTY; }
        'forty' { return TOKEN_FORTY; }
        'fourty' { return TOKEN_FORTY; }
        'fifty' { return TOKEN_FIFTY; }
        'sixty' { return TOKEN_SIXTY; }
        'seventy' { return TOKEN_SEVENTY; }
        'eighty' { return TOKEN_EIGHTY; }
        'ninety' { return TOKEN_NINETY; }

        'hundred' { return TOKEN_HUNDRED; }
        'thousand' { return TOKEN_THOUSAND; }
        'million' { return TOKEN_MILLION; }
        'billion' { return TOKEN_BILLION; }
        'trillion' { return TOKEN_TRILLION; }

        'first' { return TOKEN_FIRST; }
        'third' { return TOKEN_THIRD; }
        'thirds' { return TOKEN_THIRD; }
        'fourth' { return TOKEN_FOURTH; }
        'fourths' { return TOKEN_FOURTH; }
        'fifth' { return TOKEN_FIFTH; }
        'fifths' { return TOKEN_FIFTH; }
        'sixth' { return TOKEN_SIXTH; }
        'sixths' { return TOKEN_SIXTH; }
        'seventh' { return TOKEN_SEVENTH; }
        'sevenths' { return TOKEN_SEVENTH; }
        'eighth' { return TOKEN_EIGHTH; }
        'eighths' { return TOKEN_EIGHTH; }
        'nineth' { return TOKEN_NINTH; }
        'nineths' { return TOKEN_NINTH; }
        'ninth' { return TOKEN_NINTH; }
        'ninths' { return TOKEN_NINTH; }

        'quarter' { return TOKEN_QUARTER; }
        'quarters' { return TOKEN_QUARTER; }

        'half' { return TOKEN_HALF; }

        ANY_CHARACTER {
            return false;
        }
        WS {
            goto std;
        }
        END { return 0; }
    */
}

#endif // CALC_SCANNER_H_
