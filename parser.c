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
#line 37 "parser.c"
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
#define YYNOCODE 141
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
#define YYNSTATE             25
#define YYNRULE              183
#define YY_MAX_SHIFT         24
#define YY_MIN_SHIFTREDUCE   192
#define YY_MAX_SHIFTREDUCE   374
#define YY_MIN_REDUCE        375
#define YY_MAX_REDUCE        557
#define YY_ERROR_ACTION      558
#define YY_ACCEPT_ACTION     559
#define YY_NO_ACTION         560
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
#define YY_ACTTAB_COUNT (998)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   203,  211,  212,   11,  218,  226,  227,  233,  241,  242,
 /*    10 */   248,  256,  257,  263,    7,  273,  274,  286,  291,  292,
 /*    20 */   293,  294,  295,  296,  297,  298,  299,  300,  301,  302,
 /*    30 */   303,  304,  305,  306,  307,  308,  309,  310,  311,  312,
 /*    40 */   313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
 /*    50 */   323,  324,  325,  326,  327,  328,  329,  330,  331,  332,
 /*    60 */   333,  334,  335,  336,  337,  338,  339,  340,  341,  342,
 /*    70 */   343,  344,  345,  346,  347,  348,  349,  350,  351,  352,
 /*    80 */   353,  354,  355,  356,  357,  358,  359,  360,  361,  362,
 /*    90 */   363,  364,  365,  366,  367,  368,  369,  370,  371,  374,
 /*   100 */   203,  211,  212,   11,  218,  226,  227,  233,  241,  242,
 /*   110 */   248,  256,  257,  263,    7,  273,  274,  286,  291,  292,
 /*   120 */   293,  294,  295,  296,  297,  298,  299,  300,  301,  302,
 /*   130 */   303,  304,  305,  306,  307,  308,  309,  310,  311,  312,
 /*   140 */   313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
 /*   150 */   323,  324,  325,  326,  327,  328,  329,  330,  331,  332,
 /*   160 */   333,  334,  335,  336,  337,  338,  339,  340,  341,  342,
 /*   170 */   343,  344,  345,  346,  347,  348,  349,  350,  351,  352,
 /*   180 */   353,  354,  355,  356,  357,  358,  359,  360,  361,  362,
 /*   190 */   363,  364,  365,  366,  367,  368,  369,  370,  371,  373,
 /*   200 */    12,  374,  226,  227,  233,  241,  242,  248,  256,  257,
 /*   210 */   263,    7,  273,  274,  286,  291,  292,  293,  294,  295,
 /*   220 */   296,  297,  298,  299,  300,  301,  302,  303,  304,  305,
 /*   230 */   306,  307,  308,  309,  310,  311,  312,  313,  314,  315,
 /*   240 */   316,  317,  318,  319,  320,  321,  322,  323,  324,  325,
 /*   250 */   326,  327,  328,  329,  330,  331,  332,  333,  334,  335,
 /*   260 */   336,  337,  338,  339,  340,  341,  342,  343,  344,  345,
 /*   270 */   346,  347,  348,  349,  350,  351,  352,  353,  354,  355,
 /*   280 */   356,  357,  358,  359,  360,  361,  362,  363,  364,  365,
 /*   290 */   366,  367,  368,  369,  370,  371,   13,  207,  208,   23,
 /*   300 */   216,  241,  242,  248,  256,  257,  263,    7,  273,  274,
 /*   310 */   286,  291,  292,  293,  294,  295,  296,  297,  298,  299,
 /*   320 */   300,  301,  302,  303,  304,  305,  306,  307,  308,  309,
 /*   330 */   310,  311,  312,  313,  314,  315,  316,  317,  318,  319,
 /*   340 */   320,  321,  322,  323,  324,  325,  326,  327,  328,  329,
 /*   350 */   330,  331,  332,  333,  334,  335,  336,  337,  338,  339,
 /*   360 */   340,  341,  342,  343,  344,  345,  346,  347,  348,  349,
 /*   370 */   350,  351,  352,  353,  354,  355,  356,  357,  358,  359,
 /*   380 */   360,  361,  362,  363,  364,  365,  366,  367,  368,  369,
 /*   390 */   370,  371,   14,  254,  255,  262,  373,  271,  272,  285,
 /*   400 */   256,  257,  263,    7,  273,  274,  286,  291,  292,  293,
 /*   410 */   294,  295,  296,  297,  298,  299,  300,  301,  302,  303,
 /*   420 */   304,  305,  306,  307,  308,  309,  310,  311,  312,  313,
 /*   430 */   314,  315,  316,  317,  318,  319,  320,  321,  322,  323,
 /*   440 */   324,  325,  326,  327,  328,  329,  330,  331,  332,  333,
 /*   450 */   334,  335,  336,  337,  338,  339,  340,  341,  342,  343,
 /*   460 */   344,  345,  346,  347,  348,  349,  350,  351,  352,  353,
 /*   470 */   354,  355,  356,  357,  358,  359,  360,  361,  362,  363,
 /*   480 */   364,  365,  366,  367,  368,  369,  370,  371,   19,  239,
 /*   490 */   240,  247,  254,  255,  262,  375,  271,  272,  285,    7,
 /*   500 */   273,  274,  286,  291,  292,  293,  294,  295,  296,  297,
 /*   510 */   298,  299,  300,  301,  302,  303,  304,  305,  306,  307,
 /*   520 */   308,  309,  310,  311,  312,  313,  314,  315,  316,  317,
 /*   530 */   318,  319,  320,  321,  322,  323,  324,  325,  326,  327,
 /*   540 */   328,  329,  330,  331,  332,  333,  334,  335,  336,  337,
 /*   550 */   338,  339,  340,  341,  342,  343,  344,  345,  346,  347,
 /*   560 */   348,  349,  350,  351,  352,  353,  354,  355,  356,  357,
 /*   570 */   358,  359,  360,  361,  362,  363,  364,  365,  366,  367,
 /*   580 */   368,  369,  370,  371,    8,  222,  223,  231,  291,  292,
 /*   590 */   293,  294,  295,  296,  297,  298,  299,  300,  301,  302,
 /*   600 */   303,  304,  305,  306,  307,  308,  309,  310,  311,  312,
 /*   610 */   313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
 /*   620 */   323,  324,  325,  326,  327,  328,  329,  330,  331,  332,
 /*   630 */   333,  334,  335,  336,  337,  338,  339,  340,  341,  342,
 /*   640 */   343,  344,  345,  346,  347,  348,  349,  350,  351,  352,
 /*   650 */   353,  354,  355,  356,  357,  358,  359,  360,  361,  362,
 /*   660 */   363,  364,  365,  366,  367,  368,  369,  370,  371,  291,
 /*   670 */   292,  293,  294,  295,  296,  297,  298,  299,  300,  301,
 /*   680 */   302,  303,  304,  305,  306,  307,  308,  309,  310,  311,
 /*   690 */   312,  313,  314,  315,  316,  317,  318,  319,  320,  321,
 /*   700 */   322,  323,  324,  325,  326,  327,  328,  329,  330,  331,
 /*   710 */   332,  333,  334,  335,  336,  337,  338,  339,  340,  341,
 /*   720 */   342,  343,  344,  345,  346,  347,  348,  349,  350,  351,
 /*   730 */   352,  353,  354,  355,  356,  357,  358,  359,  360,  361,
 /*   740 */   362,  363,  364,  365,  366,  367,  368,  369,  370,  371,
 /*   750 */   559,   24,  193,   10,    1,   21,  202,    2,  206,  205,
 /*   760 */    15,    3,  221,  220,   16,    4,  236,  235,   17,    5,
 /*   770 */   251,  250,   18,    6,  268,  266,   20,    9,  278,  276,
 /*   780 */   277,  290,  289,  195,  377,   21,  202,    2,  206,  205,
 /*   790 */    15,    3,  221,  220,   16,    4,  236,  235,   17,    5,
 /*   800 */   251,  250,   18,    6,  268,  266,   20,    9,  278,  276,
 /*   810 */   277,  290,  289,  291,  292,  293,  294,  295,  296,  297,
 /*   820 */   298,  299,  234,  377,  243,    5,  251,  250,   18,    6,
 /*   830 */   268,  266,   20,    9,  278,  276,  277,  290,  289,  377,
 /*   840 */   318,  319,  320,  321,  322,  323,  324,  325,  326,  327,
 /*   850 */   328,  329,  330,  331,  332,  333,  334,  335,  204,  377,
 /*   860 */   213,    3,  221,  220,   16,    4,  236,  235,   17,    5,
 /*   870 */   251,  250,   18,    6,  268,  266,   20,    9,  278,  276,
 /*   880 */   277,  290,  289,  219,  377,  228,    4,  236,  235,   17,
 /*   890 */     5,  251,  250,   18,    6,  268,  266,   20,    9,  278,
 /*   900 */   276,  277,  290,  289,  209,  210,  377,  217,  224,  225,
 /*   910 */   232,  239,  240,  247,  254,  255,  262,  377,  271,  272,
 /*   920 */   285,  249,  377,  258,    6,  268,  266,   20,    9,  278,
 /*   930 */   276,  277,  290,  289,  377,  224,  225,  232,  239,  240,
 /*   940 */   247,  254,  255,  262,  377,  271,  272,  285,  265,  377,
 /*   950 */   280,    9,  278,  276,  277,  290,  289,  267,  377,  282,
 /*   960 */     9,  278,  276,  277,  290,  289,  264,  377,  279,    9,
 /*   970 */   278,  276,  277,  290,  289,  237,  238,  246,  377,  252,
 /*   980 */   253,  261,  377,  377,  271,  272,  285,  269,  270,  284,
 /*   990 */    22,  377,  198,  275,  200,  197,  287,  199,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    10 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*    20 */    26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
 /*    30 */    36,   37,   38,   39,   40,   41,   42,   43,   44,   45,
 /*    40 */    46,   47,   48,   49,   50,   51,   52,   53,   54,   55,
 /*    50 */    56,   57,   58,   59,   60,   61,   62,   63,   64,   65,
 /*    60 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    70 */    76,   77,   78,   79,   80,   81,   82,   83,   84,   85,
 /*    80 */    86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
 /*    90 */    96,   97,   98,   99,  100,  101,  102,  103,  104,  105,
 /*   100 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   110 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   120 */    26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
 /*   130 */    36,   37,   38,   39,   40,   41,   42,   43,   44,   45,
 /*   140 */    46,   47,   48,   49,   50,   51,   52,   53,   54,   55,
 /*   150 */    56,   57,   58,   59,   60,   61,   62,   63,   64,   65,
 /*   160 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   170 */    76,   77,   78,   79,   80,   81,   82,   83,   84,   85,
 /*   180 */    86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
 /*   190 */    96,   97,   98,   99,  100,  101,  102,  103,  104,  105,
 /*   200 */     9,  105,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   210 */    19,   20,   21,   22,   23,   24,   25,   26,   27,   28,
 /*   220 */    29,   30,   31,   32,   33,   34,   35,   36,   37,   38,
 /*   230 */    39,   40,   41,   42,   43,   44,   45,   46,   47,   48,
 /*   240 */    49,   50,   51,   52,   53,   54,   55,   56,   57,   58,
 /*   250 */    59,   60,   61,   62,   63,   64,   65,   66,   67,   68,
 /*   260 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   78,
 /*   270 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   280 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*   290 */    99,  100,  101,  102,  103,  104,    9,    7,    8,  111,
 /*   300 */    10,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   310 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   320 */    33,   34,   35,   36,   37,   38,   39,   40,   41,   42,
 /*   330 */    43,   44,   45,   46,   47,   48,   49,   50,   51,   52,
 /*   340 */    53,   54,   55,   56,   57,   58,   59,   60,   61,   62,
 /*   350 */    63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*   360 */    73,   74,   75,   76,   77,   78,   79,   80,   81,   82,
 /*   370 */    83,   84,   85,   86,   87,   88,   89,   90,   91,   92,
 /*   380 */    93,   94,   95,   96,   97,   98,   99,  100,  101,  102,
 /*   390 */   103,  104,    9,   17,   18,   19,  105,   21,   22,   23,
 /*   400 */    17,   18,   19,   20,   21,   22,   23,   24,   25,   26,
 /*   410 */    27,   28,   29,   30,   31,   32,   33,   34,   35,   36,
 /*   420 */    37,   38,   39,   40,   41,   42,   43,   44,   45,   46,
 /*   430 */    47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
 /*   440 */    57,   58,   59,   60,   61,   62,   63,   64,   65,   66,
 /*   450 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   460 */    77,   78,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   470 */    87,   88,   89,   90,   91,   92,   93,   94,   95,   96,
 /*   480 */    97,   98,   99,  100,  101,  102,  103,  104,    9,   14,
 /*   490 */    15,   16,   17,   18,   19,    0,   21,   22,   23,   20,
 /*   500 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   510 */    31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
 /*   520 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*   530 */    51,   52,   53,   54,   55,   56,   57,   58,   59,   60,
 /*   540 */    61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
 /*   550 */    71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
 /*   560 */    81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
 /*   570 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   580 */   101,  102,  103,  104,   20,   11,   12,   13,   24,   25,
 /*   590 */    26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
 /*   600 */    36,   37,   38,   39,   40,   41,   42,   43,   44,   45,
 /*   610 */    46,   47,   48,   49,   50,   51,   52,   53,   54,   55,
 /*   620 */    56,   57,   58,   59,   60,   61,   62,   63,   64,   65,
 /*   630 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   640 */    76,   77,   78,   79,   80,   81,   82,   83,   84,   85,
 /*   650 */    86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
 /*   660 */    96,   97,   98,   99,  100,  101,  102,  103,  104,   24,
 /*   670 */    25,   26,   27,   28,   29,   30,   31,   32,   33,   34,
 /*   680 */    35,   36,   37,   38,   39,   40,   41,   42,   43,   44,
 /*   690 */    45,   46,   47,   48,   49,   50,   51,   52,   53,   54,
 /*   700 */    55,   56,   57,   58,   59,   60,   61,   62,   63,   64,
 /*   710 */    65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*   720 */    75,   76,   77,   78,   79,   80,   81,   82,   83,   84,
 /*   730 */    85,   86,   87,   88,   89,   90,   91,   92,   93,   94,
 /*   740 */    95,   96,   97,   98,   99,  100,  101,  102,  103,  104,
 /*   750 */   107,  108,  109,  110,  111,  112,  113,  114,  115,  116,
 /*   760 */   117,  118,  119,  120,  121,  122,  123,  124,  125,  126,
 /*   770 */   127,  128,  129,  130,  131,  132,  133,  134,  135,  136,
 /*   780 */   137,  138,  139,  110,  140,  112,  113,  114,  115,  116,
 /*   790 */   117,  118,  119,  120,  121,  122,  123,  124,  125,  126,
 /*   800 */   127,  128,  129,  130,  131,  132,  133,  134,  135,  136,
 /*   810 */   137,  138,  139,   24,   25,   26,   27,   28,   29,   30,
 /*   820 */    31,   32,  123,  140,  125,  126,  127,  128,  129,  130,
 /*   830 */   131,  132,  133,  134,  135,  136,  137,  138,  139,  140,
 /*   840 */    51,   52,   53,   54,   55,   56,   57,   58,   59,   60,
 /*   850 */    61,   62,   63,   64,   65,   66,   67,   68,  115,  140,
 /*   860 */   117,  118,  119,  120,  121,  122,  123,  124,  125,  126,
 /*   870 */   127,  128,  129,  130,  131,  132,  133,  134,  135,  136,
 /*   880 */   137,  138,  139,  119,  140,  121,  122,  123,  124,  125,
 /*   890 */   126,  127,  128,  129,  130,  131,  132,  133,  134,  135,
 /*   900 */   136,  137,  138,  139,    7,    8,  140,   10,   11,   12,
 /*   910 */    13,   14,   15,   16,   17,   18,   19,  140,   21,   22,
 /*   920 */    23,  127,  140,  129,  130,  131,  132,  133,  134,  135,
 /*   930 */   136,  137,  138,  139,  140,   11,   12,   13,   14,   15,
 /*   940 */    16,   17,   18,   19,  140,   21,   22,   23,  131,  140,
 /*   950 */   133,  134,  135,  136,  137,  138,  139,  131,  140,  133,
 /*   960 */   134,  135,  136,  137,  138,  139,  131,  140,  133,  134,
 /*   970 */   135,  136,  137,  138,  139,   14,   15,   16,  140,   17,
 /*   980 */    18,   19,  140,  140,   21,   22,   23,   21,   22,   23,
 /*   990 */     1,  140,    3,  135,    5,    2,  138,    4,
};
#define YY_SHIFT_USE_DFLT (998)
#define YY_SHIFT_COUNT    (24)
#define YY_SHIFT_MIN      (-6)
#define YY_SHIFT_MAX      (993)
static const short yy_shift_ofst[] = {
 /*     0 */    -6,   94,  191,  287,  383,  479,  564,  645,  645,  789,
 /*    10 */    96,  897,  924,  475,  376,  290,  574,  961,  962,  963,
 /*    20 */   966,  989,  993,  291,  495,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (10)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (858)
static const short yy_reduce_ofst[] = {
 /*     0 */   643,  673,  743,  764,  699,  794,  817,  826,  835,  858,
 /*    10 */   188,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   555,  558,  397,  412,  427,  442,  464,  558,  558,  471,
 /*    10 */   377,  558,  558,  558,  558,  398,  413,  428,  443,  558,
 /*    20 */   466,  384,  558,  379,  558,
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
  "$",             "AND_A",         "QUARTER",       "QUARTERS",    
  "HALF",          "HALVES",        "ZERO",          "TRILLIONTH",  
  "TRILLIONTHS",   "NUMBER",        "TRILLION",      "BILLIONTH",   
  "BILLIONTHS",    "BILLION",       "MILLIONTH",     "MILLIONTHS",  
  "MILLION",       "THOUSANDTH",    "THOUSANDTHS",   "THOUSAND",    
  "AND",           "HUNDREDTH",     "HUNDREDTHS",    "HUNDRED",     
  "ONE",           "TWO",           "THREE",         "FOUR",        
  "FIVE",          "SIX",           "SEVEN",         "EIGHT",       
  "NINE",          "TEN",           "ELEVEN",        "TWELVE",      
  "THIRTEEN",      "FOURTEEN",      "FIFTEEN",       "SIXTEEN",     
  "SEVENTEEN",     "EIGHTEEN",      "NINETEEN",      "TWENTY",      
  "THIRTY",        "FORTY",         "FIFTY",         "SIXTY",       
  "SEVENTY",       "EIGHTY",        "NINETY",        "FIRST",       
  "FIRSTS",        "SECOND",        "SECONDS",       "THIRD",       
  "THIRDS",        "FOURTH",        "FOURTHS",       "FIFTH",       
  "FIFTHS",        "SIXTH",         "SIXTHS",        "SEVENTH",     
  "SEVENTHS",      "EIGHTH",        "EIGHTHS",       "NINTH",       
  "NINTHS",        "TENTH",         "TENTHS",        "ELEVENTH",    
  "ELEVENTHS",     "TWELFTH",       "TWELFTHS",      "THIRTEENTH",  
  "THIRTEENTHS",   "FOURTEENTH",    "FOURTEENTHS",   "FIFTEENTH",   
  "FIFTEENTHS",    "SIXTEENTH",     "SIXTEENTHS",    "SEVENTEENTH", 
  "SEVENTEENTHS",  "EIGHTEENTH",    "EIGHTEENTHS",   "NINETEENTH",  
  "NINETEENTHS",   "TWENTIETH",     "TWENTIETHS",    "THIRTIETH",   
  "THIRTIETHS",    "FOURTIETH",     "FOURTIETHS",    "FIFTIETH",    
  "FIFTIETHS",     "SIXTIETH",      "SIXTIETHS",     "SEVENTIETH",  
  "SEVENTIETHS",   "EIGHTIETH",     "EIGHTIETHS",    "NINETIETH",   
  "NINETIETHS",    "CHARACTERS",    "error",         "program",     
  "expr",          "sentence",      "final_number",  "identifiers", 
  "one_to_999999999999999",  "first_to_999999999999999th",  "trillions",     "first_to_999999999999th",
  "trillionths",   "one_to_999999999999",  "billions",      "first_to_999999999th",
  "billionths",    "one_to_999999999",  "millions",      "first_to_999999th",
  "millionths",    "one_to_999999",  "thousands",     "first_to_999th",
  "thousandths",   "one_to_999",    "hundreds",      "first_to_99th",
  "hundredths",    "one_to_99",     "tens",          "first_to_9th",
  "tenths",        "tenth_to_19th",  "one_to_9",      "ten_to_19",   
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= expr",
 /*   1 */ "expr ::= sentence",
 /*   2 */ "expr ::= final_number",
 /*   3 */ "sentence ::= identifiers final_number",
 /*   4 */ "sentence ::= final_number identifiers",
 /*   5 */ "final_number ::= one_to_999999999999999 AND_A QUARTER",
 /*   6 */ "final_number ::= one_to_999999999999999 QUARTERS",
 /*   7 */ "final_number ::= one_to_999999999999999 AND_A HALF",
 /*   8 */ "final_number ::= one_to_999999999999999 HALVES",
 /*   9 */ "final_number ::= one_to_999999999999999",
 /*  10 */ "final_number ::= first_to_999999999999999th",
 /*  11 */ "final_number ::= ZERO",
 /*  12 */ "first_to_999999999999999th ::= trillions first_to_999999999999th",
 /*  13 */ "first_to_999999999999999th ::= trillionths",
 /*  14 */ "first_to_999999999999999th ::= first_to_999999999999th",
 /*  15 */ "trillionths ::= one_to_999999999999 TRILLIONTH",
 /*  16 */ "trillionths ::= one_to_999999999999 TRILLIONTHS",
 /*  17 */ "trillionths ::= NUMBER TRILLIONTH",
 /*  18 */ "trillionths ::= NUMBER TRILLIONTHS",
 /*  19 */ "trillionths ::= TRILLIONTH",
 /*  20 */ "trillionths ::= TRILLIONTHS",
 /*  21 */ "one_to_999999999999999 ::= trillions one_to_999999999999",
 /*  22 */ "one_to_999999999999999 ::= trillions",
 /*  23 */ "one_to_999999999999999 ::= one_to_999999999999",
 /*  24 */ "trillions ::= one_to_999999999999 TRILLION",
 /*  25 */ "trillions ::= NUMBER TRILLION",
 /*  26 */ "trillions ::= TRILLION",
 /*  27 */ "first_to_999999999999th ::= billions first_to_999999999th",
 /*  28 */ "first_to_999999999999th ::= billionths",
 /*  29 */ "first_to_999999999999th ::= first_to_999999999th",
 /*  30 */ "billionths ::= one_to_999999999 BILLIONTH",
 /*  31 */ "billionths ::= one_to_999999999 BILLIONTHS",
 /*  32 */ "billionths ::= NUMBER BILLIONTH",
 /*  33 */ "billionths ::= NUMBER BILLIONTHS",
 /*  34 */ "billionths ::= BILLIONTH",
 /*  35 */ "billionths ::= BILLIONTHS",
 /*  36 */ "one_to_999999999999 ::= billions one_to_999999999",
 /*  37 */ "one_to_999999999999 ::= billions",
 /*  38 */ "one_to_999999999999 ::= one_to_999999999",
 /*  39 */ "billions ::= one_to_999999999 BILLION",
 /*  40 */ "billions ::= NUMBER BILLION",
 /*  41 */ "billions ::= BILLION",
 /*  42 */ "first_to_999999999th ::= millions first_to_999999th",
 /*  43 */ "first_to_999999999th ::= millionths",
 /*  44 */ "first_to_999999999th ::= first_to_999999th",
 /*  45 */ "millionths ::= one_to_999999 MILLIONTH",
 /*  46 */ "millionths ::= one_to_999999 MILLIONTHS",
 /*  47 */ "millionths ::= NUMBER MILLIONTH",
 /*  48 */ "millionths ::= NUMBER MILLIONTHS",
 /*  49 */ "millionths ::= MILLIONTH",
 /*  50 */ "millionths ::= MILLIONTHS",
 /*  51 */ "one_to_999999999 ::= millions one_to_999999",
 /*  52 */ "one_to_999999999 ::= millions",
 /*  53 */ "one_to_999999999 ::= one_to_999999",
 /*  54 */ "millions ::= one_to_999999 MILLION",
 /*  55 */ "millions ::= NUMBER MILLION",
 /*  56 */ "millions ::= MILLION",
 /*  57 */ "first_to_999999th ::= thousands first_to_999th",
 /*  58 */ "first_to_999999th ::= thousandths",
 /*  59 */ "first_to_999999th ::= first_to_999th",
 /*  60 */ "thousandths ::= one_to_999 THOUSANDTH",
 /*  61 */ "thousandths ::= one_to_999 THOUSANDTHS",
 /*  62 */ "thousandths ::= NUMBER THOUSANDTH",
 /*  63 */ "thousandths ::= NUMBER THOUSANDTHS",
 /*  64 */ "thousandths ::= THOUSANDTH",
 /*  65 */ "thousandths ::= THOUSANDTHS",
 /*  66 */ "one_to_999999 ::= thousands one_to_999",
 /*  67 */ "one_to_999999 ::= thousands",
 /*  68 */ "one_to_999999 ::= one_to_999",
 /*  69 */ "thousands ::= one_to_999 THOUSAND",
 /*  70 */ "thousands ::= NUMBER THOUSAND",
 /*  71 */ "thousands ::= THOUSAND",
 /*  72 */ "first_to_999th ::= hundreds AND first_to_99th",
 /*  73 */ "first_to_999th ::= hundreds first_to_99th",
 /*  74 */ "first_to_999th ::= hundredths",
 /*  75 */ "first_to_999th ::= AND first_to_99th",
 /*  76 */ "first_to_999th ::= first_to_99th",
 /*  77 */ "hundredths ::= one_to_99 HUNDREDTH",
 /*  78 */ "hundredths ::= one_to_99 HUNDREDTHS",
 /*  79 */ "hundredths ::= NUMBER HUNDREDTH",
 /*  80 */ "hundredths ::= NUMBER HUNDREDTHS",
 /*  81 */ "hundredths ::= HUNDREDTH",
 /*  82 */ "hundredths ::= HUNDREDTHS",
 /*  83 */ "first_to_99th ::= tens first_to_9th",
 /*  84 */ "first_to_99th ::= tenths",
 /*  85 */ "first_to_99th ::= tenth_to_19th",
 /*  86 */ "first_to_99th ::= first_to_9th",
 /*  87 */ "one_to_999 ::= hundreds AND one_to_99",
 /*  88 */ "one_to_999 ::= hundreds one_to_99",
 /*  89 */ "one_to_999 ::= hundreds",
 /*  90 */ "one_to_999 ::= AND one_to_99",
 /*  91 */ "one_to_999 ::= one_to_99",
 /*  92 */ "hundreds ::= one_to_99 HUNDRED",
 /*  93 */ "hundreds ::= NUMBER HUNDRED",
 /*  94 */ "hundreds ::= HUNDRED",
 /*  95 */ "one_to_99 ::= tens one_to_9",
 /*  96 */ "one_to_99 ::= tens",
 /*  97 */ "one_to_99 ::= ten_to_19",
 /*  98 */ "one_to_99 ::= one_to_9",
 /*  99 */ "one_to_9 ::= ONE",
 /* 100 */ "one_to_9 ::= TWO",
 /* 101 */ "one_to_9 ::= THREE",
 /* 102 */ "one_to_9 ::= FOUR",
 /* 103 */ "one_to_9 ::= FIVE",
 /* 104 */ "one_to_9 ::= SIX",
 /* 105 */ "one_to_9 ::= SEVEN",
 /* 106 */ "one_to_9 ::= EIGHT",
 /* 107 */ "one_to_9 ::= NINE",
 /* 108 */ "ten_to_19 ::= TEN",
 /* 109 */ "ten_to_19 ::= ELEVEN",
 /* 110 */ "ten_to_19 ::= TWELVE",
 /* 111 */ "ten_to_19 ::= THIRTEEN",
 /* 112 */ "ten_to_19 ::= FOURTEEN",
 /* 113 */ "ten_to_19 ::= FIFTEEN",
 /* 114 */ "ten_to_19 ::= SIXTEEN",
 /* 115 */ "ten_to_19 ::= SEVENTEEN",
 /* 116 */ "ten_to_19 ::= EIGHTEEN",
 /* 117 */ "ten_to_19 ::= NINETEEN",
 /* 118 */ "tens ::= TWENTY",
 /* 119 */ "tens ::= THIRTY",
 /* 120 */ "tens ::= FORTY",
 /* 121 */ "tens ::= FIFTY",
 /* 122 */ "tens ::= SIXTY",
 /* 123 */ "tens ::= SEVENTY",
 /* 124 */ "tens ::= EIGHTY",
 /* 125 */ "tens ::= NINETY",
 /* 126 */ "first_to_9th ::= FIRST",
 /* 127 */ "first_to_9th ::= FIRSTS",
 /* 128 */ "first_to_9th ::= SECOND",
 /* 129 */ "first_to_9th ::= SECONDS",
 /* 130 */ "first_to_9th ::= THIRD",
 /* 131 */ "first_to_9th ::= THIRDS",
 /* 132 */ "first_to_9th ::= FOURTH",
 /* 133 */ "first_to_9th ::= FOURTHS",
 /* 134 */ "first_to_9th ::= FIFTH",
 /* 135 */ "first_to_9th ::= FIFTHS",
 /* 136 */ "first_to_9th ::= SIXTH",
 /* 137 */ "first_to_9th ::= SIXTHS",
 /* 138 */ "first_to_9th ::= SEVENTH",
 /* 139 */ "first_to_9th ::= SEVENTHS",
 /* 140 */ "first_to_9th ::= EIGHTH",
 /* 141 */ "first_to_9th ::= EIGHTHS",
 /* 142 */ "first_to_9th ::= NINTH",
 /* 143 */ "first_to_9th ::= NINTHS",
 /* 144 */ "tenth_to_19th ::= TENTH",
 /* 145 */ "tenth_to_19th ::= TENTHS",
 /* 146 */ "tenth_to_19th ::= ELEVENTH",
 /* 147 */ "tenth_to_19th ::= ELEVENTHS",
 /* 148 */ "tenth_to_19th ::= TWELFTH",
 /* 149 */ "tenth_to_19th ::= TWELFTHS",
 /* 150 */ "tenth_to_19th ::= THIRTEENTH",
 /* 151 */ "tenth_to_19th ::= THIRTEENTHS",
 /* 152 */ "tenth_to_19th ::= FOURTEENTH",
 /* 153 */ "tenth_to_19th ::= FOURTEENTHS",
 /* 154 */ "tenth_to_19th ::= FIFTEENTH",
 /* 155 */ "tenth_to_19th ::= FIFTEENTHS",
 /* 156 */ "tenth_to_19th ::= SIXTEENTH",
 /* 157 */ "tenth_to_19th ::= SIXTEENTHS",
 /* 158 */ "tenth_to_19th ::= SEVENTEENTH",
 /* 159 */ "tenth_to_19th ::= SEVENTEENTHS",
 /* 160 */ "tenth_to_19th ::= EIGHTEENTH",
 /* 161 */ "tenth_to_19th ::= EIGHTEENTHS",
 /* 162 */ "tenth_to_19th ::= NINETEENTH",
 /* 163 */ "tenth_to_19th ::= NINETEENTHS",
 /* 164 */ "tenths ::= TWENTIETH",
 /* 165 */ "tenths ::= TWENTIETHS",
 /* 166 */ "tenths ::= THIRTIETH",
 /* 167 */ "tenths ::= THIRTIETHS",
 /* 168 */ "tenths ::= FOURTIETH",
 /* 169 */ "tenths ::= FOURTIETHS",
 /* 170 */ "tenths ::= FIFTIETH",
 /* 171 */ "tenths ::= FIFTIETHS",
 /* 172 */ "tenths ::= SIXTIETH",
 /* 173 */ "tenths ::= SIXTIETHS",
 /* 174 */ "tenths ::= SEVENTIETH",
 /* 175 */ "tenths ::= SEVENTIETHS",
 /* 176 */ "tenths ::= EIGHTIETH",
 /* 177 */ "tenths ::= EIGHTIETHS",
 /* 178 */ "tenths ::= NINETIETH",
 /* 179 */ "tenths ::= NINETIETHS",
 /* 180 */ "expr ::=",
 /* 181 */ "identifiers ::= identifiers CHARACTERS",
 /* 182 */ "identifiers ::= CHARACTERS",
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
  { 108, 1 },
  { 108, 1 },
  { 109, 2 },
  { 109, 2 },
  { 110, 3 },
  { 110, 2 },
  { 110, 3 },
  { 110, 2 },
  { 110, 1 },
  { 110, 1 },
  { 110, 1 },
  { 113, 2 },
  { 113, 1 },
  { 113, 1 },
  { 116, 2 },
  { 116, 2 },
  { 116, 2 },
  { 116, 2 },
  { 116, 1 },
  { 116, 1 },
  { 112, 2 },
  { 112, 1 },
  { 112, 1 },
  { 114, 2 },
  { 114, 2 },
  { 114, 1 },
  { 115, 2 },
  { 115, 1 },
  { 115, 1 },
  { 120, 2 },
  { 120, 2 },
  { 120, 2 },
  { 120, 2 },
  { 120, 1 },
  { 120, 1 },
  { 117, 2 },
  { 117, 1 },
  { 117, 1 },
  { 118, 2 },
  { 118, 2 },
  { 118, 1 },
  { 119, 2 },
  { 119, 1 },
  { 119, 1 },
  { 124, 2 },
  { 124, 2 },
  { 124, 2 },
  { 124, 2 },
  { 124, 1 },
  { 124, 1 },
  { 121, 2 },
  { 121, 1 },
  { 121, 1 },
  { 122, 2 },
  { 122, 2 },
  { 122, 1 },
  { 123, 2 },
  { 123, 1 },
  { 123, 1 },
  { 128, 2 },
  { 128, 2 },
  { 128, 2 },
  { 128, 2 },
  { 128, 1 },
  { 128, 1 },
  { 125, 2 },
  { 125, 1 },
  { 125, 1 },
  { 126, 2 },
  { 126, 2 },
  { 126, 1 },
  { 127, 3 },
  { 127, 2 },
  { 127, 1 },
  { 127, 2 },
  { 127, 1 },
  { 132, 2 },
  { 132, 2 },
  { 132, 2 },
  { 132, 2 },
  { 132, 1 },
  { 132, 1 },
  { 131, 2 },
  { 131, 1 },
  { 131, 1 },
  { 131, 1 },
  { 129, 3 },
  { 129, 2 },
  { 129, 1 },
  { 129, 2 },
  { 129, 1 },
  { 130, 2 },
  { 130, 2 },
  { 130, 1 },
  { 133, 2 },
  { 133, 1 },
  { 133, 1 },
  { 133, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 138, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 139, 1 },
  { 134, 1 },
  { 134, 1 },
  { 134, 1 },
  { 134, 1 },
  { 134, 1 },
  { 134, 1 },
  { 134, 1 },
  { 134, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
  { 135, 1 },
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
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
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
  { 108, 0 },
  { 111, 2 },
  { 111, 1 },
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
#line 27 "parser.yy"
{
    doubleToString(&state->result, yymsp[0].minor.yy0.double_value, state->precision);

    switch (yymsp[0].minor.yy0.suffix) {
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
#line 1375 "parser.c"
        break;
      case 1: /* expr ::= sentence */
      case 2: /* expr ::= final_number */ yytestcase(yyruleno==2);
      case 10: /* final_number ::= first_to_999999999999999th */ yytestcase(yyruleno==10);
      case 13: /* first_to_999999999999999th ::= trillionths */ yytestcase(yyruleno==13);
      case 14: /* first_to_999999999999999th ::= first_to_999999999999th */ yytestcase(yyruleno==14);
      case 28: /* first_to_999999999999th ::= billionths */ yytestcase(yyruleno==28);
      case 29: /* first_to_999999999999th ::= first_to_999999999th */ yytestcase(yyruleno==29);
      case 43: /* first_to_999999999th ::= millionths */ yytestcase(yyruleno==43);
      case 44: /* first_to_999999999th ::= first_to_999999th */ yytestcase(yyruleno==44);
      case 58: /* first_to_999999th ::= thousandths */ yytestcase(yyruleno==58);
      case 59: /* first_to_999999th ::= first_to_999th */ yytestcase(yyruleno==59);
      case 74: /* first_to_999th ::= hundredths */ yytestcase(yyruleno==74);
      case 76: /* first_to_999th ::= first_to_99th */ yytestcase(yyruleno==76);
      case 84: /* first_to_99th ::= tenths */ yytestcase(yyruleno==84);
      case 85: /* first_to_99th ::= tenth_to_19th */ yytestcase(yyruleno==85);
      case 86: /* first_to_99th ::= first_to_9th */ yytestcase(yyruleno==86);
#line 60 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1395 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 3: /* sentence ::= identifiers final_number */
      case 75: /* first_to_999th ::= AND first_to_99th */ yytestcase(yyruleno==75);
#line 64 "parser.yy"
{ yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; yymsp[-1].minor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1402 "parser.c"
        break;
      case 4: /* sentence ::= final_number identifiers */
#line 65 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[-1].minor.yy0.suffix; }
#line 1407 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 5: /* final_number ::= one_to_999999999999999 AND_A QUARTER */
#line 67 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.25; }
#line 1413 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 6: /* final_number ::= one_to_999999999999999 QUARTERS */
#line 68 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 4.0; }
#line 1419 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 7: /* final_number ::= one_to_999999999999999 AND_A HALF */
#line 69 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.5; }
#line 1425 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 8: /* final_number ::= one_to_999999999999999 HALVES */
#line 70 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 2.0; }
#line 1431 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 9: /* final_number ::= one_to_999999999999999 */
      case 22: /* one_to_999999999999999 ::= trillions */ yytestcase(yyruleno==22);
      case 23: /* one_to_999999999999999 ::= one_to_999999999999 */ yytestcase(yyruleno==23);
      case 37: /* one_to_999999999999 ::= billions */ yytestcase(yyruleno==37);
      case 38: /* one_to_999999999999 ::= one_to_999999999 */ yytestcase(yyruleno==38);
      case 52: /* one_to_999999999 ::= millions */ yytestcase(yyruleno==52);
      case 53: /* one_to_999999999 ::= one_to_999999 */ yytestcase(yyruleno==53);
      case 67: /* one_to_999999 ::= thousands */ yytestcase(yyruleno==67);
      case 68: /* one_to_999999 ::= one_to_999 */ yytestcase(yyruleno==68);
      case 89: /* one_to_999 ::= hundreds */ yytestcase(yyruleno==89);
      case 91: /* one_to_999 ::= one_to_99 */ yytestcase(yyruleno==91);
      case 96: /* one_to_99 ::= tens */ yytestcase(yyruleno==96);
      case 97: /* one_to_99 ::= ten_to_19 */ yytestcase(yyruleno==97);
      case 98: /* one_to_99 ::= one_to_9 */ yytestcase(yyruleno==98);
#line 71 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1450 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 11: /* final_number ::= ZERO */
#line 73 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 0.0; }
#line 1456 "parser.c"
        break;
      case 12: /* first_to_999999999999999th ::= trillions first_to_999999999999th */
      case 27: /* first_to_999999999999th ::= billions first_to_999999999th */ yytestcase(yyruleno==27);
      case 42: /* first_to_999999999th ::= millions first_to_999999th */ yytestcase(yyruleno==42);
      case 57: /* first_to_999999th ::= thousands first_to_999th */ yytestcase(yyruleno==57);
      case 73: /* first_to_999th ::= hundreds first_to_99th */ yytestcase(yyruleno==73);
      case 83: /* first_to_99th ::= tens first_to_9th */ yytestcase(yyruleno==83);
#line 79 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1466 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 15: /* trillionths ::= one_to_999999999999 TRILLIONTH */
      case 17: /* trillionths ::= NUMBER TRILLIONTH */ yytestcase(yyruleno==17);
#line 83 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1473 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 16: /* trillionths ::= one_to_999999999999 TRILLIONTHS */
      case 18: /* trillionths ::= NUMBER TRILLIONTHS */ yytestcase(yyruleno==18);
#line 84 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; yylhsminor.yy0.suffix = THS; }
#line 1480 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 19: /* trillionths ::= TRILLIONTH */
#line 87 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000000000.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1486 "parser.c"
        break;
      case 20: /* trillionths ::= TRILLIONTHS */
#line 88 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000000000.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1491 "parser.c"
        break;
      case 21: /* one_to_999999999999999 ::= trillions one_to_999999999999 */
      case 36: /* one_to_999999999999 ::= billions one_to_999999999 */ yytestcase(yyruleno==36);
      case 51: /* one_to_999999999 ::= millions one_to_999999 */ yytestcase(yyruleno==51);
      case 66: /* one_to_999999 ::= thousands one_to_999 */ yytestcase(yyruleno==66);
      case 88: /* one_to_999 ::= hundreds one_to_99 */ yytestcase(yyruleno==88);
      case 95: /* one_to_99 ::= tens one_to_9 */ yytestcase(yyruleno==95);
#line 94 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1501 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 24: /* trillions ::= one_to_999999999999 TRILLION */
      case 25: /* trillions ::= NUMBER TRILLION */ yytestcase(yyruleno==25);
#line 98 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; }
#line 1508 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 26: /* trillions ::= TRILLION */
#line 100 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000000000.0; }
#line 1514 "parser.c"
        break;
      case 30: /* billionths ::= one_to_999999999 BILLIONTH */
      case 32: /* billionths ::= NUMBER BILLIONTH */ yytestcase(yyruleno==32);
#line 110 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1520 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 31: /* billionths ::= one_to_999999999 BILLIONTHS */
      case 33: /* billionths ::= NUMBER BILLIONTHS */ yytestcase(yyruleno==33);
#line 111 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; yylhsminor.yy0.suffix = THS; }
#line 1527 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 34: /* billionths ::= BILLIONTH */
#line 114 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000000.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1533 "parser.c"
        break;
      case 35: /* billionths ::= BILLIONTHS */
#line 115 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000000.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1538 "parser.c"
        break;
      case 39: /* billions ::= one_to_999999999 BILLION */
      case 40: /* billions ::= NUMBER BILLION */ yytestcase(yyruleno==40);
#line 125 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; }
#line 1544 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 41: /* billions ::= BILLION */
#line 127 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000000.0; }
#line 1550 "parser.c"
        break;
      case 45: /* millionths ::= one_to_999999 MILLIONTH */
      case 47: /* millionths ::= NUMBER MILLIONTH */ yytestcase(yyruleno==47);
#line 137 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; yylhsminor.yy0.suffix = TH; }
#line 1556 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 46: /* millionths ::= one_to_999999 MILLIONTHS */
      case 48: /* millionths ::= NUMBER MILLIONTHS */ yytestcase(yyruleno==48);
#line 138 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; yylhsminor.yy0.suffix = THS; }
#line 1563 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 49: /* millionths ::= MILLIONTH */
#line 141 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1569 "parser.c"
        break;
      case 50: /* millionths ::= MILLIONTHS */
#line 142 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1574 "parser.c"
        break;
      case 54: /* millions ::= one_to_999999 MILLION */
      case 55: /* millions ::= NUMBER MILLION */ yytestcase(yyruleno==55);
#line 152 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; }
#line 1580 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 56: /* millions ::= MILLION */
#line 154 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000.0; }
#line 1586 "parser.c"
        break;
      case 60: /* thousandths ::= one_to_999 THOUSANDTH */
      case 62: /* thousandths ::= NUMBER THOUSANDTH */ yytestcase(yyruleno==62);
#line 164 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; yylhsminor.yy0.suffix = TH; }
#line 1592 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 61: /* thousandths ::= one_to_999 THOUSANDTHS */
      case 63: /* thousandths ::= NUMBER THOUSANDTHS */ yytestcase(yyruleno==63);
#line 165 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; yylhsminor.yy0.suffix = THS; }
#line 1599 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 64: /* thousandths ::= THOUSANDTH */
#line 168 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1605 "parser.c"
        break;
      case 65: /* thousandths ::= THOUSANDTHS */
#line 169 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1610 "parser.c"
        break;
      case 69: /* thousands ::= one_to_999 THOUSAND */
      case 70: /* thousands ::= NUMBER THOUSAND */ yytestcase(yyruleno==70);
#line 179 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; }
#line 1616 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 71: /* thousands ::= THOUSAND */
#line 181 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000.0; }
#line 1622 "parser.c"
        break;
      case 72: /* first_to_999th ::= hundreds AND first_to_99th */
#line 187 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1627 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 77: /* hundredths ::= one_to_99 HUNDREDTH */
      case 79: /* hundredths ::= NUMBER HUNDREDTH */ yytestcase(yyruleno==79);
#line 193 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; yylhsminor.yy0.suffix = TH; }
#line 1634 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 78: /* hundredths ::= one_to_99 HUNDREDTHS */
      case 80: /* hundredths ::= NUMBER HUNDREDTHS */ yytestcase(yyruleno==80);
#line 194 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; yylhsminor.yy0.suffix = THS; }
#line 1641 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 81: /* hundredths ::= HUNDREDTH */
#line 197 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 100.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1647 "parser.c"
        break;
      case 82: /* hundredths ::= HUNDREDTHS */
#line 198 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 100.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1652 "parser.c"
        break;
      case 87: /* one_to_999 ::= hundreds AND one_to_99 */
#line 209 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1657 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 90: /* one_to_999 ::= AND one_to_99 */
#line 212 "parser.yy"
{ yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1663 "parser.c"
        break;
      case 92: /* hundreds ::= one_to_99 HUNDRED */
      case 93: /* hundreds ::= NUMBER HUNDRED */ yytestcase(yyruleno==93);
#line 215 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; }
#line 1669 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 94: /* hundreds ::= HUNDRED */
#line 217 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 100.0; }
#line 1675 "parser.c"
        break;
      case 99: /* one_to_9 ::= ONE */
#line 228 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1.0; }
#line 1680 "parser.c"
        break;
      case 100: /* one_to_9 ::= TWO */
#line 229 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 2.0; }
#line 1685 "parser.c"
        break;
      case 101: /* one_to_9 ::= THREE */
#line 230 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 3.0; }
#line 1690 "parser.c"
        break;
      case 102: /* one_to_9 ::= FOUR */
#line 231 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 4.0; }
#line 1695 "parser.c"
        break;
      case 103: /* one_to_9 ::= FIVE */
#line 232 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 5.0; }
#line 1700 "parser.c"
        break;
      case 104: /* one_to_9 ::= SIX */
#line 233 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 6.0; }
#line 1705 "parser.c"
        break;
      case 105: /* one_to_9 ::= SEVEN */
#line 234 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 7.0; }
#line 1710 "parser.c"
        break;
      case 106: /* one_to_9 ::= EIGHT */
#line 235 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 8.0; }
#line 1715 "parser.c"
        break;
      case 107: /* one_to_9 ::= NINE */
#line 236 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 9.0; }
#line 1720 "parser.c"
        break;
      case 108: /* ten_to_19 ::= TEN */
#line 238 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 10.0; }
#line 1725 "parser.c"
        break;
      case 109: /* ten_to_19 ::= ELEVEN */
#line 239 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 11.0; }
#line 1730 "parser.c"
        break;
      case 110: /* ten_to_19 ::= TWELVE */
#line 240 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 12.0; }
#line 1735 "parser.c"
        break;
      case 111: /* ten_to_19 ::= THIRTEEN */
#line 241 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 13.0; }
#line 1740 "parser.c"
        break;
      case 112: /* ten_to_19 ::= FOURTEEN */
#line 242 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 14.0; }
#line 1745 "parser.c"
        break;
      case 113: /* ten_to_19 ::= FIFTEEN */
#line 243 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 15.0; }
#line 1750 "parser.c"
        break;
      case 114: /* ten_to_19 ::= SIXTEEN */
#line 244 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 16.0; }
#line 1755 "parser.c"
        break;
      case 115: /* ten_to_19 ::= SEVENTEEN */
#line 245 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 17.0; }
#line 1760 "parser.c"
        break;
      case 116: /* ten_to_19 ::= EIGHTEEN */
#line 246 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 18.0; }
#line 1765 "parser.c"
        break;
      case 117: /* ten_to_19 ::= NINETEEN */
#line 247 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 19.0; }
#line 1770 "parser.c"
        break;
      case 118: /* tens ::= TWENTY */
#line 249 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 20.0; }
#line 1775 "parser.c"
        break;
      case 119: /* tens ::= THIRTY */
#line 250 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 30.0; }
#line 1780 "parser.c"
        break;
      case 120: /* tens ::= FORTY */
#line 251 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 40.0; }
#line 1785 "parser.c"
        break;
      case 121: /* tens ::= FIFTY */
#line 252 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 50.0; }
#line 1790 "parser.c"
        break;
      case 122: /* tens ::= SIXTY */
#line 253 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 60.0; }
#line 1795 "parser.c"
        break;
      case 123: /* tens ::= SEVENTY */
#line 254 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 70.0; }
#line 1800 "parser.c"
        break;
      case 124: /* tens ::= EIGHTY */
#line 255 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 80.0; }
#line 1805 "parser.c"
        break;
      case 125: /* tens ::= NINETY */
#line 256 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 90.0; }
#line 1810 "parser.c"
        break;
      case 126: /* first_to_9th ::= FIRST */
#line 258 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1.0; yymsp[0].minor.yy0.suffix = ST; }
#line 1815 "parser.c"
        break;
      case 127: /* first_to_9th ::= FIRSTS */
#line 259 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1.0; yymsp[0].minor.yy0.suffix = STS; }
#line 1820 "parser.c"
        break;
      case 128: /* first_to_9th ::= SECOND */
#line 260 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 2.0; yymsp[0].minor.yy0.suffix = ND; }
#line 1825 "parser.c"
        break;
      case 129: /* first_to_9th ::= SECONDS */
#line 261 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 2.0; yymsp[0].minor.yy0.suffix = NDS; }
#line 1830 "parser.c"
        break;
      case 130: /* first_to_9th ::= THIRD */
#line 262 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 3.0; yymsp[0].minor.yy0.suffix = RD; }
#line 1835 "parser.c"
        break;
      case 131: /* first_to_9th ::= THIRDS */
#line 263 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 3.0; yymsp[0].minor.yy0.suffix = RDS; }
#line 1840 "parser.c"
        break;
      case 132: /* first_to_9th ::= FOURTH */
#line 264 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 4.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1845 "parser.c"
        break;
      case 133: /* first_to_9th ::= FOURTHS */
#line 265 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 4.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1850 "parser.c"
        break;
      case 134: /* first_to_9th ::= FIFTH */
#line 266 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 5.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1855 "parser.c"
        break;
      case 135: /* first_to_9th ::= FIFTHS */
#line 267 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 5.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1860 "parser.c"
        break;
      case 136: /* first_to_9th ::= SIXTH */
#line 268 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 6.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1865 "parser.c"
        break;
      case 137: /* first_to_9th ::= SIXTHS */
#line 269 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 6.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1870 "parser.c"
        break;
      case 138: /* first_to_9th ::= SEVENTH */
#line 270 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 7.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1875 "parser.c"
        break;
      case 139: /* first_to_9th ::= SEVENTHS */
#line 271 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 7.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1880 "parser.c"
        break;
      case 140: /* first_to_9th ::= EIGHTH */
#line 272 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 8.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1885 "parser.c"
        break;
      case 141: /* first_to_9th ::= EIGHTHS */
#line 273 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 8.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1890 "parser.c"
        break;
      case 142: /* first_to_9th ::= NINTH */
#line 274 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 9.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1895 "parser.c"
        break;
      case 143: /* first_to_9th ::= NINTHS */
#line 275 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 9.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1900 "parser.c"
        break;
      case 144: /* tenth_to_19th ::= TENTH */
#line 277 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 10.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1905 "parser.c"
        break;
      case 145: /* tenth_to_19th ::= TENTHS */
#line 278 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 10.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1910 "parser.c"
        break;
      case 146: /* tenth_to_19th ::= ELEVENTH */
#line 279 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 11.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1915 "parser.c"
        break;
      case 147: /* tenth_to_19th ::= ELEVENTHS */
#line 280 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 11.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1920 "parser.c"
        break;
      case 148: /* tenth_to_19th ::= TWELFTH */
#line 281 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 12.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1925 "parser.c"
        break;
      case 149: /* tenth_to_19th ::= TWELFTHS */
#line 282 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 12.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1930 "parser.c"
        break;
      case 150: /* tenth_to_19th ::= THIRTEENTH */
#line 283 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 13.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1935 "parser.c"
        break;
      case 151: /* tenth_to_19th ::= THIRTEENTHS */
#line 284 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 13.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1940 "parser.c"
        break;
      case 152: /* tenth_to_19th ::= FOURTEENTH */
#line 285 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 14.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1945 "parser.c"
        break;
      case 153: /* tenth_to_19th ::= FOURTEENTHS */
#line 286 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 14.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1950 "parser.c"
        break;
      case 154: /* tenth_to_19th ::= FIFTEENTH */
#line 287 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 15.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1955 "parser.c"
        break;
      case 155: /* tenth_to_19th ::= FIFTEENTHS */
#line 288 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 15.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1960 "parser.c"
        break;
      case 156: /* tenth_to_19th ::= SIXTEENTH */
#line 289 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 16.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1965 "parser.c"
        break;
      case 157: /* tenth_to_19th ::= SIXTEENTHS */
#line 290 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 16.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1970 "parser.c"
        break;
      case 158: /* tenth_to_19th ::= SEVENTEENTH */
#line 291 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 17.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1975 "parser.c"
        break;
      case 159: /* tenth_to_19th ::= SEVENTEENTHS */
#line 292 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 17.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1980 "parser.c"
        break;
      case 160: /* tenth_to_19th ::= EIGHTEENTH */
#line 293 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 18.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1985 "parser.c"
        break;
      case 161: /* tenth_to_19th ::= EIGHTEENTHS */
#line 294 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 18.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1990 "parser.c"
        break;
      case 162: /* tenth_to_19th ::= NINETEENTH */
#line 295 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 19.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1995 "parser.c"
        break;
      case 163: /* tenth_to_19th ::= NINETEENTHS */
#line 296 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 19.0; yymsp[0].minor.yy0.suffix = THS; }
#line 2000 "parser.c"
        break;
      case 164: /* tenths ::= TWENTIETH */
#line 298 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 20.0; yymsp[0].minor.yy0.suffix = TH; }
#line 2005 "parser.c"
        break;
      case 165: /* tenths ::= TWENTIETHS */
#line 299 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 20.0; yymsp[0].minor.yy0.suffix = THS; }
#line 2010 "parser.c"
        break;
      case 166: /* tenths ::= THIRTIETH */
#line 300 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 30.0; yymsp[0].minor.yy0.suffix = TH; }
#line 2015 "parser.c"
        break;
      case 167: /* tenths ::= THIRTIETHS */
#line 301 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 30.0; yymsp[0].minor.yy0.suffix = THS; }
#line 2020 "parser.c"
        break;
      case 168: /* tenths ::= FOURTIETH */
#line 302 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 40.0; yymsp[0].minor.yy0.suffix = TH; }
#line 2025 "parser.c"
        break;
      case 169: /* tenths ::= FOURTIETHS */
#line 303 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 40.0; yymsp[0].minor.yy0.suffix = THS; }
#line 2030 "parser.c"
        break;
      case 170: /* tenths ::= FIFTIETH */
#line 304 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 50.0; yymsp[0].minor.yy0.suffix = TH; }
#line 2035 "parser.c"
        break;
      case 171: /* tenths ::= FIFTIETHS */
#line 305 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 50.0; yymsp[0].minor.yy0.suffix = THS; }
#line 2040 "parser.c"
        break;
      case 172: /* tenths ::= SIXTIETH */
#line 306 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 60.0; yymsp[0].minor.yy0.suffix = TH; }
#line 2045 "parser.c"
        break;
      case 173: /* tenths ::= SIXTIETHS */
#line 307 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 60.0; yymsp[0].minor.yy0.suffix = THS; }
#line 2050 "parser.c"
        break;
      case 174: /* tenths ::= SEVENTIETH */
#line 308 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 70.0; yymsp[0].minor.yy0.suffix = TH; }
#line 2055 "parser.c"
        break;
      case 175: /* tenths ::= SEVENTIETHS */
#line 309 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 70.0; yymsp[0].minor.yy0.suffix = THS; }
#line 2060 "parser.c"
        break;
      case 176: /* tenths ::= EIGHTIETH */
#line 310 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 80.0; yymsp[0].minor.yy0.suffix = TH; }
#line 2065 "parser.c"
        break;
      case 177: /* tenths ::= EIGHTIETHS */
#line 311 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 80.0; yymsp[0].minor.yy0.suffix = THS; }
#line 2070 "parser.c"
        break;
      case 178: /* tenths ::= NINETIETH */
#line 312 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 90.0; yymsp[0].minor.yy0.suffix = TH; }
#line 2075 "parser.c"
        break;
      case 179: /* tenths ::= NINETIETHS */
#line 313 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 90.0; yymsp[0].minor.yy0.suffix = THS; }
#line 2080 "parser.c"
        break;
      default:
      /* (180) expr ::= (OPTIMIZED OUT) */ assert(yyruleno!=180);
      /* (181) identifiers ::= identifiers CHARACTERS */ yytestcase(yyruleno==181);
      /* (182) identifiers ::= CHARACTERS */ yytestcase(yyruleno==182);
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
#line 21 "parser.yy"

    fprintf(stderr,"Giving up.  Parser is hopelessly lost...\n");
#line 2129 "parser.c"
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
#line 17 "parser.yy"

    fprintf(stderr, "Syntax error\n");
#line 2149 "parser.c"
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
