#ifndef CALC_SCANNER_H_
#define CALC_SCANNER_H_

#include <fstream>
#include "scanner.def.h"
#include "parser.h"

class Scanner {
    private:
        // iostream sucks. very slow.
        std::istream *ifs;

        // buffer memory
        char* m_buffer;

        // current position
        char* m_cursor;
        char* m_limit;
        char* m_token;
        char* m_marker;
        int m_buffer_size;

    public:

        Scanner(std::istream *ifs_, int init_size=1024)
            : m_buffer(0),
              m_cursor(0),
              m_limit(0),
              m_token(0),
              m_marker(0),
              m_buffer_size(init_size)
        {
            m_buffer = new char[m_buffer_size];
            m_cursor = m_limit = m_token = m_marker = m_buffer;
            ifs = ifs_;
        }

        ~Scanner() {
            delete [] m_buffer;
        }

        bool fill(int n) {
            /*printf("fill: '%d'\n", n);*/
            /*printf("m_token: '%c'\n", *m_token);*/

            // is eof?
            if (ifs->eof()) {
                if ((m_limit - m_cursor) <= 0) {
                    return false;
                }
            }

            int restSize = (m_limit - m_token);
            if ((restSize + n) >= m_buffer_size) {
                // extend buffer
                m_buffer_size *= 2;
                char* newBuffer = new char[m_buffer_size];
                for (int i=0; i<restSize; ++i) { // memcpy
                    *(newBuffer+i) = *(m_token+i);
                }
                m_cursor = newBuffer + (m_cursor - m_token);
                m_token = newBuffer;
                m_limit = newBuffer + restSize;

                delete[] m_buffer;
                m_buffer = newBuffer;
            } else {
                // move remained data to head.
                for (int i=0; i<restSize; ++i) {
                    //memmove(m_buffer, m_token, (restSize)*sizeof(char));
                    *(m_buffer+i) = *(m_token+i);
                }
                m_cursor = m_buffer + (m_cursor - m_token);
                m_token = m_buffer;
                m_limit = m_buffer+restSize;
            }

            // fill to buffer
            int read_size = (m_buffer_size - restSize);
            ifs->read(m_limit, read_size);
            m_limit += ifs->gcount();
            // printf("m_limit: '%ld'\n", ifs->gcount());

            return true;
        }

        int scan(YYSTYPE& yylval) {
std:
            m_token = m_cursor;

            /*!re2c
                re2c:define:YYCTYPE = "char";
                re2c:define:YYCURSOR = m_cursor;
                re2c:define:YYMARKER = m_marker;
                re2c:define:YYLIMIT = m_limit;
                re2c:define:YYFILL:naked = 1;
                re2c:define:YYFILL@len = #;
                re2c:define:YYFILL = "if (!fill(#)) { return 0; }";
                re2c:yyfill:enable = 1;
                re2c:indent:top = 2;
                re2c:indent:string="    ";

                WS                     = [ \r\n\t\f];
                ANY_CHARACTER          = [^];

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
                    printf("unexpected character: '%c(%d)'\n", *m_token, *m_token);
                    goto std;
                }
            */
        }
};

#endif // CALC_SCANNER_H_
