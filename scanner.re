#ifndef CALC_SCANNER_H_
#define CALC_SCANNER_H_

#include <stdio.h>
#include <string.h>
#include "scanner.def.h"
#include "parser.h"

/*!max:re2c*/
static const size_t SIZE = 1024;

struct input_t {
    char buf[SIZE + YYMAXFILL];
    char *lim;
    char *cur;
    char *tok;
    char *mrk;
    bool eof;

    input_t()
        : buf()
        , lim(buf + SIZE)
        , cur(lim)
        , tok(lim)
        , mrk(0)
        , eof(false)
    {}

    bool fill(size_t need)
    {
        if (eof) {
            return false;
        }
        const size_t free = tok - buf;
        if (free < need) {
            return false;
        }
        memmove(buf, tok, lim - tok);
        lim -= free;
        cur -= free;
        tok -= free;
        lim += fread(lim, 1, free, stdin);
        if (lim < buf + SIZE) {
            eof = true;
            memset(lim, 0, YYMAXFILL);
            lim += YYMAXFILL;
        }
        return true;
    }
};

int lex(input_t & in) {
std:
    in.tok = in.cur;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = in.cur;
        re2c:define:YYLIMIT = in.lim;
        re2c:define:YYMARKER = in.mrk;
        re2c:define:YYFILL:naked = 1;
        re2c:define:YYFILL@len = #;
        re2c:define:YYFILL = "if (!in.fill(#)) { return 0; }";

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

        WS {
            goto std;
        }
        ANY_CHARACTER {
            printf("unexpected character: '%c(%d)'\n", *in.tok, *in.tok);
            goto std;
        }
        END { return YYMAXFILL == in.lim - in.tok; }
    */
}

#endif // CALC_SCANNER_H_
