#ifndef NUMERIZER_SCANNER_H_
#define NUMERIZER_SCANNER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.def.h"
#include "parser.h"

#include "libre2c/scan.h"
#include "libre2c/readmem.h"

int numerizer_start(scanstate *ss) {
    scanner_enter(ss);
std:
    /*!re2c
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
            printf("BAD INPUT: <<%ld %s>>\n", scan_token_length(ss), scan_token_start(ss));
            return 0;
        }
        END { return 0; }
    */
}

scanstate* numerizer_attach(scanstate *ss)
{
	if(ss) {
		ss->state = numerizer_start;
		ss->line = 1;
	}

	return ss;
}

#endif // NUMERIZER_SCANNER_H_
