#include "scanner.def.h"
#include "parser.h"
#include "scan.h"
#include "readmem.h"

#define TOKEN_SEPARATOR 10000

int numerizer_start(scanstate *ss) {
    scanner_enter(ss);
//std:
    /*!re2c
        SEPARATOR = [ \r\n\t\f\-]+;
        END       = "\x00";
        //CHARS     = [^ \r\n\t\f\-\x00]+; // not a separator
        CHARS     = [^]; // not a separator
        NUMBER     = [0-9\.]+;

        NUMBER { return TOKEN_NUMBER; }

        'and' { return TOKEN_AND; }
        'and a' { return TOKEN_AND_A; }

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
        'firsts' { return TOKEN_FIRSTS; }
        'second' { return TOKEN_SECOND; }
        'seconds' { return TOKEN_SECONDS; }
        'third' { return TOKEN_THIRD; }
        'thirds' { return TOKEN_THIRDS; }
        'fourth' { return TOKEN_FOURTH; }
        'fourths' { return TOKEN_FOURTHS; }
        'fifth' { return TOKEN_FIFTH; }
        'fifths' { return TOKEN_FIFTHS; }
        'sixth' { return TOKEN_SIXTH; }
        'sixths' { return TOKEN_SIXTHS; }
        'seventh' { return TOKEN_SEVENTH; }
        'sevenths' { return TOKEN_SEVENTHS; }
        'eighth' { return TOKEN_EIGHTH; }
        'eighths' { return TOKEN_EIGHTHS; }
        'nineth' { return TOKEN_NINTH; }
        'nineths' { return TOKEN_NINTHS; }
        'ninth' { return TOKEN_NINTH; }
        'ninths' { return TOKEN_NINTHS; }

        'tenth' { return TOKEN_TENTH; }
        'tenths' { return TOKEN_TENTHS; }
        'eleventh' { return TOKEN_ELEVENTH; }
        'elevenths' { return TOKEN_ELEVENTHS; }
        'twelfth' { return TOKEN_TWELFTH; }
        'twelfths' { return TOKEN_TWELFTHS; }
        'thirteenth' { return TOKEN_THIRTEENTH; }
        'thirteenths' { return TOKEN_THIRTEENTHS; }
        'fourteenth' { return TOKEN_FOURTEENTH; }
        'fourteenths' { return TOKEN_FOURTEENTHS; }
        'fifteenth' { return TOKEN_FIFTEENTH; }
        'fifteenths' { return TOKEN_FIFTEENTHS; }
        'sixteenth' { return TOKEN_SIXTEENTH; }
        'sixteenths' { return TOKEN_SIXTEENTHS; }
        'seventeenth' { return TOKEN_SEVENTEENTH; }
        'seventeenths' { return TOKEN_SEVENTEENTHS; }
        'eighteenth' { return TOKEN_EIGHTEENTH; }
        'eighteenths' { return TOKEN_EIGHTEENTHS; }
        'nineteenth' { return TOKEN_NINETEENTH; }
        'nineteenths' { return TOKEN_NINETEENTHS; }

        'twentieth' { return TOKEN_TWENTIETH; }
        'twentieths' { return TOKEN_TWENTIETHS; }
        'thirtieth' { return TOKEN_THIRTIETH; }
        'thirtieths' { return TOKEN_THIRTIETHS; }
        'fourtieth' { return TOKEN_FOURTIETH; }
        'fourtieths' { return TOKEN_FOURTIETHS; }
        'fiftieth' { return TOKEN_FIFTIETH; }
        'fiftieths' { return TOKEN_FIFTIETHS; }
        'sixtieth' { return TOKEN_SIXTIETH; }
        'sixtieths' { return TOKEN_SIXTIETHS; }
        'seventieth' { return TOKEN_SEVENTIETH; }
        'seventieths' { return TOKEN_SEVENTIETHS; }
        'eightieth' { return TOKEN_EIGHTIETH; }
        'eightieths' { return TOKEN_EIGHTIETHS; }
        'ninetieth' { return TOKEN_NINETIETH; }
        'ninetieths' { return TOKEN_NINETIETHS; }

        'hundredth' { return TOKEN_HUNDREDTH; }
        'hundredths' { return TOKEN_HUNDREDTHS; }
        'thousandth' { return TOKEN_THOUSANDTH; }
        'thousandths' { return TOKEN_THOUSANDTHS; }
        'millionth' { return TOKEN_MILLIONTH; }
        'millionths' { return TOKEN_MILLIONTHS; }
        'billionth' { return TOKEN_BILLIONTH; }
        'billionths' { return TOKEN_BILLIONTHS; }
        'trillionth' { return TOKEN_TRILLIONTH; }
        'trillionths' { return TOKEN_TRILLIONTHS; }

        'quarter' { return TOKEN_QUARTER; }
        'quarters' { return TOKEN_QUARTERS; }

        'half' { return TOKEN_HALF; }
        'halves' { return TOKEN_HALVES; }

        //SEPARATOR { goto std; }
        SEPARATOR { return TOKEN_SEPARATOR; }

        END { return 0; }

        CHARS { return TOKEN_CHARACTERS; }
    */
}

/*
scanstate* numerizer_attach(scanstate *ss)
{
	if(ss) {
		ss->state = numerizer_start;
		ss->line = 1;
	}

	return ss;
}
*/
