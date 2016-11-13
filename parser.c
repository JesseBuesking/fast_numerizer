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
#define YYNOCODE 110
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
#define YYNRULE              142
#define YY_MAX_SHIFT         23
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
#define YY_ACTTAB_COUNT (737)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   292,  201,  207,  292,  215,  227,  160,  166,   11,  172,
 /*    10 */   178,  184,  190,  196,  202,  208,    7,  216,  228,  233,
 /*    20 */   234,  235,  236,  237,  238,  239,  240,  241,  242,  243,
 /*    30 */   244,  245,  246,  247,  248,  249,  250,  251,  252,  253,
 /*    40 */   254,  255,  256,  257,  258,  259,  260,  261,  262,  263,
 /*    50 */   264,  265,  266,  267,  268,  269,  270,  271,  272,  273,
 /*    60 */   274,  275,  276,  277,  278,  279,  280,  281,  282,  283,
 /*    70 */   284,  285,  286,  291,  217,  293,  152,  229,    1,  160,
 /*    80 */   166,   11,  172,  178,  184,  190,  196,  202,  208,    7,
 /*    90 */   216,  228,  233,  234,  235,  236,  237,  238,  239,  240,
 /*   100 */   241,  242,  243,  244,  245,  246,  247,  248,  249,  250,
 /*   110 */   251,  252,  253,  254,  255,  256,  257,  258,  259,  260,
 /*   120 */   261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
 /*   130 */   271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
 /*   140 */   281,  282,  283,  284,  285,  286,   12,  295,  178,  184,
 /*   150 */   190,  196,  202,  208,    7,  216,  228,  233,  234,  235,
 /*   160 */   236,  237,  238,  239,  240,  241,  242,  243,  244,  245,
 /*   170 */   246,  247,  248,  249,  250,  251,  252,  253,  254,  255,
 /*   180 */   256,  257,  258,  259,  260,  261,  262,  263,  264,  265,
 /*   190 */   266,  267,  268,  269,  270,  271,  272,  273,  274,  275,
 /*   200 */   276,  277,  278,  279,  280,  281,  282,  283,  284,  285,
 /*   210 */   286,   13,  164,  295,  170,  190,  196,  202,  208,    7,
 /*   220 */   216,  228,  233,  234,  235,  236,  237,  238,  239,  240,
 /*   230 */   241,  242,  243,  244,  245,  246,  247,  248,  249,  250,
 /*   240 */   251,  252,  253,  254,  255,  256,  257,  258,  259,  260,
 /*   250 */   261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
 /*   260 */   271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
 /*   270 */   281,  282,  283,  284,  285,  286,   14,   22,  295,  155,
 /*   280 */   295,  157,  202,  208,    7,  216,  228,  233,  234,  235,
 /*   290 */   236,  237,  238,  239,  240,  241,  242,  243,  244,  245,
 /*   300 */   246,  247,  248,  249,  250,  251,  252,  253,  254,  255,
 /*   310 */   256,  257,  258,  259,  260,  261,  262,  263,  264,  265,
 /*   320 */   266,  267,  268,  269,  270,  271,  272,  273,  274,  275,
 /*   330 */   276,  277,  278,  279,  280,  281,  282,  283,  284,  285,
 /*   340 */   286,   20,  189,  195,  201,  207,  295,  215,  227,    7,
 /*   350 */   216,  228,  233,  234,  235,  236,  237,  238,  239,  240,
 /*   360 */   241,  242,  243,  244,  245,  246,  247,  248,  249,  250,
 /*   370 */   251,  252,  253,  254,  255,  256,  257,  258,  259,  260,
 /*   380 */   261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
 /*   390 */   271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
 /*   400 */   281,  282,  283,  284,  285,  286,    8,  176,  182,  233,
 /*   410 */   234,  235,  236,  237,  238,  239,  240,  241,  242,  243,
 /*   420 */   244,  245,  246,  247,  248,  249,  250,  251,  252,  253,
 /*   430 */   254,  255,  256,  257,  258,  259,  260,  261,  262,  263,
 /*   440 */   264,  265,  266,  267,  268,  269,  270,  271,  272,  273,
 /*   450 */   274,  275,  276,  277,  278,  279,  280,  281,  282,  283,
 /*   460 */   284,  285,  286,  233,  234,  235,  236,  237,  238,  239,
 /*   470 */   240,  241,  242,  243,  244,  245,  246,  247,  248,  249,
 /*   480 */   250,  251,  252,  253,  254,  255,  256,  257,  258,  259,
 /*   490 */   260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
 /*   500 */   270,  271,  272,  273,  274,  275,  276,  277,  278,  279,
 /*   510 */   280,  281,  282,  283,  284,  285,  286,  436,   23,   23,
 /*   520 */    23,   10,    1,   15,  159,    2,  163,  162,   16,    3,
 /*   530 */   175,  174,   17,    4,  187,  186,   18,    5,  199,  198,
 /*   540 */    19,    6,  213,  211,   21,    9,  220,  218,  219,  232,
 /*   550 */   231,  289,  154,   10,  156,   15,  159,    2,  163,  162,
 /*   560 */    16,    3,  175,  174,   17,    4,  187,  186,   18,    5,
 /*   570 */   199,  198,   19,    6,  213,  211,   21,    9,  220,  218,
 /*   580 */   219,  232,  231,  161,  295,  167,    3,  175,  174,   17,
 /*   590 */     4,  187,  186,   18,    5,  199,  198,   19,    6,  213,
 /*   600 */   211,   21,    9,  220,  218,  219,  232,  231,  173,  295,
 /*   610 */   179,    4,  187,  186,   18,    5,  199,  198,   19,    6,
 /*   620 */   213,  211,   21,    9,  220,  218,  219,  232,  231,  233,
 /*   630 */   234,  235,  236,  237,  238,  239,  240,  241,  185,  295,
 /*   640 */   191,    5,  199,  198,   19,    6,  213,  211,   21,    9,
 /*   650 */   220,  218,  219,  232,  231,  295,  260,  261,  262,  263,
 /*   660 */   264,  265,  266,  267,  268,  197,  295,  203,    6,  213,
 /*   670 */   211,   21,    9,  220,  218,  219,  232,  231,  165,  295,
 /*   680 */   171,  177,  183,  189,  195,  201,  207,  295,  215,  227,
 /*   690 */   210,  295,  222,    9,  220,  218,  219,  232,  231,  212,
 /*   700 */   295,  224,    9,  220,  218,  219,  232,  231,  209,  295,
 /*   710 */   221,    9,  220,  218,  219,  232,  231,  177,  183,  189,
 /*   720 */   195,  201,  207,  295,  215,  227,  188,  194,  295,  200,
 /*   730 */   206,  295,  295,  215,  227,  214,  226,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,   15,   16,    1,   18,   19,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    20 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*    30 */    31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
 /*    40 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*    50 */    51,   52,   53,   54,   55,   56,   57,   58,   59,   60,
 /*    60 */    61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
 /*    70 */    71,   72,   73,    1,  104,    0,   78,  107,   80,    7,
 /*    80 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*    90 */    18,   19,   20,   21,   22,   23,   24,   25,   26,   27,
 /*   100 */    28,   29,   30,   31,   32,   33,   34,   35,   36,   37,
 /*   110 */    38,   39,   40,   41,   42,   43,   44,   45,   46,   47,
 /*   120 */    48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
 /*   130 */    58,   59,   60,   61,   62,   63,   64,   65,   66,   67,
 /*   140 */    68,   69,   70,   71,   72,   73,    9,  109,   11,   12,
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
 /*   550 */   108,   77,    3,   79,    5,   81,   82,   83,   84,   85,
 /*   560 */    86,   87,   88,   89,   90,   91,   92,   93,   94,   95,
 /*   570 */    96,   97,   98,   99,  100,  101,  102,  103,  104,  105,
 /*   580 */   106,  107,  108,   84,  109,   86,   87,   88,   89,   90,
 /*   590 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   600 */   101,  102,  103,  104,  105,  106,  107,  108,   88,  109,
 /*   610 */    90,   91,   92,   93,   94,   95,   96,   97,   98,   99,
 /*   620 */   100,  101,  102,  103,  104,  105,  106,  107,  108,   20,
 /*   630 */    21,   22,   23,   24,   25,   26,   27,   28,   92,  109,
 /*   640 */    94,   95,   96,   97,   98,   99,  100,  101,  102,  103,
 /*   650 */   104,  105,  106,  107,  108,  109,   47,   48,   49,   50,
 /*   660 */    51,   52,   53,   54,   55,   96,  109,   98,   99,  100,
 /*   670 */   101,  102,  103,  104,  105,  106,  107,  108,    8,  109,
 /*   680 */    10,   11,   12,   13,   14,   15,   16,  109,   18,   19,
 /*   690 */   100,  109,  102,  103,  104,  105,  106,  107,  108,  100,
 /*   700 */   109,  102,  103,  104,  105,  106,  107,  108,  100,  109,
 /*   710 */   102,  103,  104,  105,  106,  107,  108,   11,   12,   13,
 /*   720 */    14,   15,   16,  109,   18,   19,   13,   14,  109,   15,
 /*   730 */    16,  109,  109,   18,   19,   18,   19,
};
#define YY_SHIFT_USE_DFLT (737)
#define YY_SHIFT_COUNT    (23)
#define YY_SHIFT_MIN      (-14)
#define YY_SHIFT_MAX      (717)
static const short yy_shift_ofst[] = {
 /*     0 */    -1,   72,  137,  202,  267,  332,  389,  443,  443,  609,
 /*    10 */     2,  670,  706,  329,  -14,  275,  204,  396,  713,  714,
 /*    20 */   715,  717,  549,   75,
};
#define YY_REDUCE_USE_DFLT (-31)
#define YY_REDUCE_COUNT (10)
#define YY_REDUCE_MIN   (-30)
#define YY_REDUCE_MAX   (608)
static const short yy_reduce_ofst[] = {
 /*     0 */   442,  474,  499,  520,  546,  569,  590,  599,  608,  -30,
 /*    10 */    -2,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   435,  432,  310,  322,  334,  346,  365,  435,  435,  372,
 /*    10 */   295,  435,  435,  435,  435,  300,  311,  323,  335,  347,
 /*    20 */   435,  367,  435,  435,
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
  "expr",          "num_ident",     "ident_num",     "final_number",
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
 /*  14 */ "trillionths ::= NUMBER TRILLIONTH",
 /*  15 */ "trillionths ::= TRILLIONTH",
 /*  16 */ "one_to_999999999999999 ::= trillions one_to_999999999999",
 /*  17 */ "one_to_999999999999999 ::= trillions",
 /*  18 */ "one_to_999999999999999 ::= one_to_999999999999",
 /*  19 */ "trillions ::= one_to_999999999999 TRILLION",
 /*  20 */ "trillions ::= NUMBER TRILLION",
 /*  21 */ "trillions ::= TRILLION",
 /*  22 */ "first_to_999999999999th ::= billions first_to_999999999th",
 /*  23 */ "first_to_999999999999th ::= billionths",
 /*  24 */ "first_to_999999999999th ::= first_to_999999999th",
 /*  25 */ "billionths ::= one_to_999999999 BILLIONTH",
 /*  26 */ "billionths ::= NUMBER BILLIONTH",
 /*  27 */ "billionths ::= BILLIONTH",
 /*  28 */ "one_to_999999999999 ::= billions one_to_999999999",
 /*  29 */ "one_to_999999999999 ::= billions",
 /*  30 */ "one_to_999999999999 ::= one_to_999999999",
 /*  31 */ "billions ::= one_to_999999999 BILLION",
 /*  32 */ "billions ::= NUMBER BILLION",
 /*  33 */ "billions ::= BILLION",
 /*  34 */ "first_to_999999999th ::= millions first_to_999999th",
 /*  35 */ "first_to_999999999th ::= millionths",
 /*  36 */ "first_to_999999999th ::= first_to_999999th",
 /*  37 */ "millionths ::= one_to_999999 MILLIONTH",
 /*  38 */ "millionths ::= NUMBER MILLIONTH",
 /*  39 */ "millionths ::= MILLIONTH",
 /*  40 */ "one_to_999999999 ::= millions one_to_999999",
 /*  41 */ "one_to_999999999 ::= millions",
 /*  42 */ "one_to_999999999 ::= one_to_999999",
 /*  43 */ "millions ::= one_to_999999 MILLION",
 /*  44 */ "millions ::= NUMBER MILLION",
 /*  45 */ "millions ::= MILLION",
 /*  46 */ "first_to_999999th ::= thousands first_to_999th",
 /*  47 */ "first_to_999999th ::= thousandths",
 /*  48 */ "first_to_999999th ::= first_to_999th",
 /*  49 */ "thousandths ::= one_to_999 THOUSANDTH",
 /*  50 */ "thousandths ::= NUMBER THOUSANDTH",
 /*  51 */ "thousandths ::= THOUSANDTH",
 /*  52 */ "one_to_999999 ::= thousands one_to_999",
 /*  53 */ "one_to_999999 ::= thousands",
 /*  54 */ "one_to_999999 ::= one_to_999",
 /*  55 */ "thousands ::= one_to_999 THOUSAND",
 /*  56 */ "thousands ::= NUMBER THOUSAND",
 /*  57 */ "thousands ::= THOUSAND",
 /*  58 */ "first_to_999th ::= hundreds AND first_to_99th",
 /*  59 */ "first_to_999th ::= hundreds first_to_99th",
 /*  60 */ "first_to_999th ::= hundredths",
 /*  61 */ "first_to_999th ::= AND first_to_99th",
 /*  62 */ "first_to_999th ::= first_to_99th",
 /*  63 */ "hundredths ::= one_to_99 HUNDREDTH",
 /*  64 */ "hundredths ::= NUMBER HUNDREDTH",
 /*  65 */ "hundredths ::= HUNDREDTH",
 /*  66 */ "first_to_99th ::= tens first_to_9th",
 /*  67 */ "first_to_99th ::= tenth",
 /*  68 */ "first_to_99th ::= tenth_to_19th",
 /*  69 */ "first_to_99th ::= first_to_9th",
 /*  70 */ "one_to_999 ::= hundreds AND one_to_99",
 /*  71 */ "one_to_999 ::= hundreds one_to_99",
 /*  72 */ "one_to_999 ::= hundreds",
 /*  73 */ "one_to_999 ::= AND one_to_99",
 /*  74 */ "one_to_999 ::= one_to_99",
 /*  75 */ "hundreds ::= one_to_99 HUNDRED",
 /*  76 */ "hundreds ::= NUMBER HUNDRED",
 /*  77 */ "hundreds ::= HUNDRED",
 /*  78 */ "one_to_99 ::= tens one_to_9",
 /*  79 */ "one_to_99 ::= tens",
 /*  80 */ "one_to_99 ::= ten_to_19",
 /*  81 */ "one_to_99 ::= one_to_9",
 /*  82 */ "one_to_9 ::= ONE",
 /*  83 */ "one_to_9 ::= TWO",
 /*  84 */ "one_to_9 ::= THREE",
 /*  85 */ "one_to_9 ::= FOUR",
 /*  86 */ "one_to_9 ::= FIVE",
 /*  87 */ "one_to_9 ::= SIX",
 /*  88 */ "one_to_9 ::= SEVEN",
 /*  89 */ "one_to_9 ::= EIGHT",
 /*  90 */ "one_to_9 ::= NINE",
 /*  91 */ "ten_to_19 ::= TEN",
 /*  92 */ "ten_to_19 ::= ELEVEN",
 /*  93 */ "ten_to_19 ::= TWELVE",
 /*  94 */ "ten_to_19 ::= THIRTEEN",
 /*  95 */ "ten_to_19 ::= FOURTEEN",
 /*  96 */ "ten_to_19 ::= FIFTEEN",
 /*  97 */ "ten_to_19 ::= SIXTEEN",
 /*  98 */ "ten_to_19 ::= SEVENTEEN",
 /*  99 */ "ten_to_19 ::= EIGHTEEN",
 /* 100 */ "ten_to_19 ::= NINETEEN",
 /* 101 */ "tens ::= TWENTY",
 /* 102 */ "tens ::= THIRTY",
 /* 103 */ "tens ::= FORTY",
 /* 104 */ "tens ::= FIFTY",
 /* 105 */ "tens ::= SIXTY",
 /* 106 */ "tens ::= SEVENTY",
 /* 107 */ "tens ::= EIGHTY",
 /* 108 */ "tens ::= NINETY",
 /* 109 */ "first_to_9th ::= FIRST",
 /* 110 */ "first_to_9th ::= SECOND",
 /* 111 */ "first_to_9th ::= THIRD",
 /* 112 */ "first_to_9th ::= FOURTH",
 /* 113 */ "first_to_9th ::= FIFTH",
 /* 114 */ "first_to_9th ::= SIXTH",
 /* 115 */ "first_to_9th ::= SEVENTH",
 /* 116 */ "first_to_9th ::= EIGHTH",
 /* 117 */ "first_to_9th ::= NINTH",
 /* 118 */ "tenth_to_19th ::= TENTH",
 /* 119 */ "tenth_to_19th ::= ELEVENTH",
 /* 120 */ "tenth_to_19th ::= TWELFTH",
 /* 121 */ "tenth_to_19th ::= THIRTEENTH",
 /* 122 */ "tenth_to_19th ::= FOURTEENTH",
 /* 123 */ "tenth_to_19th ::= FIFTEENTH",
 /* 124 */ "tenth_to_19th ::= SIXTEENTH",
 /* 125 */ "tenth_to_19th ::= SEVENTEENTH",
 /* 126 */ "tenth_to_19th ::= EIGHTEENTH",
 /* 127 */ "tenth_to_19th ::= NINETEENTH",
 /* 128 */ "tenth ::= TWENTIETH",
 /* 129 */ "tenth ::= THIRTIETH",
 /* 130 */ "tenth ::= FOURTIETH",
 /* 131 */ "tenth ::= FIFTIETH",
 /* 132 */ "tenth ::= SIXTIETH",
 /* 133 */ "tenth ::= SEVENTIETH",
 /* 134 */ "tenth ::= EIGHTIETH",
 /* 135 */ "tenth ::= NINETIETH",
 /* 136 */ "expr ::= num_ident",
 /* 137 */ "expr ::= ident_num",
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
  { 75, 1 },
  { 77, 2 },
  { 77, 1 },
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
  { 76, 1 },
  { 76, 1 },
  { 78, 2 },
  { 78, 1 },
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
#line 1239 "parser.c"
        break;
      case 1: /* num_ident ::= final_number ident_num */
#line 64 "parser.yy"
{
    insertYYSTYPE(&state->yystypeList, yymsp[-1].minor.yy0);
}
#line 1246 "parser.c"
        break;
      case 2: /* num_ident ::= final_number */
#line 68 "parser.yy"
{
    insertYYSTYPE(&state->yystypeList, yymsp[0].minor.yy0);
}
#line 1253 "parser.c"
        break;
      case 3: /* final_number ::= one_to_999999999999999 AND_A QUARTER */
#line 85 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.25; }
#line 1258 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 4: /* final_number ::= one_to_999999999999999 QUARTERS */
#line 86 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 4.0; }
#line 1264 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 5: /* final_number ::= one_to_999999999999999 AND_A HALF */
#line 87 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.5; }
#line 1270 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 6: /* final_number ::= one_to_999999999999999 HALVES */
#line 88 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 2.0; }
#line 1276 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 7: /* final_number ::= one_to_999999999999999 */
      case 17: /* one_to_999999999999999 ::= trillions */ yytestcase(yyruleno==17);
      case 18: /* one_to_999999999999999 ::= one_to_999999999999 */ yytestcase(yyruleno==18);
      case 29: /* one_to_999999999999 ::= billions */ yytestcase(yyruleno==29);
      case 30: /* one_to_999999999999 ::= one_to_999999999 */ yytestcase(yyruleno==30);
      case 41: /* one_to_999999999 ::= millions */ yytestcase(yyruleno==41);
      case 42: /* one_to_999999999 ::= one_to_999999 */ yytestcase(yyruleno==42);
      case 53: /* one_to_999999 ::= thousands */ yytestcase(yyruleno==53);
      case 54: /* one_to_999999 ::= one_to_999 */ yytestcase(yyruleno==54);
      case 72: /* one_to_999 ::= hundreds */ yytestcase(yyruleno==72);
      case 74: /* one_to_999 ::= one_to_99 */ yytestcase(yyruleno==74);
      case 79: /* one_to_99 ::= tens */ yytestcase(yyruleno==79);
      case 80: /* one_to_99 ::= ten_to_19 */ yytestcase(yyruleno==80);
      case 81: /* one_to_99 ::= one_to_9 */ yytestcase(yyruleno==81);
#line 89 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1295 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 8: /* final_number ::= first_to_999999999999999th */
      case 11: /* first_to_999999999999999th ::= trillionths */ yytestcase(yyruleno==11);
      case 12: /* first_to_999999999999999th ::= first_to_999999999999th */ yytestcase(yyruleno==12);
      case 23: /* first_to_999999999999th ::= billionths */ yytestcase(yyruleno==23);
      case 24: /* first_to_999999999999th ::= first_to_999999999th */ yytestcase(yyruleno==24);
      case 35: /* first_to_999999999th ::= millionths */ yytestcase(yyruleno==35);
      case 36: /* first_to_999999999th ::= first_to_999999th */ yytestcase(yyruleno==36);
      case 47: /* first_to_999999th ::= thousandths */ yytestcase(yyruleno==47);
      case 48: /* first_to_999999th ::= first_to_999th */ yytestcase(yyruleno==48);
      case 60: /* first_to_999th ::= hundredths */ yytestcase(yyruleno==60);
      case 62: /* first_to_999th ::= first_to_99th */ yytestcase(yyruleno==62);
      case 67: /* first_to_99th ::= tenth */ yytestcase(yyruleno==67);
      case 68: /* first_to_99th ::= tenth_to_19th */ yytestcase(yyruleno==68);
      case 69: /* first_to_99th ::= first_to_9th */ yytestcase(yyruleno==69);
#line 90 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1314 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 9: /* final_number ::= ZERO */
#line 96 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 0.0; }
#line 1320 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 10: /* first_to_999999999999999th ::= trillions first_to_999999999999th */
      case 22: /* first_to_999999999999th ::= billions first_to_999999999th */ yytestcase(yyruleno==22);
      case 34: /* first_to_999999999th ::= millions first_to_999999th */ yytestcase(yyruleno==34);
      case 46: /* first_to_999999th ::= thousands first_to_999th */ yytestcase(yyruleno==46);
      case 59: /* first_to_999th ::= hundreds first_to_99th */ yytestcase(yyruleno==59);
      case 66: /* first_to_99th ::= tens first_to_9th */ yytestcase(yyruleno==66);
#line 119 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1331 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 13: /* trillionths ::= one_to_999999999999 TRILLIONTH */
      case 14: /* trillionths ::= NUMBER TRILLIONTH */ yytestcase(yyruleno==14);
#line 123 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1338 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 15: /* trillionths ::= TRILLIONTH */
#line 125 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1344 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 16: /* one_to_999999999999999 ::= trillions one_to_999999999999 */
      case 28: /* one_to_999999999999 ::= billions one_to_999999999 */ yytestcase(yyruleno==28);
      case 40: /* one_to_999999999 ::= millions one_to_999999 */ yytestcase(yyruleno==40);
      case 52: /* one_to_999999 ::= thousands one_to_999 */ yytestcase(yyruleno==52);
      case 71: /* one_to_999 ::= hundreds one_to_99 */ yytestcase(yyruleno==71);
      case 78: /* one_to_99 ::= tens one_to_9 */ yytestcase(yyruleno==78);
#line 135 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1355 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 19: /* trillions ::= one_to_999999999999 TRILLION */
      case 20: /* trillions ::= NUMBER TRILLION */ yytestcase(yyruleno==20);
#line 139 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; }
#line 1362 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 21: /* trillions ::= TRILLION */
#line 141 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000000.0; }
#line 1368 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 25: /* billionths ::= one_to_999999999 BILLIONTH */
      case 26: /* billionths ::= NUMBER BILLIONTH */ yytestcase(yyruleno==26);
#line 151 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1375 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 27: /* billionths ::= BILLIONTH */
#line 153 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000.0; yylhsminor.yy0.suffix = TH; }
#line 1381 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 31: /* billions ::= one_to_999999999 BILLION */
      case 32: /* billions ::= NUMBER BILLION */ yytestcase(yyruleno==32);
#line 167 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; }
#line 1388 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 33: /* billions ::= BILLION */
#line 169 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000000.0; }
#line 1394 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 37: /* millionths ::= one_to_999999 MILLIONTH */
      case 38: /* millionths ::= NUMBER MILLIONTH */ yytestcase(yyruleno==38);
#line 179 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; yylhsminor.yy0.suffix = TH; }
#line 1401 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 39: /* millionths ::= MILLIONTH */
#line 181 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000.0; yylhsminor.yy0.suffix = TH; }
#line 1407 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 43: /* millions ::= one_to_999999 MILLION */
      case 44: /* millions ::= NUMBER MILLION */ yytestcase(yyruleno==44);
#line 195 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; }
#line 1414 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 45: /* millions ::= MILLION */
#line 197 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000000.0; }
#line 1420 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 49: /* thousandths ::= one_to_999 THOUSANDTH */
      case 50: /* thousandths ::= NUMBER THOUSANDTH */ yytestcase(yyruleno==50);
#line 207 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; yylhsminor.yy0.suffix = TH; }
#line 1427 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 51: /* thousandths ::= THOUSANDTH */
#line 209 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000.0; yylhsminor.yy0.suffix = TH; }
#line 1433 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 55: /* thousands ::= one_to_999 THOUSAND */
      case 56: /* thousands ::= NUMBER THOUSAND */ yytestcase(yyruleno==56);
#line 223 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; }
#line 1440 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 57: /* thousands ::= THOUSAND */
#line 225 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1000.0; }
#line 1446 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 58: /* first_to_999th ::= hundreds AND first_to_99th */
#line 231 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1452 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 61: /* first_to_999th ::= AND first_to_99th */
#line 234 "parser.yy"
{ yymsp[-1].minor.yy0.spos = yymsp[0].minor.yy0.spos; yymsp[-1].minor.yy0.epos = yymsp[0].minor.yy0.epos; yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; yymsp[-1].minor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1458 "parser.c"
        break;
      case 63: /* hundredths ::= one_to_99 HUNDREDTH */
      case 64: /* hundredths ::= NUMBER HUNDREDTH */ yytestcase(yyruleno==64);
#line 237 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; yylhsminor.yy0.suffix = TH; }
#line 1464 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 65: /* hundredths ::= HUNDREDTH */
#line 239 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 100.0; yylhsminor.yy0.suffix = TH; }
#line 1470 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 70: /* one_to_999 ::= hundreds AND one_to_99 */
#line 254 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-2].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-2].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1476 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 73: /* one_to_999 ::= AND one_to_99 */
#line 257 "parser.yy"
{ yymsp[-1].minor.yy0.spos = yymsp[0].minor.yy0.spos; yymsp[-1].minor.yy0.epos = yymsp[0].minor.yy0.epos; yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1482 "parser.c"
        break;
      case 75: /* hundreds ::= one_to_99 HUNDRED */
      case 76: /* hundreds ::= NUMBER HUNDRED */ yytestcase(yyruleno==76);
#line 260 "parser.yy"
{ yylhsminor.yy0.spos = mini(yymsp[-1].minor.yy0.spos, yymsp[0].minor.yy0.spos); yylhsminor.yy0.epos = maxi(yymsp[-1].minor.yy0.epos, yymsp[0].minor.yy0.epos); yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; }
#line 1488 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 77: /* hundreds ::= HUNDRED */
#line 262 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 100.0; }
#line 1494 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 82: /* one_to_9 ::= ONE */
#line 273 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1.0; }
#line 1500 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 83: /* one_to_9 ::= TWO */
#line 274 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 2.0; }
#line 1506 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 84: /* one_to_9 ::= THREE */
#line 275 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 3.0; }
#line 1512 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 85: /* one_to_9 ::= FOUR */
#line 276 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 4.0; }
#line 1518 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 86: /* one_to_9 ::= FIVE */
#line 277 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 5.0; }
#line 1524 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 87: /* one_to_9 ::= SIX */
#line 278 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 6.0; }
#line 1530 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 88: /* one_to_9 ::= SEVEN */
#line 279 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 7.0; }
#line 1536 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 89: /* one_to_9 ::= EIGHT */
#line 280 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 8.0; }
#line 1542 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 90: /* one_to_9 ::= NINE */
#line 281 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 9.0; }
#line 1548 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 91: /* ten_to_19 ::= TEN */
#line 283 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 10.0; }
#line 1554 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 92: /* ten_to_19 ::= ELEVEN */
#line 284 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 11.0; }
#line 1560 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 93: /* ten_to_19 ::= TWELVE */
#line 285 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 12.0; }
#line 1566 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 94: /* ten_to_19 ::= THIRTEEN */
#line 286 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 13.0; }
#line 1572 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 95: /* ten_to_19 ::= FOURTEEN */
#line 287 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 14.0; }
#line 1578 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 96: /* ten_to_19 ::= FIFTEEN */
#line 288 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 15.0; }
#line 1584 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 97: /* ten_to_19 ::= SIXTEEN */
#line 289 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 16.0; }
#line 1590 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 98: /* ten_to_19 ::= SEVENTEEN */
#line 290 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 17.0; }
#line 1596 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 99: /* ten_to_19 ::= EIGHTEEN */
#line 291 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 18.0; }
#line 1602 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 100: /* ten_to_19 ::= NINETEEN */
#line 292 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 19.0; }
#line 1608 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 101: /* tens ::= TWENTY */
#line 294 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 20.0; }
#line 1614 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 102: /* tens ::= THIRTY */
#line 295 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 30.0; }
#line 1620 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 103: /* tens ::= FORTY */
#line 296 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 40.0; }
#line 1626 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 104: /* tens ::= FIFTY */
#line 297 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 50.0; }
#line 1632 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 105: /* tens ::= SIXTY */
#line 298 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 60.0; }
#line 1638 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 106: /* tens ::= SEVENTY */
#line 299 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 70.0; }
#line 1644 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 107: /* tens ::= EIGHTY */
#line 300 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 80.0; }
#line 1650 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 108: /* tens ::= NINETY */
#line 301 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 90.0; }
#line 1656 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 109: /* first_to_9th ::= FIRST */
#line 303 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 1.0; yylhsminor.yy0.suffix = ST; }
#line 1662 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 110: /* first_to_9th ::= SECOND */
#line 304 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 2.0; yylhsminor.yy0.suffix = ND; }
#line 1668 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 111: /* first_to_9th ::= THIRD */
#line 305 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 3.0; yylhsminor.yy0.suffix = RD; }
#line 1674 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 112: /* first_to_9th ::= FOURTH */
#line 306 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 4.0; yylhsminor.yy0.suffix = TH; }
#line 1680 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 113: /* first_to_9th ::= FIFTH */
#line 307 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 5.0; yylhsminor.yy0.suffix = TH; }
#line 1686 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 114: /* first_to_9th ::= SIXTH */
#line 308 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 6.0; yylhsminor.yy0.suffix = TH; }
#line 1692 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 115: /* first_to_9th ::= SEVENTH */
#line 309 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 7.0; yylhsminor.yy0.suffix = TH; }
#line 1698 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 116: /* first_to_9th ::= EIGHTH */
#line 310 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 8.0; yylhsminor.yy0.suffix = TH; }
#line 1704 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 117: /* first_to_9th ::= NINTH */
#line 311 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 9.0; yylhsminor.yy0.suffix = TH; }
#line 1710 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 118: /* tenth_to_19th ::= TENTH */
#line 313 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 10.0; yylhsminor.yy0.suffix = TH; }
#line 1716 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 119: /* tenth_to_19th ::= ELEVENTH */
#line 314 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 11.0; yylhsminor.yy0.suffix = TH; }
#line 1722 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 120: /* tenth_to_19th ::= TWELFTH */
#line 315 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 12.0; yylhsminor.yy0.suffix = TH; }
#line 1728 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 121: /* tenth_to_19th ::= THIRTEENTH */
#line 316 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 13.0; yylhsminor.yy0.suffix = TH; }
#line 1734 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 122: /* tenth_to_19th ::= FOURTEENTH */
#line 317 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 14.0; yylhsminor.yy0.suffix = TH; }
#line 1740 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 123: /* tenth_to_19th ::= FIFTEENTH */
#line 318 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 15.0; yylhsminor.yy0.suffix = TH; }
#line 1746 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 124: /* tenth_to_19th ::= SIXTEENTH */
#line 319 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 16.0; yylhsminor.yy0.suffix = TH; }
#line 1752 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 125: /* tenth_to_19th ::= SEVENTEENTH */
#line 320 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 17.0; yylhsminor.yy0.suffix = TH; }
#line 1758 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 126: /* tenth_to_19th ::= EIGHTEENTH */
#line 321 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 18.0; yylhsminor.yy0.suffix = TH; }
#line 1764 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 127: /* tenth_to_19th ::= NINETEENTH */
#line 322 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 19.0; yylhsminor.yy0.suffix = TH; }
#line 1770 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 128: /* tenth ::= TWENTIETH */
#line 324 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 20.0; yylhsminor.yy0.suffix = TH; }
#line 1776 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 129: /* tenth ::= THIRTIETH */
#line 325 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 30.0; yylhsminor.yy0.suffix = TH; }
#line 1782 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 130: /* tenth ::= FOURTIETH */
#line 326 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 40.0; yylhsminor.yy0.suffix = TH; }
#line 1788 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 131: /* tenth ::= FIFTIETH */
#line 327 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 50.0; yylhsminor.yy0.suffix = TH; }
#line 1794 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 132: /* tenth ::= SIXTIETH */
#line 328 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 60.0; yylhsminor.yy0.suffix = TH; }
#line 1800 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 133: /* tenth ::= SEVENTIETH */
#line 329 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 70.0; yylhsminor.yy0.suffix = TH; }
#line 1806 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 134: /* tenth ::= EIGHTIETH */
#line 330 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 80.0; yylhsminor.yy0.suffix = TH; }
#line 1812 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 135: /* tenth ::= NINETIETH */
#line 331 "parser.yy"
{ yylhsminor.yy0.spos = yymsp[0].minor.yy0.spos; yylhsminor.yy0.epos = yymsp[0].minor.yy0.epos; yylhsminor.yy0.double_value = 90.0; yylhsminor.yy0.suffix = TH; }
#line 1818 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      default:
      /* (136) expr ::= num_ident (OPTIMIZED OUT) */ assert(yyruleno!=136);
      /* (137) expr ::= ident_num (OPTIMIZED OUT) */ assert(yyruleno!=137);
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
#line 22 "parser.yy"
 fprintf(stderr,"Giving up.  Parser is hopelessly lost...\n"); 
#line 1870 "parser.c"
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
#line 1889 "parser.c"
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
