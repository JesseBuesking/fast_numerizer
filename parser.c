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
#define YYNSTATE             29
#define YYNRULE              186
#define YY_MAX_SHIFT         28
#define YY_MIN_SHIFTREDUCE   196
#define YY_MAX_SHIFTREDUCE   381
#define YY_MIN_REDUCE        382
#define YY_MAX_REDUCE        567
#define YY_ERROR_ACTION      568
#define YY_ACCEPT_ACTION     569
#define YY_NO_ACTION         570
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
#define YY_ACTTAB_COUNT (1057)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   381,  213,  214,  203,  222,  205,  209,  217,  218,   15,
 /*    10 */   224,  232,  233,  239,  247,  248,  254,  262,  263,  269,
 /*    20 */     9,  279,  280,  292,  297,  298,  299,  300,  301,  302,
 /*    30 */   303,  304,  305,  306,  307,  308,  309,  310,  311,  312,
 /*    40 */   313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
 /*    50 */   323,  324,  325,  326,  327,  328,  329,  330,  331,  332,
 /*    60 */   333,  334,  335,  336,  337,  338,  339,  340,  341,  342,
 /*    70 */   343,  344,  345,  346,  347,  348,  349,  350,  351,  352,
 /*    80 */   353,  354,  355,  356,  357,  358,  359,  360,  361,  362,
 /*    90 */   363,  364,  365,  366,  367,  368,  369,  370,  371,  372,
 /*   100 */   373,  374,  375,  376,  377,  380,  228,  229,  237,  381,
 /*   110 */   380,  209,  217,  218,   15,  224,  232,  233,  239,  247,
 /*   120 */   248,  254,  262,  263,  269,    9,  279,  280,  292,  297,
 /*   130 */   298,  299,  300,  301,  302,  303,  304,  305,  306,  307,
 /*   140 */   308,  309,  310,  311,  312,  313,  314,  315,  316,  317,
 /*   150 */   318,  319,  320,  321,  322,  323,  324,  325,  326,  327,
 /*   160 */   328,  329,  330,  331,  332,  333,  334,  335,  336,  337,
 /*   170 */   338,  339,  340,  341,  342,  343,  344,  345,  346,  347,
 /*   180 */   348,  349,  350,  351,  352,  353,  354,  355,  356,  357,
 /*   190 */   358,  359,  360,  361,  362,  363,  364,  365,  366,  367,
 /*   200 */   368,  369,  370,  371,  372,  373,  374,  375,  376,  377,
 /*   210 */    16,   27,  232,  233,  239,  247,  248,  254,  262,  263,
 /*   220 */   269,    9,  279,  280,  292,  297,  298,  299,  300,  301,
 /*   230 */   302,  303,  304,  305,  306,  307,  308,  309,  310,  311,
 /*   240 */   312,  313,  314,  315,  316,  317,  318,  319,  320,  321,
 /*   250 */   322,  323,  324,  325,  326,  327,  328,  329,  330,  331,
 /*   260 */   332,  333,  334,  335,  336,  337,  338,  339,  340,  341,
 /*   270 */   342,  343,  344,  345,  346,  347,  348,  349,  350,  351,
 /*   280 */   352,  353,  354,  355,  356,  357,  358,  359,  360,  361,
 /*   290 */   362,  363,  364,  365,  366,  367,  368,  369,  370,  371,
 /*   300 */   372,  373,  374,  375,  376,  377,   17,  243,  244,  252,
 /*   310 */     1,  247,  248,  254,  262,  263,  269,    9,  279,  280,
 /*   320 */   292,  297,  298,  299,  300,  301,  302,  303,  304,  305,
 /*   330 */   306,  307,  308,  309,  310,  311,  312,  313,  314,  315,
 /*   340 */   316,  317,  318,  319,  320,  321,  322,  323,  324,  325,
 /*   350 */   326,  327,  328,  329,  330,  331,  332,  333,  334,  335,
 /*   360 */   336,  337,  338,  339,  340,  341,  342,  343,  344,  345,
 /*   370 */   346,  347,  348,  349,  350,  351,  352,  353,  354,  355,
 /*   380 */   356,  357,  358,  359,  360,  361,  362,  363,  364,  365,
 /*   390 */   366,  367,  368,  369,  370,  371,  372,  373,  374,  375,
 /*   400 */   376,  377,   18,  260,  261,  268,    3,  277,  278,  291,
 /*   410 */   262,  263,  269,    9,  279,  280,  292,  297,  298,  299,
 /*   420 */   300,  301,  302,  303,  304,  305,  306,  307,  308,  309,
 /*   430 */   310,  311,  312,  313,  314,  315,  316,  317,  318,  319,
 /*   440 */   320,  321,  322,  323,  324,  325,  326,  327,  328,  329,
 /*   450 */   330,  331,  332,  333,  334,  335,  336,  337,  338,  339,
 /*   460 */   340,  341,  342,  343,  344,  345,  346,  347,  348,  349,
 /*   470 */   350,  351,  352,  353,  354,  355,  356,  357,  358,  359,
 /*   480 */   360,  361,  362,  363,  364,  365,  366,  367,  368,  369,
 /*   490 */   370,  371,  372,  373,  374,  375,  376,  377,   23,  245,
 /*   500 */   246,  253,  260,  261,  268,  382,  277,  278,  291,    9,
 /*   510 */   279,  280,  292,  297,  298,  299,  300,  301,  302,  303,
 /*   520 */   304,  305,  306,  307,  308,  309,  310,  311,  312,  313,
 /*   530 */   314,  315,  316,  317,  318,  319,  320,  321,  322,  323,
 /*   540 */   324,  325,  326,  327,  328,  329,  330,  331,  332,  333,
 /*   550 */   334,  335,  336,  337,  338,  339,  340,  341,  342,  343,
 /*   560 */   344,  345,  346,  347,  348,  349,  350,  351,  352,  353,
 /*   570 */   354,  355,  356,  357,  358,  359,  360,  361,  362,  363,
 /*   580 */   364,  365,  366,  367,  368,  369,  370,  371,  372,  373,
 /*   590 */   374,  375,  376,  377,   10,  258,  259,  267,  297,  298,
 /*   600 */   299,  300,  301,  302,  303,  304,  305,  306,  307,  308,
 /*   610 */   309,  310,  311,  312,  313,  314,  315,  316,  317,  318,
 /*   620 */   319,  320,  321,  322,  323,  324,  325,  326,  327,  328,
 /*   630 */   329,  330,  331,  332,  333,  334,  335,  336,  337,  338,
 /*   640 */   339,  340,  341,  342,  343,  344,  345,  346,  347,  348,
 /*   650 */   349,  350,  351,  352,  353,  354,  355,  356,  357,  358,
 /*   660 */   359,  360,  361,  362,  363,  364,  365,  366,  367,  368,
 /*   670 */   369,  370,  371,  372,  373,  374,  375,  376,  377,  297,
 /*   680 */   298,  299,  300,  301,  302,  303,  304,  305,  306,  307,
 /*   690 */   308,  309,  310,  311,  312,  313,  314,  315,  316,  317,
 /*   700 */   318,  319,  320,  321,  322,  323,  324,  325,  326,  327,
 /*   710 */   328,  329,  330,  331,  332,  333,  334,  335,  336,  337,
 /*   720 */   338,  339,  340,  341,  342,  343,  344,  345,  346,  347,
 /*   730 */   348,  349,  350,  351,  352,  353,  354,  355,  356,  357,
 /*   740 */   358,  359,  360,  361,  362,  363,  364,  365,  366,  367,
 /*   750 */   368,  369,  370,  371,  372,  373,  374,  375,  376,  377,
 /*   760 */   569,   28,   28,   14,    2,   25,  208,    4,  212,  211,
 /*   770 */    19,    5,  227,  226,   20,    6,  242,  241,   21,    7,
 /*   780 */   257,  256,   22,    8,  274,  272,   24,   11,  284,  282,
 /*   790 */   283,  296,  295,   12,  384,   25,  208,    4,  212,  211,
 /*   800 */    19,    5,  227,  226,   20,    6,  242,  241,   21,    7,
 /*   810 */   257,  256,   22,    8,  274,  272,   24,   11,  284,  282,
 /*   820 */   283,  296,  295,   13,  384,   25,  208,    4,  212,  211,
 /*   830 */    19,    5,  227,  226,   20,    6,  242,  241,   21,    7,
 /*   840 */   257,  256,   22,    8,  274,  272,   24,   11,  284,  282,
 /*   850 */   283,  296,  295,  198,  384,   25,  208,    4,  212,  211,
 /*   860 */    19,    5,  227,  226,   20,    6,  242,  241,   21,    7,
 /*   870 */   257,  256,   22,    8,  274,  272,   24,   11,  284,  282,
 /*   880 */   283,  296,  295,  297,  298,  299,  300,  301,  302,  303,
 /*   890 */   304,  305,  240,  384,  249,    7,  257,  256,   22,    8,
 /*   900 */   274,  272,   24,   11,  284,  282,  283,  296,  295,  384,
 /*   910 */   324,  325,  326,  327,  328,  329,  330,  331,  332,  333,
 /*   920 */   334,  335,  336,  337,  338,  339,  340,  341,  210,  384,
 /*   930 */   219,    5,  227,  226,   20,    6,  242,  241,   21,    7,
 /*   940 */   257,  256,   22,    8,  274,  272,   24,   11,  284,  282,
 /*   950 */   283,  296,  295,  225,  384,  234,    6,  242,  241,   21,
 /*   960 */     7,  257,  256,   22,    8,  274,  272,   24,   11,  284,
 /*   970 */   282,  283,  296,  295,  215,  216,  384,  223,  230,  231,
 /*   980 */   238,  245,  246,  253,  260,  261,  268,  384,  277,  278,
 /*   990 */   291,  255,  384,  264,    8,  274,  272,   24,   11,  284,
 /*  1000 */   282,  283,  296,  295,  230,  231,  238,  245,  246,  253,
 /*  1010 */   260,  261,  268,  384,  277,  278,  291,  271,  384,  286,
 /*  1020 */    11,  284,  282,  283,  296,  295,  273,  384,  288,   11,
 /*  1030 */   284,  282,  283,  296,  295,  270,  384,  285,   11,  284,
 /*  1040 */   282,  283,  296,  295,  277,  278,  291,  275,  276,  290,
 /*  1050 */    26,  384,  204,  281,  206,  384,  293,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    8,    9,    3,   11,    5,    7,    8,    9,   10,
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
 /*   110 */     1,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   120 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   130 */    26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
 /*   140 */    36,   37,   38,   39,   40,   41,   42,   43,   44,   45,
 /*   150 */    46,   47,   48,   49,   50,   51,   52,   53,   54,   55,
 /*   160 */    56,   57,   58,   59,   60,   61,   62,   63,   64,   65,
 /*   170 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   180 */    76,   77,   78,   79,   80,   81,   82,   83,   84,   85,
 /*   190 */    86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
 /*   200 */    96,   97,   98,   99,  100,  101,  102,  103,  104,  105,
 /*   210 */    10,  111,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   220 */    20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   230 */    30,   31,   32,   33,   34,   35,   36,   37,   38,   39,
 /*   240 */    40,   41,   42,   43,   44,   45,   46,   47,   48,   49,
 /*   250 */    50,   51,   52,   53,   54,   55,   56,   57,   58,   59,
 /*   260 */    60,   61,   62,   63,   64,   65,   66,   67,   68,   69,
 /*   270 */    70,   71,   72,   73,   74,   75,   76,   77,   78,   79,
 /*   280 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   89,
 /*   290 */    90,   91,   92,   93,   94,   95,   96,   97,   98,   99,
 /*   300 */   100,  101,  102,  103,  104,  105,   10,   15,   16,   17,
 /*   310 */   111,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   320 */    24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
 /*   330 */    34,   35,   36,   37,   38,   39,   40,   41,   42,   43,
 /*   340 */    44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
 /*   350 */    54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
 /*   360 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   370 */    74,   75,   76,   77,   78,   79,   80,   81,   82,   83,
 /*   380 */    84,   85,   86,   87,   88,   89,   90,   91,   92,   93,
 /*   390 */    94,   95,   96,   97,   98,   99,  100,  101,  102,  103,
 /*   400 */   104,  105,   10,   18,   19,   20,  111,   22,   23,   24,
 /*   410 */    18,   19,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   420 */    28,   29,   30,   31,   32,   33,   34,   35,   36,   37,
 /*   430 */    38,   39,   40,   41,   42,   43,   44,   45,   46,   47,
 /*   440 */    48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
 /*   450 */    58,   59,   60,   61,   62,   63,   64,   65,   66,   67,
 /*   460 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*   470 */    78,   79,   80,   81,   82,   83,   84,   85,   86,   87,
 /*   480 */    88,   89,   90,   91,   92,   93,   94,   95,   96,   97,
 /*   490 */    98,   99,  100,  101,  102,  103,  104,  105,   10,   15,
 /*   500 */    16,   17,   18,   19,   20,    0,   22,   23,   24,   21,
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
 /*   790 */   137,  138,  139,  110,  140,  112,  113,  114,  115,  116,
 /*   800 */   117,  118,  119,  120,  121,  122,  123,  124,  125,  126,
 /*   810 */   127,  128,  129,  130,  131,  132,  133,  134,  135,  136,
 /*   820 */   137,  138,  139,  110,  140,  112,  113,  114,  115,  116,
 /*   830 */   117,  118,  119,  120,  121,  122,  123,  124,  125,  126,
 /*   840 */   127,  128,  129,  130,  131,  132,  133,  134,  135,  136,
 /*   850 */   137,  138,  139,  110,  140,  112,  113,  114,  115,  116,
 /*   860 */   117,  118,  119,  120,  121,  122,  123,  124,  125,  126,
 /*   870 */   127,  128,  129,  130,  131,  132,  133,  134,  135,  136,
 /*   880 */   137,  138,  139,   25,   26,   27,   28,   29,   30,   31,
 /*   890 */    32,   33,  123,  140,  125,  126,  127,  128,  129,  130,
 /*   900 */   131,  132,  133,  134,  135,  136,  137,  138,  139,  140,
 /*   910 */    52,   53,   54,   55,   56,   57,   58,   59,   60,   61,
 /*   920 */    62,   63,   64,   65,   66,   67,   68,   69,  115,  140,
 /*   930 */   117,  118,  119,  120,  121,  122,  123,  124,  125,  126,
 /*   940 */   127,  128,  129,  130,  131,  132,  133,  134,  135,  136,
 /*   950 */   137,  138,  139,  119,  140,  121,  122,  123,  124,  125,
 /*   960 */   126,  127,  128,  129,  130,  131,  132,  133,  134,  135,
 /*   970 */   136,  137,  138,  139,    8,    9,  140,   11,   12,   13,
 /*   980 */    14,   15,   16,   17,   18,   19,   20,  140,   22,   23,
 /*   990 */    24,  127,  140,  129,  130,  131,  132,  133,  134,  135,
 /*  1000 */   136,  137,  138,  139,   12,   13,   14,   15,   16,   17,
 /*  1010 */    18,   19,   20,  140,   22,   23,   24,  131,  140,  133,
 /*  1020 */   134,  135,  136,  137,  138,  139,  131,  140,  133,  134,
 /*  1030 */   135,  136,  137,  138,  139,  131,  140,  133,  134,  135,
 /*  1040 */   136,  137,  138,  139,   22,   23,   24,   22,   23,   24,
 /*  1050 */     2,  140,    4,  135,    6,  140,  138,
};
#define YY_SHIFT_USE_DFLT (1057)
#define YY_SHIFT_COUNT    (28)
#define YY_SHIFT_MIN      (-7)
#define YY_SHIFT_MAX      (1048)
static const short yy_shift_ofst[] = {
 /*     0 */    -1,  104,  104,  104,  200,  296,  392,  488,  573,  654,
 /*    10 */   654,  858,  108,  108,  108,  966,  992,  484,  385,   -7,
 /*    20 */    94,  292,  577, 1022, 1025, 1048,    0,  109,  505,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (14)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (918)
static const short yy_reduce_ofst[] = {
 /*     0 */   653,  683,  713,  743,  813,  834,  769,  864,  886,  895,
 /*    10 */   904,  918,  100,  199,  295,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   565,  386,  568,  388,  406,  421,  436,  451,  473,  568,
 /*    10 */   568,  480,  568,  387,  383,  568,  568,  568,  568,  407,
 /*    20 */   422,  437,  452,  568,  475,  393,  568,  385,  568,
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
 /*   1 */ "expr ::= final_number",
 /*   2 */ "sentence ::= final_number identifiers final_number",
 /*   3 */ "sentence ::= identifiers final_number identifiers final_number identifiers",
 /*   4 */ "sentence ::= identifiers final_number identifiers",
 /*   5 */ "sentence ::= identifiers final_number",
 /*   6 */ "sentence ::= final_number identifiers",
 /*   7 */ "final_number ::= one_to_999999999999999 AND_A QUARTER",
 /*   8 */ "final_number ::= one_to_999999999999999 QUARTERS",
 /*   9 */ "final_number ::= one_to_999999999999999 AND_A HALF",
 /*  10 */ "final_number ::= one_to_999999999999999 HALVES",
 /*  11 */ "final_number ::= one_to_999999999999999",
 /*  12 */ "final_number ::= first_to_999999999999999th",
 /*  13 */ "final_number ::= ZERO",
 /*  14 */ "first_to_999999999999999th ::= trillions first_to_999999999999th",
 /*  15 */ "first_to_999999999999999th ::= trillionths",
 /*  16 */ "first_to_999999999999999th ::= first_to_999999999999th",
 /*  17 */ "trillionths ::= one_to_999999999999 TRILLIONTH",
 /*  18 */ "trillionths ::= one_to_999999999999 TRILLIONTHS",
 /*  19 */ "trillionths ::= NUMBER TRILLIONTH",
 /*  20 */ "trillionths ::= NUMBER TRILLIONTHS",
 /*  21 */ "trillionths ::= TRILLIONTH",
 /*  22 */ "trillionths ::= TRILLIONTHS",
 /*  23 */ "one_to_999999999999999 ::= trillions one_to_999999999999",
 /*  24 */ "one_to_999999999999999 ::= trillions",
 /*  25 */ "one_to_999999999999999 ::= one_to_999999999999",
 /*  26 */ "trillions ::= one_to_999999999999 TRILLION",
 /*  27 */ "trillions ::= NUMBER TRILLION",
 /*  28 */ "trillions ::= TRILLION",
 /*  29 */ "first_to_999999999999th ::= billions first_to_999999999th",
 /*  30 */ "first_to_999999999999th ::= billionths",
 /*  31 */ "first_to_999999999999th ::= first_to_999999999th",
 /*  32 */ "billionths ::= one_to_999999999 BILLIONTH",
 /*  33 */ "billionths ::= one_to_999999999 BILLIONTHS",
 /*  34 */ "billionths ::= NUMBER BILLIONTH",
 /*  35 */ "billionths ::= NUMBER BILLIONTHS",
 /*  36 */ "billionths ::= BILLIONTH",
 /*  37 */ "billionths ::= BILLIONTHS",
 /*  38 */ "one_to_999999999999 ::= billions one_to_999999999",
 /*  39 */ "one_to_999999999999 ::= billions",
 /*  40 */ "one_to_999999999999 ::= one_to_999999999",
 /*  41 */ "billions ::= one_to_999999999 BILLION",
 /*  42 */ "billions ::= NUMBER BILLION",
 /*  43 */ "billions ::= BILLION",
 /*  44 */ "first_to_999999999th ::= millions first_to_999999th",
 /*  45 */ "first_to_999999999th ::= millionths",
 /*  46 */ "first_to_999999999th ::= first_to_999999th",
 /*  47 */ "millionths ::= one_to_999999 MILLIONTH",
 /*  48 */ "millionths ::= one_to_999999 MILLIONTHS",
 /*  49 */ "millionths ::= NUMBER MILLIONTH",
 /*  50 */ "millionths ::= NUMBER MILLIONTHS",
 /*  51 */ "millionths ::= MILLIONTH",
 /*  52 */ "millionths ::= MILLIONTHS",
 /*  53 */ "one_to_999999999 ::= millions one_to_999999",
 /*  54 */ "one_to_999999999 ::= millions",
 /*  55 */ "one_to_999999999 ::= one_to_999999",
 /*  56 */ "millions ::= one_to_999999 MILLION",
 /*  57 */ "millions ::= NUMBER MILLION",
 /*  58 */ "millions ::= MILLION",
 /*  59 */ "first_to_999999th ::= thousands first_to_999th",
 /*  60 */ "first_to_999999th ::= thousandths",
 /*  61 */ "first_to_999999th ::= first_to_999th",
 /*  62 */ "thousandths ::= one_to_999 THOUSANDTH",
 /*  63 */ "thousandths ::= one_to_999 THOUSANDTHS",
 /*  64 */ "thousandths ::= NUMBER THOUSANDTH",
 /*  65 */ "thousandths ::= NUMBER THOUSANDTHS",
 /*  66 */ "thousandths ::= THOUSANDTH",
 /*  67 */ "thousandths ::= THOUSANDTHS",
 /*  68 */ "one_to_999999 ::= thousands one_to_999",
 /*  69 */ "one_to_999999 ::= thousands",
 /*  70 */ "one_to_999999 ::= one_to_999",
 /*  71 */ "thousands ::= one_to_999 THOUSAND",
 /*  72 */ "thousands ::= NUMBER THOUSAND",
 /*  73 */ "thousands ::= THOUSAND",
 /*  74 */ "first_to_999th ::= hundreds AND first_to_99th",
 /*  75 */ "first_to_999th ::= hundreds first_to_99th",
 /*  76 */ "first_to_999th ::= hundredths",
 /*  77 */ "first_to_999th ::= AND first_to_99th",
 /*  78 */ "first_to_999th ::= first_to_99th",
 /*  79 */ "hundredths ::= one_to_99 HUNDREDTH",
 /*  80 */ "hundredths ::= one_to_99 HUNDREDTHS",
 /*  81 */ "hundredths ::= NUMBER HUNDREDTH",
 /*  82 */ "hundredths ::= NUMBER HUNDREDTHS",
 /*  83 */ "hundredths ::= HUNDREDTH",
 /*  84 */ "hundredths ::= HUNDREDTHS",
 /*  85 */ "first_to_99th ::= tens first_to_9th",
 /*  86 */ "first_to_99th ::= tenths",
 /*  87 */ "first_to_99th ::= tenth_to_19th",
 /*  88 */ "first_to_99th ::= first_to_9th",
 /*  89 */ "one_to_999 ::= hundreds AND one_to_99",
 /*  90 */ "one_to_999 ::= hundreds one_to_99",
 /*  91 */ "one_to_999 ::= hundreds",
 /*  92 */ "one_to_999 ::= AND one_to_99",
 /*  93 */ "one_to_999 ::= one_to_99",
 /*  94 */ "hundreds ::= one_to_99 HUNDRED",
 /*  95 */ "hundreds ::= NUMBER HUNDRED",
 /*  96 */ "hundreds ::= HUNDRED",
 /*  97 */ "one_to_99 ::= tens one_to_9",
 /*  98 */ "one_to_99 ::= tens",
 /*  99 */ "one_to_99 ::= ten_to_19",
 /* 100 */ "one_to_99 ::= one_to_9",
 /* 101 */ "one_to_9 ::= ONE",
 /* 102 */ "one_to_9 ::= TWO",
 /* 103 */ "one_to_9 ::= THREE",
 /* 104 */ "one_to_9 ::= FOUR",
 /* 105 */ "one_to_9 ::= FIVE",
 /* 106 */ "one_to_9 ::= SIX",
 /* 107 */ "one_to_9 ::= SEVEN",
 /* 108 */ "one_to_9 ::= EIGHT",
 /* 109 */ "one_to_9 ::= NINE",
 /* 110 */ "ten_to_19 ::= TEN",
 /* 111 */ "ten_to_19 ::= ELEVEN",
 /* 112 */ "ten_to_19 ::= TWELVE",
 /* 113 */ "ten_to_19 ::= THIRTEEN",
 /* 114 */ "ten_to_19 ::= FOURTEEN",
 /* 115 */ "ten_to_19 ::= FIFTEEN",
 /* 116 */ "ten_to_19 ::= SIXTEEN",
 /* 117 */ "ten_to_19 ::= SEVENTEEN",
 /* 118 */ "ten_to_19 ::= EIGHTEEN",
 /* 119 */ "ten_to_19 ::= NINETEEN",
 /* 120 */ "tens ::= TWENTY",
 /* 121 */ "tens ::= THIRTY",
 /* 122 */ "tens ::= FORTY",
 /* 123 */ "tens ::= FIFTY",
 /* 124 */ "tens ::= SIXTY",
 /* 125 */ "tens ::= SEVENTY",
 /* 126 */ "tens ::= EIGHTY",
 /* 127 */ "tens ::= NINETY",
 /* 128 */ "first_to_9th ::= FIRST",
 /* 129 */ "first_to_9th ::= FIRSTS",
 /* 130 */ "first_to_9th ::= SECOND",
 /* 131 */ "first_to_9th ::= SECONDS",
 /* 132 */ "first_to_9th ::= THIRD",
 /* 133 */ "first_to_9th ::= THIRDS",
 /* 134 */ "first_to_9th ::= FOURTH",
 /* 135 */ "first_to_9th ::= FOURTHS",
 /* 136 */ "first_to_9th ::= FIFTH",
 /* 137 */ "first_to_9th ::= FIFTHS",
 /* 138 */ "first_to_9th ::= SIXTH",
 /* 139 */ "first_to_9th ::= SIXTHS",
 /* 140 */ "first_to_9th ::= SEVENTH",
 /* 141 */ "first_to_9th ::= SEVENTHS",
 /* 142 */ "first_to_9th ::= EIGHTH",
 /* 143 */ "first_to_9th ::= EIGHTHS",
 /* 144 */ "first_to_9th ::= NINTH",
 /* 145 */ "first_to_9th ::= NINTHS",
 /* 146 */ "tenth_to_19th ::= TENTH",
 /* 147 */ "tenth_to_19th ::= TENTHS",
 /* 148 */ "tenth_to_19th ::= ELEVENTH",
 /* 149 */ "tenth_to_19th ::= ELEVENTHS",
 /* 150 */ "tenth_to_19th ::= TWELFTH",
 /* 151 */ "tenth_to_19th ::= TWELFTHS",
 /* 152 */ "tenth_to_19th ::= THIRTEENTH",
 /* 153 */ "tenth_to_19th ::= THIRTEENTHS",
 /* 154 */ "tenth_to_19th ::= FOURTEENTH",
 /* 155 */ "tenth_to_19th ::= FOURTEENTHS",
 /* 156 */ "tenth_to_19th ::= FIFTEENTH",
 /* 157 */ "tenth_to_19th ::= FIFTEENTHS",
 /* 158 */ "tenth_to_19th ::= SIXTEENTH",
 /* 159 */ "tenth_to_19th ::= SIXTEENTHS",
 /* 160 */ "tenth_to_19th ::= SEVENTEENTH",
 /* 161 */ "tenth_to_19th ::= SEVENTEENTHS",
 /* 162 */ "tenth_to_19th ::= EIGHTEENTH",
 /* 163 */ "tenth_to_19th ::= EIGHTEENTHS",
 /* 164 */ "tenth_to_19th ::= NINETEENTH",
 /* 165 */ "tenth_to_19th ::= NINETEENTHS",
 /* 166 */ "tenths ::= TWENTIETH",
 /* 167 */ "tenths ::= TWENTIETHS",
 /* 168 */ "tenths ::= THIRTIETH",
 /* 169 */ "tenths ::= THIRTIETHS",
 /* 170 */ "tenths ::= FOURTIETH",
 /* 171 */ "tenths ::= FOURTIETHS",
 /* 172 */ "tenths ::= FIFTIETH",
 /* 173 */ "tenths ::= FIFTIETHS",
 /* 174 */ "tenths ::= SIXTIETH",
 /* 175 */ "tenths ::= SIXTIETHS",
 /* 176 */ "tenths ::= SEVENTIETH",
 /* 177 */ "tenths ::= SEVENTIETHS",
 /* 178 */ "tenths ::= EIGHTIETH",
 /* 179 */ "tenths ::= EIGHTIETHS",
 /* 180 */ "tenths ::= NINETIETH",
 /* 181 */ "tenths ::= NINETIETHS",
 /* 182 */ "expr ::= sentence",
 /* 183 */ "expr ::=",
 /* 184 */ "identifiers ::= identifiers CHARACTERS",
 /* 185 */ "identifiers ::= CHARACTERS",
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
  { 109, 3 },
  { 109, 5 },
  { 109, 3 },
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
  { 108, 1 },
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
#line 1398 "parser.c"
        break;
      case 1: /* expr ::= final_number */
      case 5: /* sentence ::= identifiers final_number */ yytestcase(yyruleno==5);
#line 62 "parser.yy"
{
    insertYYSTYPE(&state->yystypeList, yymsp[0].minor.yy0);
}
#line 1406 "parser.c"
        break;
      case 2: /* sentence ::= final_number identifiers final_number */
#line 67 "parser.yy"
{
    insertYYSTYPE(&state->yystypeList, yymsp[-2].minor.yy0);
    insertYYSTYPE(&state->yystypeList, yymsp[0].minor.yy0);
}
#line 1414 "parser.c"
        break;
      case 3: /* sentence ::= identifiers final_number identifiers final_number identifiers */
#line 71 "parser.yy"
{
    insertYYSTYPE(&state->yystypeList, yymsp[-3].minor.yy0);
    insertYYSTYPE(&state->yystypeList, yymsp[-1].minor.yy0);
}
#line 1422 "parser.c"
        break;
      case 4: /* sentence ::= identifiers final_number identifiers */
      case 6: /* sentence ::= final_number identifiers */ yytestcase(yyruleno==6);
#line 75 "parser.yy"
{
    insertYYSTYPE(&state->yystypeList, yymsp[-1].minor.yy0);
}
#line 1430 "parser.c"
        break;
      case 7: /* final_number ::= one_to_999999999999999 AND_A QUARTER */
#line 88 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.25; }
#line 1435 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 8: /* final_number ::= one_to_999999999999999 QUARTERS */
#line 89 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 4.0; }
#line 1441 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 9: /* final_number ::= one_to_999999999999999 AND_A HALF */
#line 90 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.5; }
#line 1447 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 10: /* final_number ::= one_to_999999999999999 HALVES */
#line 91 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 2.0; }
#line 1453 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 11: /* final_number ::= one_to_999999999999999 */
      case 24: /* one_to_999999999999999 ::= trillions */ yytestcase(yyruleno==24);
      case 25: /* one_to_999999999999999 ::= one_to_999999999999 */ yytestcase(yyruleno==25);
      case 39: /* one_to_999999999999 ::= billions */ yytestcase(yyruleno==39);
      case 40: /* one_to_999999999999 ::= one_to_999999999 */ yytestcase(yyruleno==40);
      case 54: /* one_to_999999999 ::= millions */ yytestcase(yyruleno==54);
      case 55: /* one_to_999999999 ::= one_to_999999 */ yytestcase(yyruleno==55);
      case 69: /* one_to_999999 ::= thousands */ yytestcase(yyruleno==69);
      case 70: /* one_to_999999 ::= one_to_999 */ yytestcase(yyruleno==70);
      case 91: /* one_to_999 ::= hundreds */ yytestcase(yyruleno==91);
      case 93: /* one_to_999 ::= one_to_99 */ yytestcase(yyruleno==93);
      case 98: /* one_to_99 ::= tens */ yytestcase(yyruleno==98);
      case 99: /* one_to_99 ::= ten_to_19 */ yytestcase(yyruleno==99);
      case 100: /* one_to_99 ::= one_to_9 */ yytestcase(yyruleno==100);
#line 92 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1472 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 12: /* final_number ::= first_to_999999999999999th */
      case 15: /* first_to_999999999999999th ::= trillionths */ yytestcase(yyruleno==15);
      case 16: /* first_to_999999999999999th ::= first_to_999999999999th */ yytestcase(yyruleno==16);
      case 30: /* first_to_999999999999th ::= billionths */ yytestcase(yyruleno==30);
      case 31: /* first_to_999999999999th ::= first_to_999999999th */ yytestcase(yyruleno==31);
      case 45: /* first_to_999999999th ::= millionths */ yytestcase(yyruleno==45);
      case 46: /* first_to_999999999th ::= first_to_999999th */ yytestcase(yyruleno==46);
      case 60: /* first_to_999999th ::= thousandths */ yytestcase(yyruleno==60);
      case 61: /* first_to_999999th ::= first_to_999th */ yytestcase(yyruleno==61);
      case 76: /* first_to_999th ::= hundredths */ yytestcase(yyruleno==76);
      case 78: /* first_to_999th ::= first_to_99th */ yytestcase(yyruleno==78);
      case 86: /* first_to_99th ::= tenths */ yytestcase(yyruleno==86);
      case 87: /* first_to_99th ::= tenth_to_19th */ yytestcase(yyruleno==87);
      case 88: /* first_to_99th ::= first_to_9th */ yytestcase(yyruleno==88);
#line 93 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1491 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 13: /* final_number ::= ZERO */
#line 99 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 0.0; }
#line 1497 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 14: /* first_to_999999999999999th ::= trillions first_to_999999999999th */
      case 29: /* first_to_999999999999th ::= billions first_to_999999999th */ yytestcase(yyruleno==29);
      case 44: /* first_to_999999999th ::= millions first_to_999999th */ yytestcase(yyruleno==44);
      case 59: /* first_to_999999th ::= thousands first_to_999th */ yytestcase(yyruleno==59);
      case 75: /* first_to_999th ::= hundreds first_to_99th */ yytestcase(yyruleno==75);
      case 85: /* first_to_99th ::= tens first_to_9th */ yytestcase(yyruleno==85);
#line 119 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1508 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 17: /* trillionths ::= one_to_999999999999 TRILLIONTH */
      case 19: /* trillionths ::= NUMBER TRILLIONTH */ yytestcase(yyruleno==19);
#line 123 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1515 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 18: /* trillionths ::= one_to_999999999999 TRILLIONTHS */
      case 20: /* trillionths ::= NUMBER TRILLIONTHS */ yytestcase(yyruleno==20);
#line 124 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; yylhsminor.yy0.suffix = THS; }
#line 1522 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 21: /* trillionths ::= TRILLIONTH */
#line 127 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1528 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 22: /* trillionths ::= TRILLIONTHS */
#line 128 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000000.0; yylhsminor.yy0.suffix = THS; }
#line 1534 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 23: /* one_to_999999999999999 ::= trillions one_to_999999999999 */
      case 38: /* one_to_999999999999 ::= billions one_to_999999999 */ yytestcase(yyruleno==38);
      case 53: /* one_to_999999999 ::= millions one_to_999999 */ yytestcase(yyruleno==53);
      case 68: /* one_to_999999 ::= thousands one_to_999 */ yytestcase(yyruleno==68);
      case 90: /* one_to_999 ::= hundreds one_to_99 */ yytestcase(yyruleno==90);
      case 97: /* one_to_99 ::= tens one_to_9 */ yytestcase(yyruleno==97);
#line 134 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1545 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 26: /* trillions ::= one_to_999999999999 TRILLION */
      case 27: /* trillions ::= NUMBER TRILLION */ yytestcase(yyruleno==27);
#line 138 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; }
#line 1552 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 28: /* trillions ::= TRILLION */
#line 140 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000000.0; }
#line 1558 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 32: /* billionths ::= one_to_999999999 BILLIONTH */
      case 34: /* billionths ::= NUMBER BILLIONTH */ yytestcase(yyruleno==34);
#line 150 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1565 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 33: /* billionths ::= one_to_999999999 BILLIONTHS */
      case 35: /* billionths ::= NUMBER BILLIONTHS */ yytestcase(yyruleno==35);
#line 151 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; yylhsminor.yy0.suffix = THS; }
#line 1572 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 36: /* billionths ::= BILLIONTH */
#line 154 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1578 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 37: /* billionths ::= BILLIONTHS */
#line 155 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000.0; yylhsminor.yy0.suffix = THS; }
#line 1584 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 41: /* billions ::= one_to_999999999 BILLION */
      case 42: /* billions ::= NUMBER BILLION */ yytestcase(yyruleno==42);
#line 165 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; }
#line 1591 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 43: /* billions ::= BILLION */
#line 167 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000.0; }
#line 1597 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 47: /* millionths ::= one_to_999999 MILLIONTH */
      case 49: /* millionths ::= NUMBER MILLIONTH */ yytestcase(yyruleno==49);
#line 177 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; yylhsminor.yy0.suffix = TH; }
#line 1604 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 48: /* millionths ::= one_to_999999 MILLIONTHS */
      case 50: /* millionths ::= NUMBER MILLIONTHS */ yytestcase(yyruleno==50);
#line 178 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; yylhsminor.yy0.suffix = THS; }
#line 1611 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 51: /* millionths ::= MILLIONTH */
#line 181 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000.0; yylhsminor.yy0.suffix = TH; }
#line 1617 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 52: /* millionths ::= MILLIONTHS */
#line 182 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000.0; yylhsminor.yy0.suffix = THS; }
#line 1623 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 56: /* millions ::= one_to_999999 MILLION */
      case 57: /* millions ::= NUMBER MILLION */ yytestcase(yyruleno==57);
#line 192 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; }
#line 1630 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 58: /* millions ::= MILLION */
#line 194 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000.0; }
#line 1636 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 62: /* thousandths ::= one_to_999 THOUSANDTH */
      case 64: /* thousandths ::= NUMBER THOUSANDTH */ yytestcase(yyruleno==64);
#line 204 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; yylhsminor.yy0.suffix = TH; }
#line 1643 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 63: /* thousandths ::= one_to_999 THOUSANDTHS */
      case 65: /* thousandths ::= NUMBER THOUSANDTHS */ yytestcase(yyruleno==65);
#line 205 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; yylhsminor.yy0.suffix = THS; }
#line 1650 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 66: /* thousandths ::= THOUSANDTH */
#line 208 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000.0; yylhsminor.yy0.suffix = TH; }
#line 1656 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 67: /* thousandths ::= THOUSANDTHS */
#line 209 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000.0; yylhsminor.yy0.suffix = THS; }
#line 1662 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 71: /* thousands ::= one_to_999 THOUSAND */
      case 72: /* thousands ::= NUMBER THOUSAND */ yytestcase(yyruleno==72);
#line 219 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; }
#line 1669 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 73: /* thousands ::= THOUSAND */
#line 221 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000.0; }
#line 1675 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 74: /* first_to_999th ::= hundreds AND first_to_99th */
#line 227 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1681 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 77: /* first_to_999th ::= AND first_to_99th */
#line 230 "parser.yy"
{ yymsp[-1].minor.yy0.spos = yymsp[0].minor.yy0.spos; yymsp[-1].minor.yy0.epos = yymsp[0].minor.yy0.epos; yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; yymsp[-1].minor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1687 "parser.c"
        break;
      case 79: /* hundredths ::= one_to_99 HUNDREDTH */
      case 81: /* hundredths ::= NUMBER HUNDREDTH */ yytestcase(yyruleno==81);
#line 233 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; yylhsminor.yy0.suffix = TH; }
#line 1693 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 80: /* hundredths ::= one_to_99 HUNDREDTHS */
      case 82: /* hundredths ::= NUMBER HUNDREDTHS */ yytestcase(yyruleno==82);
#line 234 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; yylhsminor.yy0.suffix = THS; }
#line 1700 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 83: /* hundredths ::= HUNDREDTH */
#line 237 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 100.0; yylhsminor.yy0.suffix = TH; }
#line 1706 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 84: /* hundredths ::= HUNDREDTHS */
#line 238 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 100.0; yylhsminor.yy0.suffix = THS; }
#line 1712 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 89: /* one_to_999 ::= hundreds AND one_to_99 */
#line 249 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1718 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 92: /* one_to_999 ::= AND one_to_99 */
#line 252 "parser.yy"
{ yymsp[-1].minor.yy0.spos = yymsp[0].minor.yy0.spos; yymsp[-1].minor.yy0.epos = yymsp[0].minor.yy0.epos; yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1724 "parser.c"
        break;
      case 94: /* hundreds ::= one_to_99 HUNDRED */
      case 95: /* hundreds ::= NUMBER HUNDRED */ yytestcase(yyruleno==95);
#line 255 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; }
#line 1730 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 96: /* hundreds ::= HUNDRED */
#line 257 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 100.0; }
#line 1736 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 101: /* one_to_9 ::= ONE */
#line 268 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1.0; }
#line 1742 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 102: /* one_to_9 ::= TWO */
#line 269 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 2.0; }
#line 1748 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 103: /* one_to_9 ::= THREE */
#line 270 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 3.0; }
#line 1754 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 104: /* one_to_9 ::= FOUR */
#line 271 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 4.0; }
#line 1760 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 105: /* one_to_9 ::= FIVE */
#line 272 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 5.0; }
#line 1766 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 106: /* one_to_9 ::= SIX */
#line 273 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 6.0; }
#line 1772 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 107: /* one_to_9 ::= SEVEN */
#line 274 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 7.0; }
#line 1778 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 108: /* one_to_9 ::= EIGHT */
#line 275 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 8.0; }
#line 1784 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 109: /* one_to_9 ::= NINE */
#line 276 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 9.0; }
#line 1790 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 110: /* ten_to_19 ::= TEN */
#line 278 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 10.0; }
#line 1796 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 111: /* ten_to_19 ::= ELEVEN */
#line 279 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 11.0; }
#line 1802 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 112: /* ten_to_19 ::= TWELVE */
#line 280 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 12.0; }
#line 1808 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 113: /* ten_to_19 ::= THIRTEEN */
#line 281 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 13.0; }
#line 1814 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 114: /* ten_to_19 ::= FOURTEEN */
#line 282 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 14.0; }
#line 1820 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 115: /* ten_to_19 ::= FIFTEEN */
#line 283 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 15.0; }
#line 1826 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 116: /* ten_to_19 ::= SIXTEEN */
#line 284 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 16.0; }
#line 1832 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 117: /* ten_to_19 ::= SEVENTEEN */
#line 285 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 17.0; }
#line 1838 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 118: /* ten_to_19 ::= EIGHTEEN */
#line 286 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 18.0; }
#line 1844 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 119: /* ten_to_19 ::= NINETEEN */
#line 287 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 19.0; }
#line 1850 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 120: /* tens ::= TWENTY */
#line 289 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 20.0; }
#line 1856 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 121: /* tens ::= THIRTY */
#line 290 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 30.0; }
#line 1862 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 122: /* tens ::= FORTY */
#line 291 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 40.0; }
#line 1868 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 123: /* tens ::= FIFTY */
#line 292 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 50.0; }
#line 1874 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 124: /* tens ::= SIXTY */
#line 293 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 60.0; }
#line 1880 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 125: /* tens ::= SEVENTY */
#line 294 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 70.0; }
#line 1886 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 126: /* tens ::= EIGHTY */
#line 295 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 80.0; }
#line 1892 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 127: /* tens ::= NINETY */
#line 296 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 90.0; }
#line 1898 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 128: /* first_to_9th ::= FIRST */
#line 298 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1.0; yylhsminor.yy0.suffix = ST; }
#line 1904 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 129: /* first_to_9th ::= FIRSTS */
#line 299 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1.0; yylhsminor.yy0.suffix = STS; }
#line 1910 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 130: /* first_to_9th ::= SECOND */
#line 300 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 2.0; yylhsminor.yy0.suffix = ND; }
#line 1916 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 131: /* first_to_9th ::= SECONDS */
#line 301 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 2.0; yylhsminor.yy0.suffix = NDS; }
#line 1922 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 132: /* first_to_9th ::= THIRD */
#line 302 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 3.0; yylhsminor.yy0.suffix = RD; }
#line 1928 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 133: /* first_to_9th ::= THIRDS */
#line 303 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 3.0; yylhsminor.yy0.suffix = RDS; }
#line 1934 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 134: /* first_to_9th ::= FOURTH */
#line 304 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 4.0; yylhsminor.yy0.suffix = TH; }
#line 1940 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 135: /* first_to_9th ::= FOURTHS */
#line 305 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 4.0; yylhsminor.yy0.suffix = THS; }
#line 1946 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 136: /* first_to_9th ::= FIFTH */
#line 306 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 5.0; yylhsminor.yy0.suffix = TH; }
#line 1952 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 137: /* first_to_9th ::= FIFTHS */
#line 307 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 5.0; yylhsminor.yy0.suffix = THS; }
#line 1958 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 138: /* first_to_9th ::= SIXTH */
#line 308 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 6.0; yylhsminor.yy0.suffix = TH; }
#line 1964 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 139: /* first_to_9th ::= SIXTHS */
#line 309 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 6.0; yylhsminor.yy0.suffix = THS; }
#line 1970 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 140: /* first_to_9th ::= SEVENTH */
#line 310 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 7.0; yylhsminor.yy0.suffix = TH; }
#line 1976 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 141: /* first_to_9th ::= SEVENTHS */
#line 311 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 7.0; yylhsminor.yy0.suffix = THS; }
#line 1982 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 142: /* first_to_9th ::= EIGHTH */
#line 312 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 8.0; yylhsminor.yy0.suffix = TH; }
#line 1988 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 143: /* first_to_9th ::= EIGHTHS */
#line 313 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 8.0; yylhsminor.yy0.suffix = THS; }
#line 1994 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 144: /* first_to_9th ::= NINTH */
#line 314 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 9.0; yylhsminor.yy0.suffix = TH; }
#line 2000 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 145: /* first_to_9th ::= NINTHS */
#line 315 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 9.0; yylhsminor.yy0.suffix = THS; }
#line 2006 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 146: /* tenth_to_19th ::= TENTH */
#line 317 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 10.0; yylhsminor.yy0.suffix = TH; }
#line 2012 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 147: /* tenth_to_19th ::= TENTHS */
#line 318 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 10.0; yylhsminor.yy0.suffix = THS; }
#line 2018 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 148: /* tenth_to_19th ::= ELEVENTH */
#line 319 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 11.0; yylhsminor.yy0.suffix = TH; }
#line 2024 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 149: /* tenth_to_19th ::= ELEVENTHS */
#line 320 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 11.0; yylhsminor.yy0.suffix = THS; }
#line 2030 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 150: /* tenth_to_19th ::= TWELFTH */
#line 321 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 12.0; yylhsminor.yy0.suffix = TH; }
#line 2036 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 151: /* tenth_to_19th ::= TWELFTHS */
#line 322 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 12.0; yylhsminor.yy0.suffix = THS; }
#line 2042 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 152: /* tenth_to_19th ::= THIRTEENTH */
#line 323 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 13.0; yylhsminor.yy0.suffix = TH; }
#line 2048 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 153: /* tenth_to_19th ::= THIRTEENTHS */
#line 324 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 13.0; yylhsminor.yy0.suffix = THS; }
#line 2054 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 154: /* tenth_to_19th ::= FOURTEENTH */
#line 325 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 14.0; yylhsminor.yy0.suffix = TH; }
#line 2060 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 155: /* tenth_to_19th ::= FOURTEENTHS */
#line 326 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 14.0; yylhsminor.yy0.suffix = THS; }
#line 2066 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 156: /* tenth_to_19th ::= FIFTEENTH */
#line 327 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 15.0; yylhsminor.yy0.suffix = TH; }
#line 2072 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 157: /* tenth_to_19th ::= FIFTEENTHS */
#line 328 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 15.0; yylhsminor.yy0.suffix = THS; }
#line 2078 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 158: /* tenth_to_19th ::= SIXTEENTH */
#line 329 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 16.0; yylhsminor.yy0.suffix = TH; }
#line 2084 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 159: /* tenth_to_19th ::= SIXTEENTHS */
#line 330 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 16.0; yylhsminor.yy0.suffix = THS; }
#line 2090 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 160: /* tenth_to_19th ::= SEVENTEENTH */
#line 331 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 17.0; yylhsminor.yy0.suffix = TH; }
#line 2096 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 161: /* tenth_to_19th ::= SEVENTEENTHS */
#line 332 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 17.0; yylhsminor.yy0.suffix = THS; }
#line 2102 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 162: /* tenth_to_19th ::= EIGHTEENTH */
#line 333 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 18.0; yylhsminor.yy0.suffix = TH; }
#line 2108 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 163: /* tenth_to_19th ::= EIGHTEENTHS */
#line 334 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 18.0; yylhsminor.yy0.suffix = THS; }
#line 2114 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 164: /* tenth_to_19th ::= NINETEENTH */
#line 335 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 19.0; yylhsminor.yy0.suffix = TH; }
#line 2120 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 165: /* tenth_to_19th ::= NINETEENTHS */
#line 336 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 19.0; yylhsminor.yy0.suffix = THS; }
#line 2126 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 166: /* tenths ::= TWENTIETH */
#line 338 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 20.0; yylhsminor.yy0.suffix = TH; }
#line 2132 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 167: /* tenths ::= TWENTIETHS */
#line 339 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 20.0; yylhsminor.yy0.suffix = THS; }
#line 2138 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 168: /* tenths ::= THIRTIETH */
#line 340 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 30.0; yylhsminor.yy0.suffix = TH; }
#line 2144 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 169: /* tenths ::= THIRTIETHS */
#line 341 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 30.0; yylhsminor.yy0.suffix = THS; }
#line 2150 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 170: /* tenths ::= FOURTIETH */
#line 342 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 40.0; yylhsminor.yy0.suffix = TH; }
#line 2156 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 171: /* tenths ::= FOURTIETHS */
#line 343 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 40.0; yylhsminor.yy0.suffix = THS; }
#line 2162 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 172: /* tenths ::= FIFTIETH */
#line 344 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 50.0; yylhsminor.yy0.suffix = TH; }
#line 2168 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 173: /* tenths ::= FIFTIETHS */
#line 345 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 50.0; yylhsminor.yy0.suffix = THS; }
#line 2174 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 174: /* tenths ::= SIXTIETH */
#line 346 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 60.0; yylhsminor.yy0.suffix = TH; }
#line 2180 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 175: /* tenths ::= SIXTIETHS */
#line 347 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 60.0; yylhsminor.yy0.suffix = THS; }
#line 2186 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 176: /* tenths ::= SEVENTIETH */
#line 348 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 70.0; yylhsminor.yy0.suffix = TH; }
#line 2192 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 177: /* tenths ::= SEVENTIETHS */
#line 349 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 70.0; yylhsminor.yy0.suffix = THS; }
#line 2198 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 178: /* tenths ::= EIGHTIETH */
#line 350 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 80.0; yylhsminor.yy0.suffix = TH; }
#line 2204 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 179: /* tenths ::= EIGHTIETHS */
#line 351 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 80.0; yylhsminor.yy0.suffix = THS; }
#line 2210 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 180: /* tenths ::= NINETIETH */
#line 352 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 90.0; yylhsminor.yy0.suffix = TH; }
#line 2216 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 181: /* tenths ::= NINETIETHS */
#line 353 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 90.0; yylhsminor.yy0.suffix = THS; }
#line 2222 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      default:
      /* (182) expr ::= sentence (OPTIMIZED OUT) */ assert(yyruleno!=182);
      /* (183) expr ::= (OPTIMIZED OUT) */ assert(yyruleno!=183);
      /* (184) identifiers ::= identifiers CHARACTERS */ yytestcase(yyruleno==184);
      /* (185) identifiers ::= CHARACTERS */ yytestcase(yyruleno==185);
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
#line 2272 "parser.c"
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
#line 2291 "parser.c"
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
