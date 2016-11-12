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
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
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
#define YYNOCODE 142
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE  YYSTYPE 
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserState *state ;
#define ParseARG_PDECL , ParserState *state 
#define ParseARG_FETCH  ParserState *state  = yypParser->state 
#define ParseARG_STORE yypParser->state  = state 
#define YYNSTATE             24
#define YYNRULE              184
#define YY_MAX_SHIFT         23
#define YY_MIN_SHIFTREDUCE   193
#define YY_MAX_SHIFTREDUCE   376
#define YY_MIN_REDUCE        377
#define YY_MAX_REDUCE        560
#define YY_ERROR_ACTION      561
#define YY_ACCEPT_ACTION     562
#define YY_NO_ACTION         563
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
#define YY_ACTTAB_COUNT (1001)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   376,  206,  207,  194,  215,    1,  202,  210,  211,   11,
 /*    10 */   217,  225,  226,  232,  240,  241,  247,  255,  256,  262,
 /*    20 */     7,  272,  273,  285,  290,  291,  292,  293,  294,  295,
 /*    30 */   296,  297,  298,  299,  300,  301,  302,  303,  304,  305,
 /*    40 */   306,  307,  308,  309,  310,  311,  312,  313,  314,  315,
 /*    50 */   316,  317,  318,  319,  320,  321,  322,  323,  324,  325,
 /*    60 */   326,  327,  328,  329,  330,  331,  332,  333,  334,  335,
 /*    70 */   336,  337,  338,  339,  340,  341,  342,  343,  344,  345,
 /*    80 */   346,  347,  348,  349,  350,  351,  352,  353,  354,  355,
 /*    90 */   356,  357,  358,  359,  360,  361,  362,  363,  364,  365,
 /*   100 */   366,  367,  368,  369,  370,  375,  221,  222,  230,  376,
 /*   110 */   377,  202,  210,  211,   11,  217,  225,  226,  232,  240,
 /*   120 */   241,  247,  255,  256,  262,    7,  272,  273,  285,  290,
 /*   130 */   291,  292,  293,  294,  295,  296,  297,  298,  299,  300,
 /*   140 */   301,  302,  303,  304,  305,  306,  307,  308,  309,  310,
 /*   150 */   311,  312,  313,  314,  315,  316,  317,  318,  319,  320,
 /*   160 */   321,  322,  323,  324,  325,  326,  327,  328,  329,  330,
 /*   170 */   331,  332,  333,  334,  335,  336,  337,  338,  339,  340,
 /*   180 */   341,  342,  343,  344,  345,  346,  347,  348,  349,  350,
 /*   190 */   351,  352,  353,  354,  355,  356,  357,  358,  359,  360,
 /*   200 */   361,  362,  363,  364,  365,  366,  367,  368,  369,  370,
 /*   210 */    12,  379,  225,  226,  232,  240,  241,  247,  255,  256,
 /*   220 */   262,    7,  272,  273,  285,  290,  291,  292,  293,  294,
 /*   230 */   295,  296,  297,  298,  299,  300,  301,  302,  303,  304,
 /*   240 */   305,  306,  307,  308,  309,  310,  311,  312,  313,  314,
 /*   250 */   315,  316,  317,  318,  319,  320,  321,  322,  323,  324,
 /*   260 */   325,  326,  327,  328,  329,  330,  331,  332,  333,  334,
 /*   270 */   335,  336,  337,  338,  339,  340,  341,  342,  343,  344,
 /*   280 */   345,  346,  347,  348,  349,  350,  351,  352,  353,  354,
 /*   290 */   355,  356,  357,  358,  359,  360,  361,  362,  363,  364,
 /*   300 */   365,  366,  367,  368,  369,  370,   13,  236,  237,  245,
 /*   310 */   379,  240,  241,  247,  255,  256,  262,    7,  272,  273,
 /*   320 */   285,  290,  291,  292,  293,  294,  295,  296,  297,  298,
 /*   330 */   299,  300,  301,  302,  303,  304,  305,  306,  307,  308,
 /*   340 */   309,  310,  311,  312,  313,  314,  315,  316,  317,  318,
 /*   350 */   319,  320,  321,  322,  323,  324,  325,  326,  327,  328,
 /*   360 */   329,  330,  331,  332,  333,  334,  335,  336,  337,  338,
 /*   370 */   339,  340,  341,  342,  343,  344,  345,  346,  347,  348,
 /*   380 */   349,  350,  351,  352,  353,  354,  355,  356,  357,  358,
 /*   390 */   359,  360,  361,  362,  363,  364,  365,  366,  367,  368,
 /*   400 */   369,  370,   14,  253,  254,  261,  379,  270,  271,  284,
 /*   410 */   255,  256,  262,    7,  272,  273,  285,  290,  291,  292,
 /*   420 */   293,  294,  295,  296,  297,  298,  299,  300,  301,  302,
 /*   430 */   303,  304,  305,  306,  307,  308,  309,  310,  311,  312,
 /*   440 */   313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
 /*   450 */   323,  324,  325,  326,  327,  328,  329,  330,  331,  332,
 /*   460 */   333,  334,  335,  336,  337,  338,  339,  340,  341,  342,
 /*   470 */   343,  344,  345,  346,  347,  348,  349,  350,  351,  352,
 /*   480 */   353,  354,  355,  356,  357,  358,  359,  360,  361,  362,
 /*   490 */   363,  364,  365,  366,  367,  368,  369,  370,   19,  238,
 /*   500 */   239,  246,  253,  254,  261,  379,  270,  271,  284,    7,
 /*   510 */   272,  273,  285,  290,  291,  292,  293,  294,  295,  296,
 /*   520 */   297,  298,  299,  300,  301,  302,  303,  304,  305,  306,
 /*   530 */   307,  308,  309,  310,  311,  312,  313,  314,  315,  316,
 /*   540 */   317,  318,  319,  320,  321,  322,  323,  324,  325,  326,
 /*   550 */   327,  328,  329,  330,  331,  332,  333,  334,  335,  336,
 /*   560 */   337,  338,  339,  340,  341,  342,  343,  344,  345,  346,
 /*   570 */   347,  348,  349,  350,  351,  352,  353,  354,  355,  356,
 /*   580 */   357,  358,  359,  360,  361,  362,  363,  364,  365,  366,
 /*   590 */   367,  368,  369,  370,    8,  251,  252,  260,  290,  291,
 /*   600 */   292,  293,  294,  295,  296,  297,  298,  299,  300,  301,
 /*   610 */   302,  303,  304,  305,  306,  307,  308,  309,  310,  311,
 /*   620 */   312,  313,  314,  315,  316,  317,  318,  319,  320,  321,
 /*   630 */   322,  323,  324,  325,  326,  327,  328,  329,  330,  331,
 /*   640 */   332,  333,  334,  335,  336,  337,  338,  339,  340,  341,
 /*   650 */   342,  343,  344,  345,  346,  347,  348,  349,  350,  351,
 /*   660 */   352,  353,  354,  355,  356,  357,  358,  359,  360,  361,
 /*   670 */   362,  363,  364,  365,  366,  367,  368,  369,  370,  290,
 /*   680 */   291,  292,  293,  294,  295,  296,  297,  298,  299,  300,
 /*   690 */   301,  302,  303,  304,  305,  306,  307,  308,  309,  310,
 /*   700 */   311,  312,  313,  314,  315,  316,  317,  318,  319,  320,
 /*   710 */   321,  322,  323,  324,  325,  326,  327,  328,  329,  330,
 /*   720 */   331,  332,  333,  334,  335,  336,  337,  338,  339,  340,
 /*   730 */   341,  342,  343,  344,  345,  346,  347,  348,  349,  350,
 /*   740 */   351,  352,  353,  354,  355,  356,  357,  358,  359,  360,
 /*   750 */   361,  362,  363,  364,  365,  366,  367,  368,  369,  370,
 /*   760 */   562,   23,   23,   23,   10,    1,   21,  201,    2,  205,
 /*   770 */   204,   15,    3,  220,  219,   16,    4,  235,  234,   17,
 /*   780 */     5,  250,  249,   18,    6,  267,  265,   20,    9,  277,
 /*   790 */   275,  276,  289,  288,  373,  196,   10,  198,   21,  201,
 /*   800 */     2,  205,  204,   15,    3,  220,  219,   16,    4,  235,
 /*   810 */   234,   17,    5,  250,  249,   18,    6,  267,  265,   20,
 /*   820 */     9,  277,  275,  276,  289,  288,  290,  291,  292,  293,
 /*   830 */   294,  295,  296,  297,  298,  233,  379,  242,    5,  250,
 /*   840 */   249,   18,    6,  267,  265,   20,    9,  277,  275,  276,
 /*   850 */   289,  288,  379,  317,  318,  319,  320,  321,  322,  323,
 /*   860 */   324,  325,  326,  327,  328,  329,  330,  331,  332,  333,
 /*   870 */   334,  203,  379,  212,    3,  220,  219,   16,    4,  235,
 /*   880 */   234,   17,    5,  250,  249,   18,    6,  267,  265,   20,
 /*   890 */     9,  277,  275,  276,  289,  288,  218,  379,  227,    4,
 /*   900 */   235,  234,   17,    5,  250,  249,   18,    6,  267,  265,
 /*   910 */    20,    9,  277,  275,  276,  289,  288,  208,  209,  379,
 /*   920 */   216,  223,  224,  231,  238,  239,  246,  253,  254,  261,
 /*   930 */   379,  270,  271,  284,  248,  379,  257,    6,  267,  265,
 /*   940 */    20,    9,  277,  275,  276,  289,  288,  223,  224,  231,
 /*   950 */   238,  239,  246,  253,  254,  261,  379,  270,  271,  284,
 /*   960 */   264,  379,  279,    9,  277,  275,  276,  289,  288,  379,
 /*   970 */   266,  379,  281,    9,  277,  275,  276,  289,  288,  263,
 /*   980 */   379,  278,    9,  277,  275,  276,  289,  288,  270,  271,
 /*   990 */   284,  268,  269,  283,   22,  379,  197,  274,  199,  379,
 /*  1000 */   286,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    8,    9,  110,   11,  112,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    20 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*    30 */    31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
 /*    40 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*    50 */    51,   52,   53,   54,   55,   56,   57,   58,   59,   60,
 /*    60 */    61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
 /*    70 */    71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
 /*    80 */    81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
 /*    90 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   100 */   101,  102,  103,  104,  105,    1,   12,   13,   14,    1,
 /*   110 */     0,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   120 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   130 */    26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
 /*   140 */    36,   37,   38,   39,   40,   41,   42,   43,   44,   45,
 /*   150 */    46,   47,   48,   49,   50,   51,   52,   53,   54,   55,
 /*   160 */    56,   57,   58,   59,   60,   61,   62,   63,   64,   65,
 /*   170 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   180 */    76,   77,   78,   79,   80,   81,   82,   83,   84,   85,
 /*   190 */    86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
 /*   200 */    96,   97,   98,   99,  100,  101,  102,  103,  104,  105,
 /*   210 */    10,  141,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   220 */    20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   230 */    30,   31,   32,   33,   34,   35,   36,   37,   38,   39,
 /*   240 */    40,   41,   42,   43,   44,   45,   46,   47,   48,   49,
 /*   250 */    50,   51,   52,   53,   54,   55,   56,   57,   58,   59,
 /*   260 */    60,   61,   62,   63,   64,   65,   66,   67,   68,   69,
 /*   270 */    70,   71,   72,   73,   74,   75,   76,   77,   78,   79,
 /*   280 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   89,
 /*   290 */    90,   91,   92,   93,   94,   95,   96,   97,   98,   99,
 /*   300 */   100,  101,  102,  103,  104,  105,   10,   15,   16,   17,
 /*   310 */   141,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   320 */    24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
 /*   330 */    34,   35,   36,   37,   38,   39,   40,   41,   42,   43,
 /*   340 */    44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
 /*   350 */    54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
 /*   360 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   370 */    74,   75,   76,   77,   78,   79,   80,   81,   82,   83,
 /*   380 */    84,   85,   86,   87,   88,   89,   90,   91,   92,   93,
 /*   390 */    94,   95,   96,   97,   98,   99,  100,  101,  102,  103,
 /*   400 */   104,  105,   10,   18,   19,   20,  141,   22,   23,   24,
 /*   410 */    18,   19,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   420 */    28,   29,   30,   31,   32,   33,   34,   35,   36,   37,
 /*   430 */    38,   39,   40,   41,   42,   43,   44,   45,   46,   47,
 /*   440 */    48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
 /*   450 */    58,   59,   60,   61,   62,   63,   64,   65,   66,   67,
 /*   460 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*   470 */    78,   79,   80,   81,   82,   83,   84,   85,   86,   87,
 /*   480 */    88,   89,   90,   91,   92,   93,   94,   95,   96,   97,
 /*   490 */    98,   99,  100,  101,  102,  103,  104,  105,   10,   15,
 /*   500 */    16,   17,   18,   19,   20,  141,   22,   23,   24,   21,
 /*   510 */    22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
 /*   520 */    32,   33,   34,   35,   36,   37,   38,   39,   40,   41,
 /*   530 */    42,   43,   44,   45,   46,   47,   48,   49,   50,   51,
 /*   540 */    52,   53,   54,   55,   56,   57,   58,   59,   60,   61,
 /*   550 */    62,   63,   64,   65,   66,   67,   68,   69,   70,   71,
 /*   560 */    72,   73,   74,   75,   76,   77,   78,   79,   80,   81,
 /*   570 */    82,   83,   84,   85,   86,   87,   88,   89,   90,   91,
 /*   580 */    92,   93,   94,   95,   96,   97,   98,   99,  100,  101,
 /*   590 */   102,  103,  104,  105,   21,   18,   19,   20,   25,   26,
 /*   600 */    27,   28,   29,   30,   31,   32,   33,   34,   35,   36,
 /*   610 */    37,   38,   39,   40,   41,   42,   43,   44,   45,   46,
 /*   620 */    47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
 /*   630 */    57,   58,   59,   60,   61,   62,   63,   64,   65,   66,
 /*   640 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   650 */    77,   78,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   660 */    87,   88,   89,   90,   91,   92,   93,   94,   95,   96,
 /*   670 */    97,   98,   99,  100,  101,  102,  103,  104,  105,   25,
 /*   680 */    26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
 /*   690 */    36,   37,   38,   39,   40,   41,   42,   43,   44,   45,
 /*   700 */    46,   47,   48,   49,   50,   51,   52,   53,   54,   55,
 /*   710 */    56,   57,   58,   59,   60,   61,   62,   63,   64,   65,
 /*   720 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   730 */    76,   77,   78,   79,   80,   81,   82,   83,   84,   85,
 /*   740 */    86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
 /*   750 */    96,   97,   98,   99,  100,  101,  102,  103,  104,  105,
 /*   760 */   107,  108,  109,  110,  111,  112,  113,  114,  115,  116,
 /*   770 */   117,  118,  119,  120,  121,  122,  123,  124,  125,  126,
 /*   780 */   127,  128,  129,  130,  131,  132,  133,  134,  135,  136,
 /*   790 */   137,  138,  139,  140,  109,    3,  111,    5,  113,  114,
 /*   800 */   115,  116,  117,  118,  119,  120,  121,  122,  123,  124,
 /*   810 */   125,  126,  127,  128,  129,  130,  131,  132,  133,  134,
 /*   820 */   135,  136,  137,  138,  139,  140,   25,   26,   27,   28,
 /*   830 */    29,   30,   31,   32,   33,  124,  141,  126,  127,  128,
 /*   840 */   129,  130,  131,  132,  133,  134,  135,  136,  137,  138,
 /*   850 */   139,  140,  141,   52,   53,   54,   55,   56,   57,   58,
 /*   860 */    59,   60,   61,   62,   63,   64,   65,   66,   67,   68,
 /*   870 */    69,  116,  141,  118,  119,  120,  121,  122,  123,  124,
 /*   880 */   125,  126,  127,  128,  129,  130,  131,  132,  133,  134,
 /*   890 */   135,  136,  137,  138,  139,  140,  120,  141,  122,  123,
 /*   900 */   124,  125,  126,  127,  128,  129,  130,  131,  132,  133,
 /*   910 */   134,  135,  136,  137,  138,  139,  140,    8,    9,  141,
 /*   920 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   930 */   141,   22,   23,   24,  128,  141,  130,  131,  132,  133,
 /*   940 */   134,  135,  136,  137,  138,  139,  140,   12,   13,   14,
 /*   950 */    15,   16,   17,   18,   19,   20,  141,   22,   23,   24,
 /*   960 */   132,  141,  134,  135,  136,  137,  138,  139,  140,  141,
 /*   970 */   132,  141,  134,  135,  136,  137,  138,  139,  140,  132,
 /*   980 */   141,  134,  135,  136,  137,  138,  139,  140,   22,   23,
 /*   990 */    24,   22,   23,   24,    2,  141,    4,  136,    6,  141,
 /*  1000 */   139,
};
#define YY_SHIFT_USE_DFLT (1001)
#define YY_SHIFT_COUNT    (23)
#define YY_SHIFT_MIN      (-7)
#define YY_SHIFT_MAX      (992)
static const short yy_shift_ofst[] = {
 /*     0 */    -1,  104,  200,  296,  392,  488,  573,  654,  654,  801,
 /*    10 */   108,  909,  935,  484,  385,   -7,   94,  292,  577,  966,
 /*    20 */   969,  992,  792,  110,
};
#define YY_REDUCE_USE_DFLT (-108)
#define YY_REDUCE_COUNT (10)
#define YY_REDUCE_MIN   (-107)
#define YY_REDUCE_MAX   (861)
static const short yy_reduce_ofst[] = {
 /*     0 */   653,  685,  755,  776,  711,  806,  828,  838,  847,  861,
 /*    10 */  -107,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   561,  558,  397,  412,  427,  442,  464,  561,  561,  471,
 /*    10 */   379,  561,  561,  561,  561,  398,  413,  428,  443,  561,
 /*    20 */   466,  384,  561,  561,
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
  "TRILLIONTH",    "TRILLIONTHS",   "NUMBER",        "TRILLION",    
  "BILLIONTH",     "BILLIONTHS",    "BILLION",       "MILLIONTH",   
  "MILLIONTHS",    "MILLION",       "THOUSANDTH",    "THOUSANDTHS", 
  "THOUSAND",      "AND",           "HUNDREDTH",     "HUNDREDTHS",  
  "HUNDRED",       "ONE",           "TWO",           "THREE",       
  "FOUR",          "FIVE",          "SIX",           "SEVEN",       
  "EIGHT",         "NINE",          "TEN",           "ELEVEN",      
  "TWELVE",        "THIRTEEN",      "FOURTEEN",      "FIFTEEN",     
  "SIXTEEN",       "SEVENTEEN",     "EIGHTEEN",      "NINETEEN",    
  "TWENTY",        "THIRTY",        "FORTY",         "FIFTY",       
  "SIXTY",         "SEVENTY",       "EIGHTY",        "NINETY",      
  "FIRST",         "FIRSTS",        "SECOND",        "SECONDS",     
  "THIRD",         "THIRDS",        "FOURTH",        "FOURTHS",     
  "FIFTH",         "FIFTHS",        "SIXTH",         "SIXTHS",      
  "SEVENTH",       "SEVENTHS",      "EIGHTH",        "EIGHTHS",     
  "NINTH",         "NINTHS",        "TENTH",         "TENTHS",      
  "ELEVENTH",      "ELEVENTHS",     "TWELFTH",       "TWELFTHS",    
  "THIRTEENTH",    "THIRTEENTHS",   "FOURTEENTH",    "FOURTEENTHS", 
  "FIFTEENTH",     "FIFTEENTHS",    "SIXTEENTH",     "SIXTEENTHS",  
  "SEVENTEENTH",   "SEVENTEENTHS",  "EIGHTEENTH",    "EIGHTEENTHS", 
  "NINETEENTH",    "NINETEENTHS",   "TWENTIETH",     "TWENTIETHS",  
  "THIRTIETH",     "THIRTIETHS",    "FOURTIETH",     "FOURTIETHS",  
  "FIFTIETH",      "FIFTIETHS",     "SIXTIETH",      "SIXTIETHS",   
  "SEVENTIETH",    "SEVENTIETHS",   "EIGHTIETH",     "EIGHTIETHS",  
  "NINETIETH",     "NINETIETHS",    "error",         "program",     
  "expr",          "num_ident",     "ident_num",     "final_number",
  "identifiers",   "one_to_999999999999999",  "first_to_999999999999999th",  "trillions",   
  "first_to_999999999999th",  "trillionths",   "one_to_999999999999",  "billions",    
  "first_to_999999999th",  "billionths",    "one_to_999999999",  "millions",    
  "first_to_999999th",  "millionths",    "one_to_999999",  "thousands",   
  "first_to_999th",  "thousandths",   "one_to_999",    "hundreds",    
  "first_to_99th",  "hundredths",    "one_to_99",     "tens",        
  "first_to_9th",  "tenths",        "tenth_to_19th",  "one_to_9",    
  "ten_to_19",   
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= expr",
 /*   1 */ "num_ident ::= final_number ident_num",
 /*   2 */ "num_ident ::= final_number",
 /*   3 */ "final_number ::= one_to_999999999999999 AND_A QUARTER",
 /*   4 */ "final_number ::= one_to_999999999999999 QUARTERS",
 /*   5 */ "final_number ::= one_to_999999999999999 AND_A HALF",
 /*   6 */ "final_number ::= one_to_999999999999999 HALVES",
 /*   7 */ "final_number ::= one_to_999999999999999",
 /*   8 */ "final_number ::= first_to_999999999999999th",
 /*   9 */ "final_number ::= ZERO",
 /*  10 */ "first_to_999999999999999th ::= trillions first_to_999999999999th",
 /*  11 */ "first_to_999999999999999th ::= trillionths",
 /*  12 */ "first_to_999999999999999th ::= first_to_999999999999th",
 /*  13 */ "trillionths ::= one_to_999999999999 TRILLIONTH",
 /*  14 */ "trillionths ::= one_to_999999999999 TRILLIONTHS",
 /*  15 */ "trillionths ::= NUMBER TRILLIONTH",
 /*  16 */ "trillionths ::= NUMBER TRILLIONTHS",
 /*  17 */ "trillionths ::= TRILLIONTH",
 /*  18 */ "trillionths ::= TRILLIONTHS",
 /*  19 */ "one_to_999999999999999 ::= trillions one_to_999999999999",
 /*  20 */ "one_to_999999999999999 ::= trillions",
 /*  21 */ "one_to_999999999999999 ::= one_to_999999999999",
 /*  22 */ "trillions ::= one_to_999999999999 TRILLION",
 /*  23 */ "trillions ::= NUMBER TRILLION",
 /*  24 */ "trillions ::= TRILLION",
 /*  25 */ "first_to_999999999999th ::= billions first_to_999999999th",
 /*  26 */ "first_to_999999999999th ::= billionths",
 /*  27 */ "first_to_999999999999th ::= first_to_999999999th",
 /*  28 */ "billionths ::= one_to_999999999 BILLIONTH",
 /*  29 */ "billionths ::= one_to_999999999 BILLIONTHS",
 /*  30 */ "billionths ::= NUMBER BILLIONTH",
 /*  31 */ "billionths ::= NUMBER BILLIONTHS",
 /*  32 */ "billionths ::= BILLIONTH",
 /*  33 */ "billionths ::= BILLIONTHS",
 /*  34 */ "one_to_999999999999 ::= billions one_to_999999999",
 /*  35 */ "one_to_999999999999 ::= billions",
 /*  36 */ "one_to_999999999999 ::= one_to_999999999",
 /*  37 */ "billions ::= one_to_999999999 BILLION",
 /*  38 */ "billions ::= NUMBER BILLION",
 /*  39 */ "billions ::= BILLION",
 /*  40 */ "first_to_999999999th ::= millions first_to_999999th",
 /*  41 */ "first_to_999999999th ::= millionths",
 /*  42 */ "first_to_999999999th ::= first_to_999999th",
 /*  43 */ "millionths ::= one_to_999999 MILLIONTH",
 /*  44 */ "millionths ::= one_to_999999 MILLIONTHS",
 /*  45 */ "millionths ::= NUMBER MILLIONTH",
 /*  46 */ "millionths ::= NUMBER MILLIONTHS",
 /*  47 */ "millionths ::= MILLIONTH",
 /*  48 */ "millionths ::= MILLIONTHS",
 /*  49 */ "one_to_999999999 ::= millions one_to_999999",
 /*  50 */ "one_to_999999999 ::= millions",
 /*  51 */ "one_to_999999999 ::= one_to_999999",
 /*  52 */ "millions ::= one_to_999999 MILLION",
 /*  53 */ "millions ::= NUMBER MILLION",
 /*  54 */ "millions ::= MILLION",
 /*  55 */ "first_to_999999th ::= thousands first_to_999th",
 /*  56 */ "first_to_999999th ::= thousandths",
 /*  57 */ "first_to_999999th ::= first_to_999th",
 /*  58 */ "thousandths ::= one_to_999 THOUSANDTH",
 /*  59 */ "thousandths ::= one_to_999 THOUSANDTHS",
 /*  60 */ "thousandths ::= NUMBER THOUSANDTH",
 /*  61 */ "thousandths ::= NUMBER THOUSANDTHS",
 /*  62 */ "thousandths ::= THOUSANDTH",
 /*  63 */ "thousandths ::= THOUSANDTHS",
 /*  64 */ "one_to_999999 ::= thousands one_to_999",
 /*  65 */ "one_to_999999 ::= thousands",
 /*  66 */ "one_to_999999 ::= one_to_999",
 /*  67 */ "thousands ::= one_to_999 THOUSAND",
 /*  68 */ "thousands ::= NUMBER THOUSAND",
 /*  69 */ "thousands ::= THOUSAND",
 /*  70 */ "first_to_999th ::= hundreds AND first_to_99th",
 /*  71 */ "first_to_999th ::= hundreds first_to_99th",
 /*  72 */ "first_to_999th ::= hundredths",
 /*  73 */ "first_to_999th ::= AND first_to_99th",
 /*  74 */ "first_to_999th ::= first_to_99th",
 /*  75 */ "hundredths ::= one_to_99 HUNDREDTH",
 /*  76 */ "hundredths ::= one_to_99 HUNDREDTHS",
 /*  77 */ "hundredths ::= NUMBER HUNDREDTH",
 /*  78 */ "hundredths ::= NUMBER HUNDREDTHS",
 /*  79 */ "hundredths ::= HUNDREDTH",
 /*  80 */ "hundredths ::= HUNDREDTHS",
 /*  81 */ "first_to_99th ::= tens first_to_9th",
 /*  82 */ "first_to_99th ::= tenths",
 /*  83 */ "first_to_99th ::= tenth_to_19th",
 /*  84 */ "first_to_99th ::= first_to_9th",
 /*  85 */ "one_to_999 ::= hundreds AND one_to_99",
 /*  86 */ "one_to_999 ::= hundreds one_to_99",
 /*  87 */ "one_to_999 ::= hundreds",
 /*  88 */ "one_to_999 ::= AND one_to_99",
 /*  89 */ "one_to_999 ::= one_to_99",
 /*  90 */ "hundreds ::= one_to_99 HUNDRED",
 /*  91 */ "hundreds ::= NUMBER HUNDRED",
 /*  92 */ "hundreds ::= HUNDRED",
 /*  93 */ "one_to_99 ::= tens one_to_9",
 /*  94 */ "one_to_99 ::= tens",
 /*  95 */ "one_to_99 ::= ten_to_19",
 /*  96 */ "one_to_99 ::= one_to_9",
 /*  97 */ "one_to_9 ::= ONE",
 /*  98 */ "one_to_9 ::= TWO",
 /*  99 */ "one_to_9 ::= THREE",
 /* 100 */ "one_to_9 ::= FOUR",
 /* 101 */ "one_to_9 ::= FIVE",
 /* 102 */ "one_to_9 ::= SIX",
 /* 103 */ "one_to_9 ::= SEVEN",
 /* 104 */ "one_to_9 ::= EIGHT",
 /* 105 */ "one_to_9 ::= NINE",
 /* 106 */ "ten_to_19 ::= TEN",
 /* 107 */ "ten_to_19 ::= ELEVEN",
 /* 108 */ "ten_to_19 ::= TWELVE",
 /* 109 */ "ten_to_19 ::= THIRTEEN",
 /* 110 */ "ten_to_19 ::= FOURTEEN",
 /* 111 */ "ten_to_19 ::= FIFTEEN",
 /* 112 */ "ten_to_19 ::= SIXTEEN",
 /* 113 */ "ten_to_19 ::= SEVENTEEN",
 /* 114 */ "ten_to_19 ::= EIGHTEEN",
 /* 115 */ "ten_to_19 ::= NINETEEN",
 /* 116 */ "tens ::= TWENTY",
 /* 117 */ "tens ::= THIRTY",
 /* 118 */ "tens ::= FORTY",
 /* 119 */ "tens ::= FIFTY",
 /* 120 */ "tens ::= SIXTY",
 /* 121 */ "tens ::= SEVENTY",
 /* 122 */ "tens ::= EIGHTY",
 /* 123 */ "tens ::= NINETY",
 /* 124 */ "first_to_9th ::= FIRST",
 /* 125 */ "first_to_9th ::= FIRSTS",
 /* 126 */ "first_to_9th ::= SECOND",
 /* 127 */ "first_to_9th ::= SECONDS",
 /* 128 */ "first_to_9th ::= THIRD",
 /* 129 */ "first_to_9th ::= THIRDS",
 /* 130 */ "first_to_9th ::= FOURTH",
 /* 131 */ "first_to_9th ::= FOURTHS",
 /* 132 */ "first_to_9th ::= FIFTH",
 /* 133 */ "first_to_9th ::= FIFTHS",
 /* 134 */ "first_to_9th ::= SIXTH",
 /* 135 */ "first_to_9th ::= SIXTHS",
 /* 136 */ "first_to_9th ::= SEVENTH",
 /* 137 */ "first_to_9th ::= SEVENTHS",
 /* 138 */ "first_to_9th ::= EIGHTH",
 /* 139 */ "first_to_9th ::= EIGHTHS",
 /* 140 */ "first_to_9th ::= NINTH",
 /* 141 */ "first_to_9th ::= NINTHS",
 /* 142 */ "tenth_to_19th ::= TENTH",
 /* 143 */ "tenth_to_19th ::= TENTHS",
 /* 144 */ "tenth_to_19th ::= ELEVENTH",
 /* 145 */ "tenth_to_19th ::= ELEVENTHS",
 /* 146 */ "tenth_to_19th ::= TWELFTH",
 /* 147 */ "tenth_to_19th ::= TWELFTHS",
 /* 148 */ "tenth_to_19th ::= THIRTEENTH",
 /* 149 */ "tenth_to_19th ::= THIRTEENTHS",
 /* 150 */ "tenth_to_19th ::= FOURTEENTH",
 /* 151 */ "tenth_to_19th ::= FOURTEENTHS",
 /* 152 */ "tenth_to_19th ::= FIFTEENTH",
 /* 153 */ "tenth_to_19th ::= FIFTEENTHS",
 /* 154 */ "tenth_to_19th ::= SIXTEENTH",
 /* 155 */ "tenth_to_19th ::= SIXTEENTHS",
 /* 156 */ "tenth_to_19th ::= SEVENTEENTH",
 /* 157 */ "tenth_to_19th ::= SEVENTEENTHS",
 /* 158 */ "tenth_to_19th ::= EIGHTEENTH",
 /* 159 */ "tenth_to_19th ::= EIGHTEENTHS",
 /* 160 */ "tenth_to_19th ::= NINETEENTH",
 /* 161 */ "tenth_to_19th ::= NINETEENTHS",
 /* 162 */ "tenths ::= TWENTIETH",
 /* 163 */ "tenths ::= TWENTIETHS",
 /* 164 */ "tenths ::= THIRTIETH",
 /* 165 */ "tenths ::= THIRTIETHS",
 /* 166 */ "tenths ::= FOURTIETH",
 /* 167 */ "tenths ::= FOURTIETHS",
 /* 168 */ "tenths ::= FIFTIETH",
 /* 169 */ "tenths ::= FIFTIETHS",
 /* 170 */ "tenths ::= SIXTIETH",
 /* 171 */ "tenths ::= SIXTIETHS",
 /* 172 */ "tenths ::= SEVENTIETH",
 /* 173 */ "tenths ::= SEVENTIETHS",
 /* 174 */ "tenths ::= EIGHTIETH",
 /* 175 */ "tenths ::= EIGHTIETHS",
 /* 176 */ "tenths ::= NINETIETH",
 /* 177 */ "tenths ::= NINETIETHS",
 /* 178 */ "expr ::= num_ident",
 /* 179 */ "expr ::= ident_num",
 /* 180 */ "ident_num ::= identifiers num_ident",
 /* 181 */ "ident_num ::= identifiers",
 /* 182 */ "identifiers ::= identifiers CHARACTERS",
 /* 183 */ "identifiers ::= CHARACTERS",
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
  { 107, 1 },
  { 109, 2 },
  { 109, 1 },
  { 111, 3 },
  { 111, 2 },
  { 111, 3 },
  { 111, 2 },
  { 111, 1 },
  { 111, 1 },
  { 111, 1 },
  { 114, 2 },
  { 114, 1 },
  { 114, 1 },
  { 117, 2 },
  { 117, 2 },
  { 117, 2 },
  { 117, 2 },
  { 117, 1 },
  { 117, 1 },
  { 113, 2 },
  { 113, 1 },
  { 113, 1 },
  { 115, 2 },
  { 115, 2 },
  { 115, 1 },
  { 116, 2 },
  { 116, 1 },
  { 116, 1 },
  { 121, 2 },
  { 121, 2 },
  { 121, 2 },
  { 121, 2 },
  { 121, 1 },
  { 121, 1 },
  { 118, 2 },
  { 118, 1 },
  { 118, 1 },
  { 119, 2 },
  { 119, 2 },
  { 119, 1 },
  { 120, 2 },
  { 120, 1 },
  { 120, 1 },
  { 125, 2 },
  { 125, 2 },
  { 125, 2 },
  { 125, 2 },
  { 125, 1 },
  { 125, 1 },
  { 122, 2 },
  { 122, 1 },
  { 122, 1 },
  { 123, 2 },
  { 123, 2 },
  { 123, 1 },
  { 124, 2 },
  { 124, 1 },
  { 124, 1 },
  { 129, 2 },
  { 129, 2 },
  { 129, 2 },
  { 129, 2 },
  { 129, 1 },
  { 129, 1 },
  { 126, 2 },
  { 126, 1 },
  { 126, 1 },
  { 127, 2 },
  { 127, 2 },
  { 127, 1 },
  { 128, 3 },
  { 128, 2 },
  { 128, 1 },
  { 128, 2 },
  { 128, 1 },
  { 133, 2 },
  { 133, 2 },
  { 133, 2 },
  { 133, 2 },
  { 133, 1 },
  { 133, 1 },
  { 132, 2 },
  { 132, 1 },
  { 132, 1 },
  { 132, 1 },
  { 130, 3 },
  { 130, 2 },
  { 130, 1 },
  { 130, 2 },
  { 130, 1 },
  { 131, 2 },
  { 131, 2 },
  { 131, 1 },
  { 134, 2 },
  { 134, 1 },
  { 134, 1 },
  { 134, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 140, 1 },
  { 140, 1 },
  { 140, 1 },
  { 140, 1 },
  { 140, 1 },
  { 140, 1 },
  { 140, 1 },
  { 140, 1 },
  { 140, 1 },
  { 140, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 136, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 108, 1 },
  { 108, 1 },
  { 110, 2 },
  { 110, 1 },
  { 112, 2 },
  { 112, 1 },
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
      case 0: /* program ::= expr */
#line 26 "parser.yy"
{
    /*printf("locations %d %d\n", yymsp[0].minor.yy0.spos, yymsp[0].minor.yy0.epos);*/

    /*doubleToString(&state->result, yymsp[0].minor.yy0.double_value, state->precision);*/

    /*switch (yymsp[0].minor.yy0.suffix) {*/
        /*case ST:*/
            /*state->result = sdscat(state->result, "st");*/
            /*break;*/
        /*case STS:*/
            /*state->result = sdscat(state->result, "sts");*/
            /*break;*/
        /*case ND:*/
            /*state->result = sdscat(state->result, "nd");*/
            /*break;*/
        /*case NDS:*/
            /*state->result = sdscat(state->result, "nds");*/
            /*break;*/
        /*case RD:*/
            /*state->result = sdscat(state->result, "rd");*/
            /*break;*/
        /*case RDS:*/
            /*state->result = sdscat(state->result, "rds");*/
            /*break;*/
        /*case TH:*/
            /*state->result = sdscat(state->result, "th");*/
            /*break;*/
        /*case THS:*/
            /*state->result = sdscat(state->result, "ths");*/
            /*break;*/
    /*}*/

    /*state->result = sdsRemoveFreeSpace(state->result);*/
}
#line 1385 "parser.c"
        break;
      case 1: /* num_ident ::= final_number ident_num */
#line 64 "parser.yy"
{
    insertYYSTYPE(&state->yystypeList, yymsp[-1].minor.yy0);
}
#line 1392 "parser.c"
        break;
      case 2: /* num_ident ::= final_number */
#line 68 "parser.yy"
{
    insertYYSTYPE(&state->yystypeList, yymsp[0].minor.yy0);
}
#line 1399 "parser.c"
        break;
      case 3: /* final_number ::= one_to_999999999999999 AND_A QUARTER */
#line 79 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.25; }
#line 1404 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 4: /* final_number ::= one_to_999999999999999 QUARTERS */
#line 80 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 4.0; }
#line 1410 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 5: /* final_number ::= one_to_999999999999999 AND_A HALF */
#line 81 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.5; }
#line 1416 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 6: /* final_number ::= one_to_999999999999999 HALVES */
#line 82 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 2.0; }
#line 1422 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 7: /* final_number ::= one_to_999999999999999 */
      case 20: /* one_to_999999999999999 ::= trillions */ yytestcase(yyruleno==20);
      case 21: /* one_to_999999999999999 ::= one_to_999999999999 */ yytestcase(yyruleno==21);
      case 35: /* one_to_999999999999 ::= billions */ yytestcase(yyruleno==35);
      case 36: /* one_to_999999999999 ::= one_to_999999999 */ yytestcase(yyruleno==36);
      case 50: /* one_to_999999999 ::= millions */ yytestcase(yyruleno==50);
      case 51: /* one_to_999999999 ::= one_to_999999 */ yytestcase(yyruleno==51);
      case 65: /* one_to_999999 ::= thousands */ yytestcase(yyruleno==65);
      case 66: /* one_to_999999 ::= one_to_999 */ yytestcase(yyruleno==66);
      case 87: /* one_to_999 ::= hundreds */ yytestcase(yyruleno==87);
      case 89: /* one_to_999 ::= one_to_99 */ yytestcase(yyruleno==89);
      case 94: /* one_to_99 ::= tens */ yytestcase(yyruleno==94);
      case 95: /* one_to_99 ::= ten_to_19 */ yytestcase(yyruleno==95);
      case 96: /* one_to_99 ::= one_to_9 */ yytestcase(yyruleno==96);
#line 83 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1441 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 8: /* final_number ::= first_to_999999999999999th */
      case 11: /* first_to_999999999999999th ::= trillionths */ yytestcase(yyruleno==11);
      case 12: /* first_to_999999999999999th ::= first_to_999999999999th */ yytestcase(yyruleno==12);
      case 26: /* first_to_999999999999th ::= billionths */ yytestcase(yyruleno==26);
      case 27: /* first_to_999999999999th ::= first_to_999999999th */ yytestcase(yyruleno==27);
      case 41: /* first_to_999999999th ::= millionths */ yytestcase(yyruleno==41);
      case 42: /* first_to_999999999th ::= first_to_999999th */ yytestcase(yyruleno==42);
      case 56: /* first_to_999999th ::= thousandths */ yytestcase(yyruleno==56);
      case 57: /* first_to_999999th ::= first_to_999th */ yytestcase(yyruleno==57);
      case 72: /* first_to_999th ::= hundredths */ yytestcase(yyruleno==72);
      case 74: /* first_to_999th ::= first_to_99th */ yytestcase(yyruleno==74);
      case 82: /* first_to_99th ::= tenths */ yytestcase(yyruleno==82);
      case 83: /* first_to_99th ::= tenth_to_19th */ yytestcase(yyruleno==83);
      case 84: /* first_to_99th ::= first_to_9th */ yytestcase(yyruleno==84);
#line 84 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1460 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 9: /* final_number ::= ZERO */
#line 90 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 0.0; }
#line 1466 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 10: /* first_to_999999999999999th ::= trillions first_to_999999999999th */
      case 25: /* first_to_999999999999th ::= billions first_to_999999999th */ yytestcase(yyruleno==25);
      case 40: /* first_to_999999999th ::= millions first_to_999999th */ yytestcase(yyruleno==40);
      case 55: /* first_to_999999th ::= thousands first_to_999th */ yytestcase(yyruleno==55);
      case 71: /* first_to_999th ::= hundreds first_to_99th */ yytestcase(yyruleno==71);
      case 81: /* first_to_99th ::= tens first_to_9th */ yytestcase(yyruleno==81);
#line 110 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1477 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 13: /* trillionths ::= one_to_999999999999 TRILLIONTH */
      case 15: /* trillionths ::= NUMBER TRILLIONTH */ yytestcase(yyruleno==15);
#line 114 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1484 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 14: /* trillionths ::= one_to_999999999999 TRILLIONTHS */
      case 16: /* trillionths ::= NUMBER TRILLIONTHS */ yytestcase(yyruleno==16);
#line 115 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; yylhsminor.yy0.suffix = THS; }
#line 1491 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 17: /* trillionths ::= TRILLIONTH */
#line 118 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1497 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 18: /* trillionths ::= TRILLIONTHS */
#line 119 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000000.0; yylhsminor.yy0.suffix = THS; }
#line 1503 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 19: /* one_to_999999999999999 ::= trillions one_to_999999999999 */
      case 34: /* one_to_999999999999 ::= billions one_to_999999999 */ yytestcase(yyruleno==34);
      case 49: /* one_to_999999999 ::= millions one_to_999999 */ yytestcase(yyruleno==49);
      case 64: /* one_to_999999 ::= thousands one_to_999 */ yytestcase(yyruleno==64);
      case 86: /* one_to_999 ::= hundreds one_to_99 */ yytestcase(yyruleno==86);
      case 93: /* one_to_99 ::= tens one_to_9 */ yytestcase(yyruleno==93);
#line 125 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1514 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 22: /* trillions ::= one_to_999999999999 TRILLION */
      case 23: /* trillions ::= NUMBER TRILLION */ yytestcase(yyruleno==23);
#line 129 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; }
#line 1521 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 24: /* trillions ::= TRILLION */
#line 131 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000000.0; }
#line 1527 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 28: /* billionths ::= one_to_999999999 BILLIONTH */
      case 30: /* billionths ::= NUMBER BILLIONTH */ yytestcase(yyruleno==30);
#line 141 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1534 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 29: /* billionths ::= one_to_999999999 BILLIONTHS */
      case 31: /* billionths ::= NUMBER BILLIONTHS */ yytestcase(yyruleno==31);
#line 142 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; yylhsminor.yy0.suffix = THS; }
#line 1541 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 32: /* billionths ::= BILLIONTH */
#line 145 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1547 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 33: /* billionths ::= BILLIONTHS */
#line 146 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000.0; yylhsminor.yy0.suffix = THS; }
#line 1553 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 37: /* billions ::= one_to_999999999 BILLION */
      case 38: /* billions ::= NUMBER BILLION */ yytestcase(yyruleno==38);
#line 156 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; }
#line 1560 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 39: /* billions ::= BILLION */
#line 158 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000.0; }
#line 1566 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 43: /* millionths ::= one_to_999999 MILLIONTH */
      case 45: /* millionths ::= NUMBER MILLIONTH */ yytestcase(yyruleno==45);
#line 168 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; yylhsminor.yy0.suffix = TH; }
#line 1573 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 44: /* millionths ::= one_to_999999 MILLIONTHS */
      case 46: /* millionths ::= NUMBER MILLIONTHS */ yytestcase(yyruleno==46);
#line 169 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; yylhsminor.yy0.suffix = THS; }
#line 1580 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 47: /* millionths ::= MILLIONTH */
#line 172 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000.0; yylhsminor.yy0.suffix = TH; }
#line 1586 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 48: /* millionths ::= MILLIONTHS */
#line 173 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000.0; yylhsminor.yy0.suffix = THS; }
#line 1592 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 52: /* millions ::= one_to_999999 MILLION */
      case 53: /* millions ::= NUMBER MILLION */ yytestcase(yyruleno==53);
#line 183 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; }
#line 1599 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 54: /* millions ::= MILLION */
#line 185 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000.0; }
#line 1605 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 58: /* thousandths ::= one_to_999 THOUSANDTH */
      case 60: /* thousandths ::= NUMBER THOUSANDTH */ yytestcase(yyruleno==60);
#line 195 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; yylhsminor.yy0.suffix = TH; }
#line 1612 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 59: /* thousandths ::= one_to_999 THOUSANDTHS */
      case 61: /* thousandths ::= NUMBER THOUSANDTHS */ yytestcase(yyruleno==61);
#line 196 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; yylhsminor.yy0.suffix = THS; }
#line 1619 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 62: /* thousandths ::= THOUSANDTH */
#line 199 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000.0; yylhsminor.yy0.suffix = TH; }
#line 1625 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 63: /* thousandths ::= THOUSANDTHS */
#line 200 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000.0; yylhsminor.yy0.suffix = THS; }
#line 1631 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 67: /* thousands ::= one_to_999 THOUSAND */
      case 68: /* thousands ::= NUMBER THOUSAND */ yytestcase(yyruleno==68);
#line 210 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; }
#line 1638 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 69: /* thousands ::= THOUSAND */
#line 212 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000.0; }
#line 1644 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 70: /* first_to_999th ::= hundreds AND first_to_99th */
#line 218 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1650 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 73: /* first_to_999th ::= AND first_to_99th */
#line 221 "parser.yy"
{ yymsp[-1].minor.yy0.spos = yymsp[0].minor.yy0.spos; yymsp[-1].minor.yy0.epos = yymsp[0].minor.yy0.epos; yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; yymsp[-1].minor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1656 "parser.c"
        break;
      case 75: /* hundredths ::= one_to_99 HUNDREDTH */
      case 77: /* hundredths ::= NUMBER HUNDREDTH */ yytestcase(yyruleno==77);
#line 224 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; yylhsminor.yy0.suffix = TH; }
#line 1662 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 76: /* hundredths ::= one_to_99 HUNDREDTHS */
      case 78: /* hundredths ::= NUMBER HUNDREDTHS */ yytestcase(yyruleno==78);
#line 225 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; yylhsminor.yy0.suffix = THS; }
#line 1669 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 79: /* hundredths ::= HUNDREDTH */
#line 228 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 100.0; yylhsminor.yy0.suffix = TH; }
#line 1675 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 80: /* hundredths ::= HUNDREDTHS */
#line 229 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 100.0; yylhsminor.yy0.suffix = THS; }
#line 1681 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 85: /* one_to_999 ::= hundreds AND one_to_99 */
#line 240 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1687 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 88: /* one_to_999 ::= AND one_to_99 */
#line 243 "parser.yy"
{ yymsp[-1].minor.yy0.spos = yymsp[0].minor.yy0.spos; yymsp[-1].minor.yy0.epos = yymsp[0].minor.yy0.epos; yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1693 "parser.c"
        break;
      case 90: /* hundreds ::= one_to_99 HUNDRED */
      case 91: /* hundreds ::= NUMBER HUNDRED */ yytestcase(yyruleno==91);
#line 246 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; }
#line 1699 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 92: /* hundreds ::= HUNDRED */
#line 248 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 100.0; }
#line 1705 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 97: /* one_to_9 ::= ONE */
#line 259 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1.0; }
#line 1711 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 98: /* one_to_9 ::= TWO */
#line 260 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 2.0; }
#line 1717 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 99: /* one_to_9 ::= THREE */
#line 261 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 3.0; }
#line 1723 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 100: /* one_to_9 ::= FOUR */
#line 262 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 4.0; }
#line 1729 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 101: /* one_to_9 ::= FIVE */
#line 263 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 5.0; }
#line 1735 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 102: /* one_to_9 ::= SIX */
#line 264 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 6.0; }
#line 1741 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 103: /* one_to_9 ::= SEVEN */
#line 265 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 7.0; }
#line 1747 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 104: /* one_to_9 ::= EIGHT */
#line 266 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 8.0; }
#line 1753 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 105: /* one_to_9 ::= NINE */
#line 267 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 9.0; }
#line 1759 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 106: /* ten_to_19 ::= TEN */
#line 269 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 10.0; }
#line 1765 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 107: /* ten_to_19 ::= ELEVEN */
#line 270 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 11.0; }
#line 1771 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 108: /* ten_to_19 ::= TWELVE */
#line 271 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 12.0; }
#line 1777 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 109: /* ten_to_19 ::= THIRTEEN */
#line 272 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 13.0; }
#line 1783 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 110: /* ten_to_19 ::= FOURTEEN */
#line 273 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 14.0; }
#line 1789 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 111: /* ten_to_19 ::= FIFTEEN */
#line 274 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 15.0; }
#line 1795 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 112: /* ten_to_19 ::= SIXTEEN */
#line 275 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 16.0; }
#line 1801 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 113: /* ten_to_19 ::= SEVENTEEN */
#line 276 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 17.0; }
#line 1807 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 114: /* ten_to_19 ::= EIGHTEEN */
#line 277 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 18.0; }
#line 1813 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 115: /* ten_to_19 ::= NINETEEN */
#line 278 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 19.0; }
#line 1819 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 116: /* tens ::= TWENTY */
#line 280 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 20.0; }
#line 1825 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 117: /* tens ::= THIRTY */
#line 281 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 30.0; }
#line 1831 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 118: /* tens ::= FORTY */
#line 282 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 40.0; }
#line 1837 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 119: /* tens ::= FIFTY */
#line 283 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 50.0; }
#line 1843 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 120: /* tens ::= SIXTY */
#line 284 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 60.0; }
#line 1849 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 121: /* tens ::= SEVENTY */
#line 285 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 70.0; }
#line 1855 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 122: /* tens ::= EIGHTY */
#line 286 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 80.0; }
#line 1861 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 123: /* tens ::= NINETY */
#line 287 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 90.0; }
#line 1867 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 124: /* first_to_9th ::= FIRST */
#line 289 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1.0; yylhsminor.yy0.suffix = ST; }
#line 1873 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 125: /* first_to_9th ::= FIRSTS */
#line 290 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1.0; yylhsminor.yy0.suffix = STS; }
#line 1879 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 126: /* first_to_9th ::= SECOND */
#line 291 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 2.0; yylhsminor.yy0.suffix = ND; }
#line 1885 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 127: /* first_to_9th ::= SECONDS */
#line 292 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 2.0; yylhsminor.yy0.suffix = NDS; }
#line 1891 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 128: /* first_to_9th ::= THIRD */
#line 293 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 3.0; yylhsminor.yy0.suffix = RD; }
#line 1897 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 129: /* first_to_9th ::= THIRDS */
#line 294 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 3.0; yylhsminor.yy0.suffix = RDS; }
#line 1903 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 130: /* first_to_9th ::= FOURTH */
#line 295 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 4.0; yylhsminor.yy0.suffix = TH; }
#line 1909 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 131: /* first_to_9th ::= FOURTHS */
#line 296 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 4.0; yylhsminor.yy0.suffix = THS; }
#line 1915 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 132: /* first_to_9th ::= FIFTH */
#line 297 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 5.0; yylhsminor.yy0.suffix = TH; }
#line 1921 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 133: /* first_to_9th ::= FIFTHS */
#line 298 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 5.0; yylhsminor.yy0.suffix = THS; }
#line 1927 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 134: /* first_to_9th ::= SIXTH */
#line 299 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 6.0; yylhsminor.yy0.suffix = TH; }
#line 1933 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 135: /* first_to_9th ::= SIXTHS */
#line 300 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 6.0; yylhsminor.yy0.suffix = THS; }
#line 1939 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 136: /* first_to_9th ::= SEVENTH */
#line 301 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 7.0; yylhsminor.yy0.suffix = TH; }
#line 1945 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 137: /* first_to_9th ::= SEVENTHS */
#line 302 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 7.0; yylhsminor.yy0.suffix = THS; }
#line 1951 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 138: /* first_to_9th ::= EIGHTH */
#line 303 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 8.0; yylhsminor.yy0.suffix = TH; }
#line 1957 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 139: /* first_to_9th ::= EIGHTHS */
#line 304 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 8.0; yylhsminor.yy0.suffix = THS; }
#line 1963 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 140: /* first_to_9th ::= NINTH */
#line 305 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 9.0; yylhsminor.yy0.suffix = TH; }
#line 1969 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 141: /* first_to_9th ::= NINTHS */
#line 306 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 9.0; yylhsminor.yy0.suffix = THS; }
#line 1975 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 142: /* tenth_to_19th ::= TENTH */
#line 308 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 10.0; yylhsminor.yy0.suffix = TH; }
#line 1981 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 143: /* tenth_to_19th ::= TENTHS */
#line 309 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 10.0; yylhsminor.yy0.suffix = THS; }
#line 1987 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 144: /* tenth_to_19th ::= ELEVENTH */
#line 310 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 11.0; yylhsminor.yy0.suffix = TH; }
#line 1993 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 145: /* tenth_to_19th ::= ELEVENTHS */
#line 311 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 11.0; yylhsminor.yy0.suffix = THS; }
#line 1999 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 146: /* tenth_to_19th ::= TWELFTH */
#line 312 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 12.0; yylhsminor.yy0.suffix = TH; }
#line 2005 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 147: /* tenth_to_19th ::= TWELFTHS */
#line 313 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 12.0; yylhsminor.yy0.suffix = THS; }
#line 2011 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 148: /* tenth_to_19th ::= THIRTEENTH */
#line 314 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 13.0; yylhsminor.yy0.suffix = TH; }
#line 2017 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 149: /* tenth_to_19th ::= THIRTEENTHS */
#line 315 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 13.0; yylhsminor.yy0.suffix = THS; }
#line 2023 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 150: /* tenth_to_19th ::= FOURTEENTH */
#line 316 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 14.0; yylhsminor.yy0.suffix = TH; }
#line 2029 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 151: /* tenth_to_19th ::= FOURTEENTHS */
#line 317 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 14.0; yylhsminor.yy0.suffix = THS; }
#line 2035 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 152: /* tenth_to_19th ::= FIFTEENTH */
#line 318 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 15.0; yylhsminor.yy0.suffix = TH; }
#line 2041 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 153: /* tenth_to_19th ::= FIFTEENTHS */
#line 319 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 15.0; yylhsminor.yy0.suffix = THS; }
#line 2047 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 154: /* tenth_to_19th ::= SIXTEENTH */
#line 320 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 16.0; yylhsminor.yy0.suffix = TH; }
#line 2053 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 155: /* tenth_to_19th ::= SIXTEENTHS */
#line 321 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 16.0; yylhsminor.yy0.suffix = THS; }
#line 2059 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 156: /* tenth_to_19th ::= SEVENTEENTH */
#line 322 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 17.0; yylhsminor.yy0.suffix = TH; }
#line 2065 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 157: /* tenth_to_19th ::= SEVENTEENTHS */
#line 323 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 17.0; yylhsminor.yy0.suffix = THS; }
#line 2071 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 158: /* tenth_to_19th ::= EIGHTEENTH */
#line 324 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 18.0; yylhsminor.yy0.suffix = TH; }
#line 2077 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 159: /* tenth_to_19th ::= EIGHTEENTHS */
#line 325 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 18.0; yylhsminor.yy0.suffix = THS; }
#line 2083 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 160: /* tenth_to_19th ::= NINETEENTH */
#line 326 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 19.0; yylhsminor.yy0.suffix = TH; }
#line 2089 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 161: /* tenth_to_19th ::= NINETEENTHS */
#line 327 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 19.0; yylhsminor.yy0.suffix = THS; }
#line 2095 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 162: /* tenths ::= TWENTIETH */
#line 329 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 20.0; yylhsminor.yy0.suffix = TH; }
#line 2101 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 163: /* tenths ::= TWENTIETHS */
#line 330 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 20.0; yylhsminor.yy0.suffix = THS; }
#line 2107 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 164: /* tenths ::= THIRTIETH */
#line 331 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 30.0; yylhsminor.yy0.suffix = TH; }
#line 2113 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 165: /* tenths ::= THIRTIETHS */
#line 332 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 30.0; yylhsminor.yy0.suffix = THS; }
#line 2119 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 166: /* tenths ::= FOURTIETH */
#line 333 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 40.0; yylhsminor.yy0.suffix = TH; }
#line 2125 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 167: /* tenths ::= FOURTIETHS */
#line 334 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 40.0; yylhsminor.yy0.suffix = THS; }
#line 2131 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 168: /* tenths ::= FIFTIETH */
#line 335 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 50.0; yylhsminor.yy0.suffix = TH; }
#line 2137 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 169: /* tenths ::= FIFTIETHS */
#line 336 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 50.0; yylhsminor.yy0.suffix = THS; }
#line 2143 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 170: /* tenths ::= SIXTIETH */
#line 337 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 60.0; yylhsminor.yy0.suffix = TH; }
#line 2149 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 171: /* tenths ::= SIXTIETHS */
#line 338 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 60.0; yylhsminor.yy0.suffix = THS; }
#line 2155 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 172: /* tenths ::= SEVENTIETH */
#line 339 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 70.0; yylhsminor.yy0.suffix = TH; }
#line 2161 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 173: /* tenths ::= SEVENTIETHS */
#line 340 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 70.0; yylhsminor.yy0.suffix = THS; }
#line 2167 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 174: /* tenths ::= EIGHTIETH */
#line 341 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 80.0; yylhsminor.yy0.suffix = TH; }
#line 2173 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 175: /* tenths ::= EIGHTIETHS */
#line 342 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 80.0; yylhsminor.yy0.suffix = THS; }
#line 2179 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 176: /* tenths ::= NINETIETH */
#line 343 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 90.0; yylhsminor.yy0.suffix = TH; }
#line 2185 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 177: /* tenths ::= NINETIETHS */
#line 344 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 90.0; yylhsminor.yy0.suffix = THS; }
#line 2191 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      default:
      /* (178) expr ::= num_ident (OPTIMIZED OUT) */ assert(yyruleno!=178);
      /* (179) expr ::= ident_num (OPTIMIZED OUT) */ assert(yyruleno!=179);
      /* (180) ident_num ::= identifiers num_ident */ yytestcase(yyruleno==180);
      /* (181) ident_num ::= identifiers */ yytestcase(yyruleno==181);
      /* (182) identifiers ::= identifiers CHARACTERS */ yytestcase(yyruleno==182);
      /* (183) identifiers ::= CHARACTERS */ yytestcase(yyruleno==183);
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
#line 22 "parser.yy"
 fprintf(stderr,"Giving up.  Parser is hopelessly lost...\n"); 
#line 2243 "parser.c"
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
 fprintf(stderr, "Syntax error\n"); 
#line 2262 "parser.c"
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
