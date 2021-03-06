/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
/************ Begin %include sections from the grammar ************************/
#line 7 "parser.yy"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "scanner.def.h"
#include "sds.h"
#include "num-fmt.h"

#define maxi(a, b) (a > b ? a : b)
#define mini(a, b) (a < b ? a : b)
#line 40 "parser.c"
#include "parser.h"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
#if INTERFACE
#define TOKEN_CHARACTERS                      1
#define TOKEN_AND_A                           2
#define TOKEN_QUARTER                         3
#define TOKEN_QUARTERS                        4
#define TOKEN_HALF                            5
#define TOKEN_HALVES                          6
#define TOKEN_ZERO                            7
#define TOKEN_TRILLIONTH                      8
#define TOKEN_NUMBER                          9
#define TOKEN_TRILLION                       10
#define TOKEN_BILLIONTH                      11
#define TOKEN_BILLION                        12
#define TOKEN_MILLIONTH                      13
#define TOKEN_MILLION                        14
#define TOKEN_THOUSANDTH                     15
#define TOKEN_THOUSAND                       16
#define TOKEN_AND                            17
#define TOKEN_HUNDREDTH                      18
#define TOKEN_HUNDRED                        19
#define TOKEN_ONE                            20
#define TOKEN_TWO                            21
#define TOKEN_THREE                          22
#define TOKEN_FOUR                           23
#define TOKEN_FIVE                           24
#define TOKEN_SIX                            25
#define TOKEN_SEVEN                          26
#define TOKEN_EIGHT                          27
#define TOKEN_NINE                           28
#define TOKEN_TEN                            29
#define TOKEN_ELEVEN                         30
#define TOKEN_TWELVE                         31
#define TOKEN_THIRTEEN                       32
#define TOKEN_FOURTEEN                       33
#define TOKEN_FIFTEEN                        34
#define TOKEN_SIXTEEN                        35
#define TOKEN_SEVENTEEN                      36
#define TOKEN_EIGHTEEN                       37
#define TOKEN_NINETEEN                       38
#define TOKEN_TWENTY                         39
#define TOKEN_THIRTY                         40
#define TOKEN_FORTY                          41
#define TOKEN_FIFTY                          42
#define TOKEN_SIXTY                          43
#define TOKEN_SEVENTY                        44
#define TOKEN_EIGHTY                         45
#define TOKEN_NINETY                         46
#define TOKEN_FIRST                          47
#define TOKEN_SECOND                         48
#define TOKEN_THIRD                          49
#define TOKEN_FOURTH                         50
#define TOKEN_FIFTH                          51
#define TOKEN_SIXTH                          52
#define TOKEN_SEVENTH                        53
#define TOKEN_EIGHTH                         54
#define TOKEN_NINTH                          55
#define TOKEN_TENTH                          56
#define TOKEN_ELEVENTH                       57
#define TOKEN_TWELFTH                        58
#define TOKEN_THIRTEENTH                     59
#define TOKEN_FOURTEENTH                     60
#define TOKEN_FIFTEENTH                      61
#define TOKEN_SIXTEENTH                      62
#define TOKEN_SEVENTEENTH                    63
#define TOKEN_EIGHTEENTH                     64
#define TOKEN_NINETEENTH                     65
#define TOKEN_TWENTIETH                      66
#define TOKEN_THIRTIETH                      67
#define TOKEN_FOURTIETH                      68
#define TOKEN_FIFTIETH                       69
#define TOKEN_SIXTIETH                       70
#define TOKEN_SEVENTIETH                     71
#define TOKEN_EIGHTIETH                      72
#define TOKEN_NINETIETH                      73
#endif
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    ParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_MIN_REDUCE      Maximum value for reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 110
#define YYACTIONTYPE unsigned short int
#if INTERFACE
#define ParseTOKENTYPE  YYSTYPE 
#endif
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#if INTERFACE
#define ParseARG_SDECL  ParserState *state ;
#define ParseARG_PDECL , ParserState *state 
#define ParseARG_FETCH  ParserState *state  = yypParser->state 
#define ParseARG_STORE yypParser->state  = state 
#endif
#define YYNSTATE             25
#define YYNRULE              142
#define YY_MAX_SHIFT         24
#define YY_MIN_SHIFTREDUCE   151
#define YY_MAX_SHIFTREDUCE   292
#define YY_MIN_REDUCE        293
#define YY_MAX_REDUCE        434
#define YY_ERROR_ACTION      435
#define YY_ACCEPT_ACTION     436
#define YY_NO_ACTION         437
/************* End control #defines *******************************************/

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if:
**    (1)  The yy_shift_ofst[S]+X value is out of range, or
**    (2)  yy_lookahead[yy_shift_ofst[S]+X] is not equal to X, or
**    (3)  yy_shift_ofst[S] equal YY_SHIFT_USE_DFLT.
** (Implementation note: YY_SHIFT_USE_DFLT is chosen so that
** YY_SHIFT_USE_DFLT+X will be out of range for all possible lookaheads X.
** Hence only tests (1) and (2) need to be evaluated.)
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (741)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   292,  199,  205,  292,  213,  225,  158,  164,   11,  170,
 /*    10 */   176,  182,  188,  194,  200,  206,    7,  214,  226,  231,
 /*    20 */   232,  233,  234,  235,  236,  237,  238,  239,  240,  241,
 /*    30 */   242,  243,  244,  245,  246,  247,  248,  249,  250,  251,
 /*    40 */   252,  253,  254,  255,  256,  257,  258,  259,  260,  261,
 /*    50 */   262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
 /*    60 */   272,  273,  274,  275,  276,  277,  278,  279,  280,  281,
 /*    70 */   282,  283,  284,  291,  215,  287,  428,  227,    1,  158,
 /*    80 */   164,   11,  170,  176,  182,  188,  194,  200,  206,    7,
 /*    90 */   214,  226,  231,  232,  233,  234,  235,  236,  237,  238,
 /*   100 */   239,  240,  241,  242,  243,  244,  245,  246,  247,  248,
 /*   110 */   249,  250,  251,  252,  253,  254,  255,  256,  257,  258,
 /*   120 */   259,  260,  261,  262,  263,  264,  265,  266,  267,  268,
 /*   130 */   269,  270,  271,  272,  273,  274,  275,  276,  277,  278,
 /*   140 */   279,  280,  281,  282,  283,  284,   12,  427,  176,  182,
 /*   150 */   188,  194,  200,  206,    7,  214,  226,  231,  232,  233,
 /*   160 */   234,  235,  236,  237,  238,  239,  240,  241,  242,  243,
 /*   170 */   244,  245,  246,  247,  248,  249,  250,  251,  252,  253,
 /*   180 */   254,  255,  256,  257,  258,  259,  260,  261,  262,  263,
 /*   190 */   264,  265,  266,  267,  268,  269,  270,  271,  272,  273,
 /*   200 */   274,  275,  276,  277,  278,  279,  280,  281,  282,  283,
 /*   210 */   284,   13,  162,  295,  168,  188,  194,  200,  206,    7,
 /*   220 */   214,  226,  231,  232,  233,  234,  235,  236,  237,  238,
 /*   230 */   239,  240,  241,  242,  243,  244,  245,  246,  247,  248,
 /*   240 */   249,  250,  251,  252,  253,  254,  255,  256,  257,  258,
 /*   250 */   259,  260,  261,  262,  263,  264,  265,  266,  267,  268,
 /*   260 */   269,  270,  271,  272,  273,  274,  275,  276,  277,  278,
 /*   270 */   279,  280,  281,  282,  283,  284,   14,   22,  295,  153,
 /*   280 */   295,  155,  200,  206,    7,  214,  226,  231,  232,  233,
 /*   290 */   234,  235,  236,  237,  238,  239,  240,  241,  242,  243,
 /*   300 */   244,  245,  246,  247,  248,  249,  250,  251,  252,  253,
 /*   310 */   254,  255,  256,  257,  258,  259,  260,  261,  262,  263,
 /*   320 */   264,  265,  266,  267,  268,  269,  270,  271,  272,  273,
 /*   330 */   274,  275,  276,  277,  278,  279,  280,  281,  282,  283,
 /*   340 */   284,   20,  187,  193,  199,  205,  295,  213,  225,    7,
 /*   350 */   214,  226,  231,  232,  233,  234,  235,  236,  237,  238,
 /*   360 */   239,  240,  241,  242,  243,  244,  245,  246,  247,  248,
 /*   370 */   249,  250,  251,  252,  253,  254,  255,  256,  257,  258,
 /*   380 */   259,  260,  261,  262,  263,  264,  265,  266,  267,  268,
 /*   390 */   269,  270,  271,  272,  273,  274,  275,  276,  277,  278,
 /*   400 */   279,  280,  281,  282,  283,  284,    8,  174,  180,  231,
 /*   410 */   232,  233,  234,  235,  236,  237,  238,  239,  240,  241,
 /*   420 */   242,  243,  244,  245,  246,  247,  248,  249,  250,  251,
 /*   430 */   252,  253,  254,  255,  256,  257,  258,  259,  260,  261,
 /*   440 */   262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
 /*   450 */   272,  273,  274,  275,  276,  277,  278,  279,  280,  281,
 /*   460 */   282,  283,  284,  231,  232,  233,  234,  235,  236,  237,
 /*   470 */   238,  239,  240,  241,  242,  243,  244,  245,  246,  247,
 /*   480 */   248,  249,  250,  251,  252,  253,  254,  255,  256,  257,
 /*   490 */   258,  259,  260,  261,  262,  263,  264,  265,  266,  267,
 /*   500 */   268,  269,  270,  271,  272,  273,  274,  275,  276,  277,
 /*   510 */   278,  279,  280,  281,  282,  283,  284,  436,   24,   23,
 /*   520 */    10,  151,    1,   15,  157,    2,  161,  160,   16,    3,
 /*   530 */   173,  172,   17,    4,  185,  184,   18,    5,  197,  196,
 /*   540 */    19,    6,  211,  209,   21,    9,  218,  216,  217,  230,
 /*   550 */   229,  289,  295,   10,  151,  295,   15,  157,    2,  161,
 /*   560 */   160,   16,    3,  173,  172,   17,    4,  185,  184,   18,
 /*   570 */     5,  197,  196,   19,    6,  211,  209,   21,    9,  218,
 /*   580 */   216,  217,  230,  229,  159,  295,  165,    3,  173,  172,
 /*   590 */    17,    4,  185,  184,   18,    5,  197,  196,   19,    6,
 /*   600 */   211,  209,   21,    9,  218,  216,  217,  230,  229,  171,
 /*   610 */   295,  177,    4,  185,  184,   18,    5,  197,  196,   19,
 /*   620 */     6,  211,  209,   21,    9,  218,  216,  217,  230,  229,
 /*   630 */   231,  232,  233,  234,  235,  236,  237,  238,  239,  183,
 /*   640 */   295,  189,    5,  197,  196,   19,    6,  211,  209,   21,
 /*   650 */     9,  218,  216,  217,  230,  229,  295,  258,  259,  260,
 /*   660 */   261,  262,  263,  264,  265,  266,  195,  295,  201,    6,
 /*   670 */   211,  209,   21,    9,  218,  216,  217,  230,  229,  163,
 /*   680 */   295,  169,  175,  181,  187,  193,  199,  205,  295,  213,
 /*   690 */   225,  208,  295,  220,    9,  218,  216,  217,  230,  229,
 /*   700 */   210,  295,  222,    9,  218,  216,  217,  230,  229,  207,
 /*   710 */   295,  219,    9,  218,  216,  217,  230,  229,  175,  181,
 /*   720 */   187,  193,  199,  205,  295,  213,  225,  186,  192,  295,
 /*   730 */   198,  204,  295,  295,  213,  225,  212,  224,  152,  295,
 /*   740 */   154,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,   15,   16,    1,   18,   19,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    20 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*    30 */    31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
 /*    40 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*    50 */    51,   52,   53,   54,   55,   56,   57,   58,   59,   60,
 /*    60 */    61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
 /*    70 */    71,   72,   73,    1,  104,   77,    0,  107,   80,    7,
 /*    80 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*    90 */    18,   19,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   100 */    28,   29,   30,   31,   32,   33,   34,   35,   36,   37,
 /*   110 */    38,   39,   40,   41,   42,   43,   44,   45,   46,   47,
 /*   120 */    48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
 /*   130 */    58,   59,   60,   61,   62,   63,   64,   65,   66,   67,
 /*   140 */    68,   69,   70,   71,   72,   73,    9,    0,   11,   12,
 /*   150 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   160 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   170 */    33,   34,   35,   36,   37,   38,   39,   40,   41,   42,
 /*   180 */    43,   44,   45,   46,   47,   48,   49,   50,   51,   52,
 /*   190 */    53,   54,   55,   56,   57,   58,   59,   60,   61,   62,
 /*   200 */    63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*   210 */    73,    9,    8,  109,   10,   13,   14,   15,   16,   17,
 /*   220 */    18,   19,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   230 */    28,   29,   30,   31,   32,   33,   34,   35,   36,   37,
 /*   240 */    38,   39,   40,   41,   42,   43,   44,   45,   46,   47,
 /*   250 */    48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
 /*   260 */    58,   59,   60,   61,   62,   63,   64,   65,   66,   67,
 /*   270 */    68,   69,   70,   71,   72,   73,    9,    2,  109,    4,
 /*   280 */   109,    6,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   290 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   300 */    33,   34,   35,   36,   37,   38,   39,   40,   41,   42,
 /*   310 */    43,   44,   45,   46,   47,   48,   49,   50,   51,   52,
 /*   320 */    53,   54,   55,   56,   57,   58,   59,   60,   61,   62,
 /*   330 */    63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*   340 */    73,    9,   13,   14,   15,   16,  109,   18,   19,   17,
 /*   350 */    18,   19,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   360 */    28,   29,   30,   31,   32,   33,   34,   35,   36,   37,
 /*   370 */    38,   39,   40,   41,   42,   43,   44,   45,   46,   47,
 /*   380 */    48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
 /*   390 */    58,   59,   60,   61,   62,   63,   64,   65,   66,   67,
 /*   400 */    68,   69,   70,   71,   72,   73,   17,   11,   12,   20,
 /*   410 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   420 */    31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
 /*   430 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*   440 */    51,   52,   53,   54,   55,   56,   57,   58,   59,   60,
 /*   450 */    61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
 /*   460 */    71,   72,   73,   20,   21,   22,   23,   24,   25,   26,
 /*   470 */    27,   28,   29,   30,   31,   32,   33,   34,   35,   36,
 /*   480 */    37,   38,   39,   40,   41,   42,   43,   44,   45,   46,
 /*   490 */    47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
 /*   500 */    57,   58,   59,   60,   61,   62,   63,   64,   65,   66,
 /*   510 */    67,   68,   69,   70,   71,   72,   73,   75,   76,   77,
 /*   520 */    78,   79,   80,   81,   82,   83,   84,   85,   86,   87,
 /*   530 */    88,   89,   90,   91,   92,   93,   94,   95,   96,   97,
 /*   540 */    98,   99,  100,  101,  102,  103,  104,  105,  106,  107,
 /*   550 */   108,   76,  109,   78,   79,  109,   81,   82,   83,   84,
 /*   560 */    85,   86,   87,   88,   89,   90,   91,   92,   93,   94,
 /*   570 */    95,   96,   97,   98,   99,  100,  101,  102,  103,  104,
 /*   580 */   105,  106,  107,  108,   84,  109,   86,   87,   88,   89,
 /*   590 */    90,   91,   92,   93,   94,   95,   96,   97,   98,   99,
 /*   600 */   100,  101,  102,  103,  104,  105,  106,  107,  108,   88,
 /*   610 */   109,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*   620 */    99,  100,  101,  102,  103,  104,  105,  106,  107,  108,
 /*   630 */    20,   21,   22,   23,   24,   25,   26,   27,   28,   92,
 /*   640 */   109,   94,   95,   96,   97,   98,   99,  100,  101,  102,
 /*   650 */   103,  104,  105,  106,  107,  108,  109,   47,   48,   49,
 /*   660 */    50,   51,   52,   53,   54,   55,   96,  109,   98,   99,
 /*   670 */   100,  101,  102,  103,  104,  105,  106,  107,  108,    8,
 /*   680 */   109,   10,   11,   12,   13,   14,   15,   16,  109,   18,
 /*   690 */    19,  100,  109,  102,  103,  104,  105,  106,  107,  108,
 /*   700 */   100,  109,  102,  103,  104,  105,  106,  107,  108,  100,
 /*   710 */   109,  102,  103,  104,  105,  106,  107,  108,   11,   12,
 /*   720 */    13,   14,   15,   16,  109,   18,   19,   13,   14,  109,
 /*   730 */    15,   16,  109,  109,   18,   19,   18,   19,    3,  109,
 /*   740 */     5,
};
#define YY_SHIFT_USE_DFLT (741)
#define YY_SHIFT_COUNT    (24)
#define YY_SHIFT_MIN      (-14)
#define YY_SHIFT_MAX      (735)
static const short yy_shift_ofst[] = {
 /*     0 */    -1,   72,  137,  202,  267,  332,  389,  443,  443,  610,
 /*    10 */     2,  671,  707,  329,  -14,  275,  204,  396,  714,  715,
 /*    20 */   716,  718,  735,   76,  147,
};
#define YY_REDUCE_USE_DFLT (-31)
#define YY_REDUCE_COUNT (10)
#define YY_REDUCE_MIN   (-30)
#define YY_REDUCE_MAX   (609)
static const short yy_reduce_ofst[] = {
 /*     0 */   442,  475,  500,  521,  547,  570,  591,  600,  609,  -30,
 /*    10 */    -2,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   435,  432,  308,  320,  332,  344,  363,  435,  435,  370,
 /*    10 */   430,  435,  435,  435,  435,  298,  309,  321,  333,  345,
 /*    20 */   435,  365,  435,  435,  435,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "CHARACTERS",    "AND_A",         "QUARTER",     
  "QUARTERS",      "HALF",          "HALVES",        "ZERO",        
  "TRILLIONTH",    "NUMBER",        "TRILLION",      "BILLIONTH",   
  "BILLION",       "MILLIONTH",     "MILLION",       "THOUSANDTH",  
  "THOUSAND",      "AND",           "HUNDREDTH",     "HUNDRED",     
  "ONE",           "TWO",           "THREE",         "FOUR",        
  "FIVE",          "SIX",           "SEVEN",         "EIGHT",       
  "NINE",          "TEN",           "ELEVEN",        "TWELVE",      
  "THIRTEEN",      "FOURTEEN",      "FIFTEEN",       "SIXTEEN",     
  "SEVENTEEN",     "EIGHTEEN",      "NINETEEN",      "TWENTY",      
  "THIRTY",        "FORTY",         "FIFTY",         "SIXTY",       
  "SEVENTY",       "EIGHTY",        "NINETY",        "FIRST",       
  "SECOND",        "THIRD",         "FOURTH",        "FIFTH",       
  "SIXTH",         "SEVENTH",       "EIGHTH",        "NINTH",       
  "TENTH",         "ELEVENTH",      "TWELFTH",       "THIRTEENTH",  
  "FOURTEENTH",    "FIFTEENTH",     "SIXTEENTH",     "SEVENTEENTH", 
  "EIGHTEENTH",    "NINETEENTH",    "TWENTIETH",     "THIRTIETH",   
  "FOURTIETH",     "FIFTIETH",      "SIXTIETH",      "SEVENTIETH",  
  "EIGHTIETH",     "NINETIETH",     "error",         "program",     
  "num_ident",     "ident_num",     "number",        "final_number",
  "identifiers",   "one_to_999999999999999",  "first_to_999999999999999th",  "trillions",   
  "first_to_999999999999th",  "trillionths",   "one_to_999999999999",  "billions",    
  "first_to_999999999th",  "billionths",    "one_to_999999999",  "millions",    
  "first_to_999999th",  "millionths",    "one_to_999999",  "thousands",   
  "first_to_999th",  "thousandths",   "one_to_999",    "hundreds",    
  "first_to_99th",  "hundredths",    "one_to_99",     "tens",        
  "first_to_9th",  "tenth",         "tenth_to_19th",  "one_to_9",    
  "ten_to_19",   
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "number ::= final_number",
 /*   1 */ "final_number ::= one_to_999999999999999 AND_A QUARTER",
 /*   2 */ "final_number ::= one_to_999999999999999 QUARTERS",
 /*   3 */ "final_number ::= one_to_999999999999999 AND_A HALF",
 /*   4 */ "final_number ::= one_to_999999999999999 HALVES",
 /*   5 */ "final_number ::= one_to_999999999999999",
 /*   6 */ "final_number ::= first_to_999999999999999th",
 /*   7 */ "final_number ::= ZERO",
 /*   8 */ "first_to_999999999999999th ::= trillions first_to_999999999999th",
 /*   9 */ "first_to_999999999999999th ::= trillionths",
 /*  10 */ "first_to_999999999999999th ::= first_to_999999999999th",
 /*  11 */ "trillionths ::= one_to_999999999999 TRILLIONTH",
 /*  12 */ "trillionths ::= NUMBER TRILLIONTH",
 /*  13 */ "trillionths ::= TRILLIONTH",
 /*  14 */ "one_to_999999999999999 ::= trillions one_to_999999999999",
 /*  15 */ "one_to_999999999999999 ::= trillions",
 /*  16 */ "one_to_999999999999999 ::= one_to_999999999999",
 /*  17 */ "trillions ::= one_to_999999999999 TRILLION",
 /*  18 */ "trillions ::= NUMBER TRILLION",
 /*  19 */ "trillions ::= TRILLION",
 /*  20 */ "first_to_999999999999th ::= billions first_to_999999999th",
 /*  21 */ "first_to_999999999999th ::= billionths",
 /*  22 */ "first_to_999999999999th ::= first_to_999999999th",
 /*  23 */ "billionths ::= one_to_999999999 BILLIONTH",
 /*  24 */ "billionths ::= NUMBER BILLIONTH",
 /*  25 */ "billionths ::= BILLIONTH",
 /*  26 */ "one_to_999999999999 ::= billions one_to_999999999",
 /*  27 */ "one_to_999999999999 ::= billions",
 /*  28 */ "one_to_999999999999 ::= one_to_999999999",
 /*  29 */ "billions ::= one_to_999999999 BILLION",
 /*  30 */ "billions ::= NUMBER BILLION",
 /*  31 */ "billions ::= BILLION",
 /*  32 */ "first_to_999999999th ::= millions first_to_999999th",
 /*  33 */ "first_to_999999999th ::= millionths",
 /*  34 */ "first_to_999999999th ::= first_to_999999th",
 /*  35 */ "millionths ::= one_to_999999 MILLIONTH",
 /*  36 */ "millionths ::= NUMBER MILLIONTH",
 /*  37 */ "millionths ::= MILLIONTH",
 /*  38 */ "one_to_999999999 ::= millions one_to_999999",
 /*  39 */ "one_to_999999999 ::= millions",
 /*  40 */ "one_to_999999999 ::= one_to_999999",
 /*  41 */ "millions ::= one_to_999999 MILLION",
 /*  42 */ "millions ::= NUMBER MILLION",
 /*  43 */ "millions ::= MILLION",
 /*  44 */ "first_to_999999th ::= thousands first_to_999th",
 /*  45 */ "first_to_999999th ::= thousandths",
 /*  46 */ "first_to_999999th ::= first_to_999th",
 /*  47 */ "thousandths ::= one_to_999 THOUSANDTH",
 /*  48 */ "thousandths ::= NUMBER THOUSANDTH",
 /*  49 */ "thousandths ::= THOUSANDTH",
 /*  50 */ "one_to_999999 ::= thousands one_to_999",
 /*  51 */ "one_to_999999 ::= thousands",
 /*  52 */ "one_to_999999 ::= one_to_999",
 /*  53 */ "thousands ::= one_to_999 THOUSAND",
 /*  54 */ "thousands ::= NUMBER THOUSAND",
 /*  55 */ "thousands ::= THOUSAND",
 /*  56 */ "first_to_999th ::= hundreds AND first_to_99th",
 /*  57 */ "first_to_999th ::= hundreds first_to_99th",
 /*  58 */ "first_to_999th ::= hundredths",
 /*  59 */ "first_to_999th ::= AND first_to_99th",
 /*  60 */ "first_to_999th ::= first_to_99th",
 /*  61 */ "hundredths ::= one_to_99 HUNDREDTH",
 /*  62 */ "hundredths ::= NUMBER HUNDREDTH",
 /*  63 */ "hundredths ::= HUNDREDTH",
 /*  64 */ "first_to_99th ::= tens first_to_9th",
 /*  65 */ "first_to_99th ::= tenth",
 /*  66 */ "first_to_99th ::= tenth_to_19th",
 /*  67 */ "first_to_99th ::= first_to_9th",
 /*  68 */ "one_to_999 ::= hundreds AND one_to_99",
 /*  69 */ "one_to_999 ::= hundreds one_to_99",
 /*  70 */ "one_to_999 ::= hundreds",
 /*  71 */ "one_to_999 ::= AND one_to_99",
 /*  72 */ "one_to_999 ::= one_to_99",
 /*  73 */ "hundreds ::= one_to_99 HUNDRED",
 /*  74 */ "hundreds ::= NUMBER HUNDRED",
 /*  75 */ "hundreds ::= HUNDRED",
 /*  76 */ "one_to_99 ::= tens one_to_9",
 /*  77 */ "one_to_99 ::= tens",
 /*  78 */ "one_to_99 ::= ten_to_19",
 /*  79 */ "one_to_99 ::= one_to_9",
 /*  80 */ "one_to_9 ::= ONE",
 /*  81 */ "one_to_9 ::= TWO",
 /*  82 */ "one_to_9 ::= THREE",
 /*  83 */ "one_to_9 ::= FOUR",
 /*  84 */ "one_to_9 ::= FIVE",
 /*  85 */ "one_to_9 ::= SIX",
 /*  86 */ "one_to_9 ::= SEVEN",
 /*  87 */ "one_to_9 ::= EIGHT",
 /*  88 */ "one_to_9 ::= NINE",
 /*  89 */ "ten_to_19 ::= TEN",
 /*  90 */ "ten_to_19 ::= ELEVEN",
 /*  91 */ "ten_to_19 ::= TWELVE",
 /*  92 */ "ten_to_19 ::= THIRTEEN",
 /*  93 */ "ten_to_19 ::= FOURTEEN",
 /*  94 */ "ten_to_19 ::= FIFTEEN",
 /*  95 */ "ten_to_19 ::= SIXTEEN",
 /*  96 */ "ten_to_19 ::= SEVENTEEN",
 /*  97 */ "ten_to_19 ::= EIGHTEEN",
 /*  98 */ "ten_to_19 ::= NINETEEN",
 /*  99 */ "tens ::= TWENTY",
 /* 100 */ "tens ::= THIRTY",
 /* 101 */ "tens ::= FORTY",
 /* 102 */ "tens ::= FIFTY",
 /* 103 */ "tens ::= SIXTY",
 /* 104 */ "tens ::= SEVENTY",
 /* 105 */ "tens ::= EIGHTY",
 /* 106 */ "tens ::= NINETY",
 /* 107 */ "first_to_9th ::= FIRST",
 /* 108 */ "first_to_9th ::= SECOND",
 /* 109 */ "first_to_9th ::= THIRD",
 /* 110 */ "first_to_9th ::= FOURTH",
 /* 111 */ "first_to_9th ::= FIFTH",
 /* 112 */ "first_to_9th ::= SIXTH",
 /* 113 */ "first_to_9th ::= SEVENTH",
 /* 114 */ "first_to_9th ::= EIGHTH",
 /* 115 */ "first_to_9th ::= NINTH",
 /* 116 */ "tenth_to_19th ::= TENTH",
 /* 117 */ "tenth_to_19th ::= ELEVENTH",
 /* 118 */ "tenth_to_19th ::= TWELFTH",
 /* 119 */ "tenth_to_19th ::= THIRTEENTH",
 /* 120 */ "tenth_to_19th ::= FOURTEENTH",
 /* 121 */ "tenth_to_19th ::= FIFTEENTH",
 /* 122 */ "tenth_to_19th ::= SIXTEENTH",
 /* 123 */ "tenth_to_19th ::= SEVENTEENTH",
 /* 124 */ "tenth_to_19th ::= EIGHTEENTH",
 /* 125 */ "tenth_to_19th ::= NINETEENTH",
 /* 126 */ "tenth ::= TWENTIETH",
 /* 127 */ "tenth ::= THIRTIETH",
 /* 128 */ "tenth ::= FOURTIETH",
 /* 129 */ "tenth ::= FIFTIETH",
 /* 130 */ "tenth ::= SIXTIETH",
 /* 131 */ "tenth ::= SEVENTIETH",
 /* 132 */ "tenth ::= EIGHTIETH",
 /* 133 */ "tenth ::= NINETIETH",
 /* 134 */ "program ::= num_ident",
 /* 135 */ "program ::= ident_num",
 /* 136 */ "num_ident ::= number ident_num",
 /* 137 */ "num_ident ::= number",
 /* 138 */ "ident_num ::= identifiers num_ident",
 /* 139 */ "ident_num ::= identifiers",
 /* 140 */ "identifiers ::= identifiers CHARACTERS",
 /* 141 */ "identifiers ::= CHARACTERS",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to ParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( pParser ){
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yytos = NULL;
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    if( yyGrowStack(pParser) ){
      pParser->yystack = &pParser->yystk0;
      pParser->yystksz = 1;
    }
#endif
#ifndef YYNOERRORRECOVERY
    pParser->yyerrcnt = -1;
#endif
    pParser->yytos = pParser->yystack;
    pParser->yystack[0].stateno = 0;
    pParser->yystack[0].major = 0;
  }
  return pParser;
}

/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
#ifndef YYPARSEFREENEVERNULL
  if( pParser==0 ) return;
#endif
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ParseReset(
  void *p                    /* The parser to be reset */
){
  yyParser *pParser = (yyParser*)p;
#ifndef YYPARSEFREENEVERNULL
  if( pParser==0 ) return;
#endif
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif

  if( pParser ){
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yytos = NULL;
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    /*if( yyGrowStack(pParser) ){*/
      /*pParser->yystack = &pParser->yystk0;*/
      /*pParser->yystksz = 1;*/
    /*}*/
#endif
#ifndef YYNOERRORRECOVERY
    pParser->yyerrcnt = -1;
#endif
    pParser->yytos = pParser->yystack;
    pParser->yystack[0].stateno = 0;
    pParser->yystack[0].major = 0;
  }
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static unsigned int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yytos->stateno;
 
  if( stateno>=YY_MIN_REDUCE ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
  do{
    i = yy_shift_ofst[stateno];
    assert( iLookAhead!=YYNOCODE );
    i += iLookAhead;
    if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   ParseARG_FETCH;
   yypParser->yytos--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%sShift '%s', go to state %d\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%sShift '%s'\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major]);
    }
  }
}
#else
# define yyTraceShift(X,Y)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  ParseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH] ){
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState);
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 78, 1 },
  { 79, 3 },
  { 79, 2 },
  { 79, 3 },
  { 79, 2 },
  { 79, 1 },
  { 79, 1 },
  { 79, 1 },
  { 82, 2 },
  { 82, 1 },
  { 82, 1 },
  { 85, 2 },
  { 85, 2 },
  { 85, 1 },
  { 81, 2 },
  { 81, 1 },
  { 81, 1 },
  { 83, 2 },
  { 83, 2 },
  { 83, 1 },
  { 84, 2 },
  { 84, 1 },
  { 84, 1 },
  { 89, 2 },
  { 89, 2 },
  { 89, 1 },
  { 86, 2 },
  { 86, 1 },
  { 86, 1 },
  { 87, 2 },
  { 87, 2 },
  { 87, 1 },
  { 88, 2 },
  { 88, 1 },
  { 88, 1 },
  { 93, 2 },
  { 93, 2 },
  { 93, 1 },
  { 90, 2 },
  { 90, 1 },
  { 90, 1 },
  { 91, 2 },
  { 91, 2 },
  { 91, 1 },
  { 92, 2 },
  { 92, 1 },
  { 92, 1 },
  { 97, 2 },
  { 97, 2 },
  { 97, 1 },
  { 94, 2 },
  { 94, 1 },
  { 94, 1 },
  { 95, 2 },
  { 95, 2 },
  { 95, 1 },
  { 96, 3 },
  { 96, 2 },
  { 96, 1 },
  { 96, 2 },
  { 96, 1 },
  { 101, 2 },
  { 101, 2 },
  { 101, 1 },
  { 100, 2 },
  { 100, 1 },
  { 100, 1 },
  { 100, 1 },
  { 98, 3 },
  { 98, 2 },
  { 98, 1 },
  { 98, 2 },
  { 98, 1 },
  { 99, 2 },
  { 99, 2 },
  { 99, 1 },
  { 102, 2 },
  { 102, 1 },
  { 102, 1 },
  { 102, 1 },
  { 107, 1 },
  { 107, 1 },
  { 107, 1 },
  { 107, 1 },
  { 107, 1 },
  { 107, 1 },
  { 107, 1 },
  { 107, 1 },
  { 107, 1 },
  { 108, 1 },
  { 108, 1 },
  { 108, 1 },
  { 108, 1 },
  { 108, 1 },
  { 108, 1 },
  { 108, 1 },
  { 108, 1 },
  { 108, 1 },
  { 108, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 75, 1 },
  { 75, 1 },
  { 76, 2 },
  { 76, 1 },
  { 77, 2 },
  { 77, 1 },
  { 80, 2 },
  { 80, 1 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno        /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    fprintf(yyTraceFILE, "%sReduce [%s], go to state %d.\n", yyTracePrompt,
      yyRuleName[yyruleno], yymsp[-yysize].stateno);
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfo[yyruleno].nrhs==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH-1] ){
      yyStackOverflow(yypParser);
      return;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        return;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* number ::= final_number */
#line 44 "parser.yy"
{
    insertYYSTYPE(&state->yystypeList, yymsp[0].minor.yy0);
}
#line 1332 "parser.c"
        break;
      case 1: /* final_number ::= one_to_999999999999999 AND_A QUARTER */
#line 57 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.25; }
#line 1337 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 2: /* final_number ::= one_to_999999999999999 QUARTERS */
#line 58 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 4.0; }
#line 1343 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 3: /* final_number ::= one_to_999999999999999 AND_A HALF */
#line 59 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.5; }
#line 1349 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 4: /* final_number ::= one_to_999999999999999 HALVES */
#line 60 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 2.0; }
#line 1355 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 5: /* final_number ::= one_to_999999999999999 */
      case 15: /* one_to_999999999999999 ::= trillions */ yytestcase(yyruleno==15);
      case 16: /* one_to_999999999999999 ::= one_to_999999999999 */ yytestcase(yyruleno==16);
      case 27: /* one_to_999999999999 ::= billions */ yytestcase(yyruleno==27);
      case 28: /* one_to_999999999999 ::= one_to_999999999 */ yytestcase(yyruleno==28);
      case 39: /* one_to_999999999 ::= millions */ yytestcase(yyruleno==39);
      case 40: /* one_to_999999999 ::= one_to_999999 */ yytestcase(yyruleno==40);
      case 51: /* one_to_999999 ::= thousands */ yytestcase(yyruleno==51);
      case 52: /* one_to_999999 ::= one_to_999 */ yytestcase(yyruleno==52);
      case 70: /* one_to_999 ::= hundreds */ yytestcase(yyruleno==70);
      case 72: /* one_to_999 ::= one_to_99 */ yytestcase(yyruleno==72);
      case 77: /* one_to_99 ::= tens */ yytestcase(yyruleno==77);
      case 78: /* one_to_99 ::= ten_to_19 */ yytestcase(yyruleno==78);
      case 79: /* one_to_99 ::= one_to_9 */ yytestcase(yyruleno==79);
#line 61 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1374 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 6: /* final_number ::= first_to_999999999999999th */
      case 9: /* first_to_999999999999999th ::= trillionths */ yytestcase(yyruleno==9);
      case 10: /* first_to_999999999999999th ::= first_to_999999999999th */ yytestcase(yyruleno==10);
      case 21: /* first_to_999999999999th ::= billionths */ yytestcase(yyruleno==21);
      case 22: /* first_to_999999999999th ::= first_to_999999999th */ yytestcase(yyruleno==22);
      case 33: /* first_to_999999999th ::= millionths */ yytestcase(yyruleno==33);
      case 34: /* first_to_999999999th ::= first_to_999999th */ yytestcase(yyruleno==34);
      case 45: /* first_to_999999th ::= thousandths */ yytestcase(yyruleno==45);
      case 46: /* first_to_999999th ::= first_to_999th */ yytestcase(yyruleno==46);
      case 58: /* first_to_999th ::= hundredths */ yytestcase(yyruleno==58);
      case 60: /* first_to_999th ::= first_to_99th */ yytestcase(yyruleno==60);
      case 65: /* first_to_99th ::= tenth */ yytestcase(yyruleno==65);
      case 66: /* first_to_99th ::= tenth_to_19th */ yytestcase(yyruleno==66);
      case 67: /* first_to_99th ::= first_to_9th */ yytestcase(yyruleno==67);
#line 62 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1393 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 7: /* final_number ::= ZERO */
#line 73 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 0.0; }
#line 1399 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 8: /* first_to_999999999999999th ::= trillions first_to_999999999999th */
      case 20: /* first_to_999999999999th ::= billions first_to_999999999th */ yytestcase(yyruleno==20);
      case 32: /* first_to_999999999th ::= millions first_to_999999th */ yytestcase(yyruleno==32);
      case 44: /* first_to_999999th ::= thousands first_to_999th */ yytestcase(yyruleno==44);
      case 57: /* first_to_999th ::= hundreds first_to_99th */ yytestcase(yyruleno==57);
      case 64: /* first_to_99th ::= tens first_to_9th */ yytestcase(yyruleno==64);
#line 96 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1410 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 11: /* trillionths ::= one_to_999999999999 TRILLIONTH */
      case 12: /* trillionths ::= NUMBER TRILLIONTH */ yytestcase(yyruleno==12);
#line 100 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1417 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 13: /* trillionths ::= TRILLIONTH */
#line 102 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1423 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 14: /* one_to_999999999999999 ::= trillions one_to_999999999999 */
      case 26: /* one_to_999999999999 ::= billions one_to_999999999 */ yytestcase(yyruleno==26);
      case 38: /* one_to_999999999 ::= millions one_to_999999 */ yytestcase(yyruleno==38);
      case 50: /* one_to_999999 ::= thousands one_to_999 */ yytestcase(yyruleno==50);
      case 69: /* one_to_999 ::= hundreds one_to_99 */ yytestcase(yyruleno==69);
      case 76: /* one_to_99 ::= tens one_to_9 */ yytestcase(yyruleno==76);
#line 112 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1434 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 17: /* trillions ::= one_to_999999999999 TRILLION */
      case 18: /* trillions ::= NUMBER TRILLION */ yytestcase(yyruleno==18);
#line 116 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; }
#line 1441 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 19: /* trillions ::= TRILLION */
#line 118 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000000.0; }
#line 1447 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 23: /* billionths ::= one_to_999999999 BILLIONTH */
      case 24: /* billionths ::= NUMBER BILLIONTH */ yytestcase(yyruleno==24);
#line 128 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1454 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 25: /* billionths ::= BILLIONTH */
#line 130 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1460 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 29: /* billions ::= one_to_999999999 BILLION */
      case 30: /* billions ::= NUMBER BILLION */ yytestcase(yyruleno==30);
#line 144 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; }
#line 1467 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 31: /* billions ::= BILLION */
#line 146 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000.0; }
#line 1473 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 35: /* millionths ::= one_to_999999 MILLIONTH */
      case 36: /* millionths ::= NUMBER MILLIONTH */ yytestcase(yyruleno==36);
#line 156 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; yylhsminor.yy0.suffix = TH; }
#line 1480 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 37: /* millionths ::= MILLIONTH */
#line 158 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000.0; yylhsminor.yy0.suffix = TH; }
#line 1486 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 41: /* millions ::= one_to_999999 MILLION */
      case 42: /* millions ::= NUMBER MILLION */ yytestcase(yyruleno==42);
#line 172 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; }
#line 1493 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 43: /* millions ::= MILLION */
#line 174 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000.0; }
#line 1499 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 47: /* thousandths ::= one_to_999 THOUSANDTH */
      case 48: /* thousandths ::= NUMBER THOUSANDTH */ yytestcase(yyruleno==48);
#line 184 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; yylhsminor.yy0.suffix = TH; }
#line 1506 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 49: /* thousandths ::= THOUSANDTH */
#line 186 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000.0; yylhsminor.yy0.suffix = TH; }
#line 1512 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 53: /* thousands ::= one_to_999 THOUSAND */
      case 54: /* thousands ::= NUMBER THOUSAND */ yytestcase(yyruleno==54);
#line 200 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; }
#line 1519 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 55: /* thousands ::= THOUSAND */
#line 202 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000.0; }
#line 1525 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 56: /* first_to_999th ::= hundreds AND first_to_99th */
#line 208 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1531 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 59: /* first_to_999th ::= AND first_to_99th */
#line 211 "parser.yy"
{ yymsp[-1].minor.yy0.spos = yymsp[0].minor.yy0.spos; yymsp[-1].minor.yy0.epos = yymsp[0].minor.yy0.epos; yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; yymsp[-1].minor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1537 "parser.c"
        break;
      case 61: /* hundredths ::= one_to_99 HUNDREDTH */
      case 62: /* hundredths ::= NUMBER HUNDREDTH */ yytestcase(yyruleno==62);
#line 214 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; yylhsminor.yy0.suffix = TH; }
#line 1543 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 63: /* hundredths ::= HUNDREDTH */
#line 216 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 100.0; yylhsminor.yy0.suffix = TH; }
#line 1549 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 68: /* one_to_999 ::= hundreds AND one_to_99 */
#line 231 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1555 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 71: /* one_to_999 ::= AND one_to_99 */
#line 234 "parser.yy"
{ yymsp[-1].minor.yy0.spos = yymsp[0].minor.yy0.spos; yymsp[-1].minor.yy0.epos = yymsp[0].minor.yy0.epos; yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1561 "parser.c"
        break;
      case 73: /* hundreds ::= one_to_99 HUNDRED */
      case 74: /* hundreds ::= NUMBER HUNDRED */ yytestcase(yyruleno==74);
#line 237 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; }
#line 1567 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 75: /* hundreds ::= HUNDRED */
#line 239 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 100.0; }
#line 1573 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 80: /* one_to_9 ::= ONE */
#line 250 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1.0; }
#line 1579 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 81: /* one_to_9 ::= TWO */
#line 251 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 2.0; }
#line 1585 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 82: /* one_to_9 ::= THREE */
#line 252 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 3.0; }
#line 1591 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 83: /* one_to_9 ::= FOUR */
#line 253 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 4.0; }
#line 1597 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 84: /* one_to_9 ::= FIVE */
#line 254 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 5.0; }
#line 1603 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 85: /* one_to_9 ::= SIX */
#line 255 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 6.0; }
#line 1609 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 86: /* one_to_9 ::= SEVEN */
#line 256 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 7.0; }
#line 1615 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 87: /* one_to_9 ::= EIGHT */
#line 257 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 8.0; }
#line 1621 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 88: /* one_to_9 ::= NINE */
#line 258 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 9.0; }
#line 1627 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 89: /* ten_to_19 ::= TEN */
#line 260 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 10.0; }
#line 1633 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 90: /* ten_to_19 ::= ELEVEN */
#line 261 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 11.0; }
#line 1639 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 91: /* ten_to_19 ::= TWELVE */
#line 262 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 12.0; }
#line 1645 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 92: /* ten_to_19 ::= THIRTEEN */
#line 263 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 13.0; }
#line 1651 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 93: /* ten_to_19 ::= FOURTEEN */
#line 264 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 14.0; }
#line 1657 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 94: /* ten_to_19 ::= FIFTEEN */
#line 265 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 15.0; }
#line 1663 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 95: /* ten_to_19 ::= SIXTEEN */
#line 266 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 16.0; }
#line 1669 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 96: /* ten_to_19 ::= SEVENTEEN */
#line 267 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 17.0; }
#line 1675 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 97: /* ten_to_19 ::= EIGHTEEN */
#line 268 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 18.0; }
#line 1681 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 98: /* ten_to_19 ::= NINETEEN */
#line 269 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 19.0; }
#line 1687 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 99: /* tens ::= TWENTY */
#line 271 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 20.0; }
#line 1693 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 100: /* tens ::= THIRTY */
#line 272 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 30.0; }
#line 1699 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 101: /* tens ::= FORTY */
#line 273 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 40.0; }
#line 1705 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 102: /* tens ::= FIFTY */
#line 274 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 50.0; }
#line 1711 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 103: /* tens ::= SIXTY */
#line 275 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 60.0; }
#line 1717 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 104: /* tens ::= SEVENTY */
#line 276 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 70.0; }
#line 1723 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 105: /* tens ::= EIGHTY */
#line 277 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 80.0; }
#line 1729 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 106: /* tens ::= NINETY */
#line 278 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 90.0; }
#line 1735 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 107: /* first_to_9th ::= FIRST */
#line 280 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1.0; yylhsminor.yy0.suffix = ST; }
#line 1741 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 108: /* first_to_9th ::= SECOND */
#line 281 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 2.0; yylhsminor.yy0.suffix = ND; }
#line 1747 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 109: /* first_to_9th ::= THIRD */
#line 282 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 3.0; yylhsminor.yy0.suffix = RD; }
#line 1753 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 110: /* first_to_9th ::= FOURTH */
#line 283 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 4.0; yylhsminor.yy0.suffix = TH; }
#line 1759 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 111: /* first_to_9th ::= FIFTH */
#line 284 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 5.0; yylhsminor.yy0.suffix = TH; }
#line 1765 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 112: /* first_to_9th ::= SIXTH */
#line 285 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 6.0; yylhsminor.yy0.suffix = TH; }
#line 1771 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 113: /* first_to_9th ::= SEVENTH */
#line 286 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 7.0; yylhsminor.yy0.suffix = TH; }
#line 1777 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 114: /* first_to_9th ::= EIGHTH */
#line 287 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 8.0; yylhsminor.yy0.suffix = TH; }
#line 1783 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 115: /* first_to_9th ::= NINTH */
#line 288 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 9.0; yylhsminor.yy0.suffix = TH; }
#line 1789 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 116: /* tenth_to_19th ::= TENTH */
#line 290 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 10.0; yylhsminor.yy0.suffix = TH; }
#line 1795 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 117: /* tenth_to_19th ::= ELEVENTH */
#line 291 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 11.0; yylhsminor.yy0.suffix = TH; }
#line 1801 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 118: /* tenth_to_19th ::= TWELFTH */
#line 292 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 12.0; yylhsminor.yy0.suffix = TH; }
#line 1807 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 119: /* tenth_to_19th ::= THIRTEENTH */
#line 293 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 13.0; yylhsminor.yy0.suffix = TH; }
#line 1813 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 120: /* tenth_to_19th ::= FOURTEENTH */
#line 294 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 14.0; yylhsminor.yy0.suffix = TH; }
#line 1819 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 121: /* tenth_to_19th ::= FIFTEENTH */
#line 295 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 15.0; yylhsminor.yy0.suffix = TH; }
#line 1825 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 122: /* tenth_to_19th ::= SIXTEENTH */
#line 296 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 16.0; yylhsminor.yy0.suffix = TH; }
#line 1831 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 123: /* tenth_to_19th ::= SEVENTEENTH */
#line 297 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 17.0; yylhsminor.yy0.suffix = TH; }
#line 1837 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 124: /* tenth_to_19th ::= EIGHTEENTH */
#line 298 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 18.0; yylhsminor.yy0.suffix = TH; }
#line 1843 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 125: /* tenth_to_19th ::= NINETEENTH */
#line 299 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 19.0; yylhsminor.yy0.suffix = TH; }
#line 1849 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 126: /* tenth ::= TWENTIETH */
#line 301 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 20.0; yylhsminor.yy0.suffix = TH; }
#line 1855 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 127: /* tenth ::= THIRTIETH */
#line 302 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 30.0; yylhsminor.yy0.suffix = TH; }
#line 1861 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 128: /* tenth ::= FOURTIETH */
#line 303 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 40.0; yylhsminor.yy0.suffix = TH; }
#line 1867 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 129: /* tenth ::= FIFTIETH */
#line 304 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 50.0; yylhsminor.yy0.suffix = TH; }
#line 1873 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 130: /* tenth ::= SIXTIETH */
#line 305 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 60.0; yylhsminor.yy0.suffix = TH; }
#line 1879 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 131: /* tenth ::= SEVENTIETH */
#line 306 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 70.0; yylhsminor.yy0.suffix = TH; }
#line 1885 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 132: /* tenth ::= EIGHTIETH */
#line 307 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 80.0; yylhsminor.yy0.suffix = TH; }
#line 1891 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 133: /* tenth ::= NINETIETH */
#line 308 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 90.0; yylhsminor.yy0.suffix = TH; }
#line 1897 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      default:
      /* (134) program ::= num_ident */ yytestcase(yyruleno==134);
      /* (135) program ::= ident_num */ yytestcase(yyruleno==135);
      /* (136) num_ident ::= number ident_num */ yytestcase(yyruleno==136);
      /* (137) num_ident ::= number */ yytestcase(yyruleno==137);
      /* (138) ident_num ::= identifiers num_ident */ yytestcase(yyruleno==138);
      /* (139) ident_num ::= identifiers */ yytestcase(yyruleno==139);
      /* (140) identifiers ::= identifiers CHARACTERS */ yytestcase(yyruleno==140);
      /* (141) identifiers ::= CHARACTERS */ yytestcase(yyruleno==141);
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact <= YY_MAX_SHIFTREDUCE ){
    if( yyact>YY_MAX_SHIFT ){
      yyact += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
    }
    yymsp -= yysize-1;
    yypParser->yytos = yymsp;
    yymsp->stateno = (YYACTIONTYPE)yyact;
    yymsp->major = (YYCODETYPE)yygoto;
    yyTraceShift(yypParser, yyact);
  }else{
    assert( yyact == YY_ACCEPT_ACTION );
    yypParser->yytos -= yysize;
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
#line 27 "parser.yy"

    state->error = PARSE_FAILURE;
#if print_errors
    fprintf(stderr,"Giving up.  Parser is hopelessly lost...\n");
#endif
#line 1955 "parser.c"
/************ End %parse_failure code *****************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  ParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 20 "parser.yy"

    state->error = SYNTAX_ERROR;
#if print_errors
    fprintf(stderr, "Syntax error\n");
#endif
#line 1978 "parser.c"
/************ End %syntax_error code ******************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
/*********** End %parse_accept code *******************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  unsigned int yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  yypParser = (yyParser*)yyp;
  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput '%s'\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      yymajor = YYNOCODE;
    }else if( yyact <= YY_MAX_REDUCE ){
      yy_reduce(yypParser,yyact-YY_MIN_REDUCE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && yymx != YYERRORSYMBOL
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}
