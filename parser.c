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
#define YYNOCODE 125
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
#define YYNSTATE             31
#define YYNRULE              147
#define YY_MAX_SHIFT         30
#define YY_MIN_SHIFTREDUCE   161
#define YY_MAX_SHIFTREDUCE   307
#define YY_MIN_REDUCE        308
#define YY_MAX_REDUCE        454
#define YY_ERROR_ACTION      455
#define YY_ACCEPT_ACTION     456
#define YY_NO_ACTION         457
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
#define YY_ACTTAB_COUNT (800)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   172,  178,   16,  184,  190,  196,    4,  206,  207,  219,
 /*    10 */   224,  225,  226,  227,  228,  229,  230,  231,  232,  233,
 /*    20 */   234,  235,  236,  237,  238,  239,  240,  241,  242,  243,
 /*    30 */   244,  245,  246,  247,  248,  249,  250,  251,  252,  253,
 /*    40 */   254,  255,  256,  257,  258,  259,  260,  261,  262,  263,
 /*    50 */   264,  265,  266,  267,  268,  269,  270,  271,  272,  273,
 /*    60 */   274,  275,  276,  277,  278,  279,  280,  281,  282,  283,
 /*    70 */   284,  285,  286,  287,  288,  289,  290,  291,  292,  293,
 /*    80 */   294,  295,  296,  297,  298,  299,  300,  301,  302,  303,
 /*    90 */   304,  307,  172,  178,   16,  184,  190,  196,    4,  206,
 /*   100 */   207,  219,  224,  225,  226,  227,  228,  229,  230,  231,
 /*   110 */   232,  233,  234,  235,  236,  237,  238,  239,  240,  241,
 /*   120 */   242,  243,  244,  245,  246,  247,  248,  249,  250,  251,
 /*   130 */   252,  253,  254,  255,  256,  257,  258,  259,  260,  261,
 /*   140 */   262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
 /*   150 */   272,  273,  274,  275,  276,  277,  278,  279,  280,  281,
 /*   160 */   282,  283,  284,  285,  286,  287,  288,  289,  290,  291,
 /*   170 */   292,  293,  294,  295,  296,  297,  298,  299,  300,  301,
 /*   180 */   302,  303,  304,  306,  224,  225,  226,  227,  228,  229,
 /*   190 */   230,  231,  232,  233,  234,  235,  236,  237,  238,  239,
 /*   200 */   240,  241,  242,  243,  244,  245,  246,  247,  248,  249,
 /*   210 */   250,  251,  252,  253,  254,  255,  256,  257,  258,  259,
 /*   220 */   260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
 /*   230 */   270,  271,  272,  273,  274,  275,  276,  277,  278,  279,
 /*   240 */   280,  281,  282,  283,  284,  285,  286,  287,  288,  289,
 /*   250 */   290,  291,  292,  293,  294,  295,  296,  297,  298,  299,
 /*   260 */   300,  301,  302,  303,  304,    8,  164,  220,   20,  171,
 /*   270 */     2,   23,    3,   24,    5,   25,    6,   26,    7,  201,
 /*   280 */    18,   12,  223,  209,  210,  211,    9,  222,  243,  244,
 /*   290 */   245,  246,  247,  248,  249,  250,  251,  252,  253,  254,
 /*   300 */   255,  256,  257,  258,  259,  260,  261,  262,  263,  264,
 /*   310 */   265,  266,  267,  268,  269,  270,  271,  272,  273,  274,
 /*   320 */   275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
 /*   330 */   285,  286,  287,  288,  289,  290,  291,  292,  293,  294,
 /*   340 */   295,  296,  297,  298,  299,  300,  301,  302,  303,  304,
 /*   350 */   243,  244,  245,  246,  247,  248,  249,  250,  251,  252,
 /*   360 */   253,  254,  255,  256,  257,  258,  259,  260,  261,  262,
 /*   370 */   263,  264,  265,  266,  267,  268,  269,  270,  271,  272,
 /*   380 */   273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
 /*   390 */   283,  284,  285,  286,  287,  288,  289,  290,  291,  292,
 /*   400 */   293,  294,  295,  296,  297,  298,  299,  300,  301,  302,
 /*   410 */   303,  304,   17,  184,  190,  196,   10,  208,  307,  219,
 /*   420 */   224,  225,  226,  227,  228,  229,  230,  231,  232,  233,
 /*   430 */   234,  235,  236,  237,  238,  239,  240,  241,  242,  243,
 /*   440 */   244,  245,  246,  247,  248,  249,  250,   19,  195,  190,
 /*   450 */   196,   10,  218,   29,  219,  224,  225,  226,  227,  228,
 /*   460 */   229,  230,  231,  232,  233,  234,  235,  236,  237,  238,
 /*   470 */   239,  240,  241,  242,  243,  244,  245,  246,  247,  248,
 /*   480 */   249,  250,   21,  189,  195,  196,   10,  176,  218,  219,
 /*   490 */   224,  225,  226,  227,  228,  229,  230,  231,  232,  233,
 /*   500 */   234,  235,  236,  237,  238,  239,  240,  241,  242,  243,
 /*   510 */   244,  245,  246,  247,  248,  249,  250,   27,  202,  203,
 /*   520 */   217,   10,  182,  194,  219,  224,  225,  226,  227,  228,
 /*   530 */   229,  230,  231,  232,  233,  234,  235,  236,  237,  238,
 /*   540 */   239,  240,  241,  242,  243,  244,  245,  246,  247,  248,
 /*   550 */   249,  250,   11,  166,  188,  168,  224,  225,  226,  227,
 /*   560 */   228,  229,  230,  231,  232,  233,  234,  235,  236,  237,
 /*   570 */   238,  239,  240,  241,  242,  243,  244,  245,  246,  247,
 /*   580 */   248,  249,  250,  224,  225,  226,  227,  228,  229,  230,
 /*   590 */   231,  232,  233,  234,  235,  236,  237,  238,  239,  240,
 /*   600 */   241,  242,  243,  244,  245,  246,  247,  248,  249,  250,
 /*   610 */   224,  225,  226,  227,  228,  229,  230,  231,  232,  251,
 /*   620 */   252,  253,  254,  255,  256,  257,  258,  259,  260,  261,
 /*   630 */   262,  263,  264,  265,  266,  267,  268,  251,  252,  253,
 /*   640 */   254,  255,  256,  257,  258,  259,  260,  261,  262,  263,
 /*   650 */   264,  265,  266,  267,  268,  306,  456,   30,  162,   15,
 /*   660 */     1,   20,  171,    2,   23,    3,   24,    5,   25,    6,
 /*   670 */    26,    7,  201,   18,   12,  223,  209,  210,  211,    9,
 /*   680 */   222,  173,    3,   24,    5,   25,    6,   26,  218,  308,
 /*   690 */    28,   13,  223,  217,  310,  310,    9,  222,  179,    5,
 /*   700 */    25,    6,   26,  310,  310,   28,   13,  223,  310,  310,
 /*   710 */   310,    9,  222,  224,  225,  226,  227,  228,  229,  230,
 /*   720 */   231,  232,  200,  215,   12,  223,  209,  210,  211,  310,
 /*   730 */   222,  185,    6,   26,  310,  310,   28,   13,  223,  310,
 /*   740 */   310,  310,    9,  222,  177,  310,  183,  189,  195,  310,
 /*   750 */   204,  205,  218,  191,  310,  310,   28,   13,  223,  310,
 /*   760 */   310,  310,    9,  222,  198,  310,   14,  310,  209,  210,
 /*   770 */   211,   22,  197,  167,   14,  169,  209,  210,  211,  213,
 /*   780 */    13,  223,  215,   13,  223,  208,  222,  310,  220,  222,
 /*   790 */   212,   13,  223,  183,  189,  195,  310,  222,  310,  218,
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
 /*    90 */    96,   97,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   100 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   110 */    24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
 /*   120 */    34,   35,   36,   37,   38,   39,   40,   41,   42,   43,
 /*   130 */    44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
 /*   140 */    54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
 /*   150 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   160 */    74,   75,   76,   77,   78,   79,   80,   81,   82,   83,
 /*   170 */    84,   85,   86,   87,   88,   89,   90,   91,   92,   93,
 /*   180 */    94,   95,   96,   97,   16,   17,   18,   19,   20,   21,
 /*   190 */    22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
 /*   200 */    32,   33,   34,   35,   36,   37,   38,   39,   40,   41,
 /*   210 */    42,   43,   44,   45,   46,   47,   48,   49,   50,   51,
 /*   220 */    52,   53,   54,   55,   56,   57,   58,   59,   60,   61,
 /*   230 */    62,   63,   64,   65,   66,   67,   68,   69,   70,   71,
 /*   240 */    72,   73,   74,   75,   76,   77,   78,   79,   80,   81,
 /*   250 */    82,   83,   84,   85,   86,   87,   88,   89,   90,   91,
 /*   260 */    92,   93,   94,   95,   96,   12,  102,  121,  104,  105,
 /*   270 */   106,  107,  108,  109,  110,  111,  112,  113,  114,  115,
 /*   280 */   116,  117,  118,  119,  120,  121,  122,  123,   35,   36,
 /*   290 */    37,   38,   39,   40,   41,   42,   43,   44,   45,   46,
 /*   300 */    47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
 /*   310 */    57,   58,   59,   60,   61,   62,   63,   64,   65,   66,
 /*   320 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   330 */    77,   78,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   340 */    87,   88,   89,   90,   91,   92,   93,   94,   95,   96,
 /*   350 */    35,   36,   37,   38,   39,   40,   41,   42,   43,   44,
 /*   360 */    45,   46,   47,   48,   49,   50,   51,   52,   53,   54,
 /*   370 */    55,   56,   57,   58,   59,   60,   61,   62,   63,   64,
 /*   380 */    65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*   390 */    75,   76,   77,   78,   79,   80,   81,   82,   83,   84,
 /*   400 */    85,   86,   87,   88,   89,   90,   91,   92,   93,   94,
 /*   410 */    95,   96,    8,    9,   10,   11,   12,  118,   97,   15,
 /*   420 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   430 */    26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
 /*   440 */    36,   37,   38,   39,   40,   41,   42,    8,   11,   10,
 /*   450 */    11,   12,   15,  103,   15,   16,   17,   18,   19,   20,
 /*   460 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   470 */    31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
 /*   480 */    41,   42,    8,   10,   11,   11,   12,    7,   15,   15,
 /*   490 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*   500 */    26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
 /*   510 */    36,   37,   38,   39,   40,   41,   42,    8,   13,   14,
 /*   520 */    15,   12,    9,   11,   15,   16,   17,   18,   19,   20,
 /*   530 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   540 */    31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
 /*   550 */    41,   42,   12,    2,   10,    4,   16,   17,   18,   19,
 /*   560 */    20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   570 */    30,   31,   32,   33,   34,   35,   36,   37,   38,   39,
 /*   580 */    40,   41,   42,   16,   17,   18,   19,   20,   21,   22,
 /*   590 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   600 */    33,   34,   35,   36,   37,   38,   39,   40,   41,   42,
 /*   610 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   43,
 /*   620 */    44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
 /*   630 */    54,   55,   56,   57,   58,   59,   60,   43,   44,   45,
 /*   640 */    46,   47,   48,   49,   50,   51,   52,   53,   54,   55,
 /*   650 */    56,   57,   58,   59,   60,   97,   99,  100,  101,  102,
 /*   660 */   103,  104,  105,  106,  107,  108,  109,  110,  111,  112,
 /*   670 */   113,  114,  115,  116,  117,  118,  119,  120,  121,  122,
 /*   680 */   123,  107,  108,  109,  110,  111,  112,  113,   15,    0,
 /*   690 */   116,  117,  118,   15,  124,  124,  122,  123,  109,  110,
 /*   700 */   111,  112,  113,  124,  124,  116,  117,  118,  124,  124,
 /*   710 */   124,  122,  123,   16,   17,   18,   19,   20,   21,   22,
 /*   720 */    23,   24,  115,  116,  117,  118,  119,  120,  121,  124,
 /*   730 */   123,  111,  112,  113,  124,  124,  116,  117,  118,  124,
 /*   740 */   124,  124,  122,  123,    7,  124,    9,   10,   11,  124,
 /*   750 */    13,   14,   15,  113,  124,  124,  116,  117,  118,  124,
 /*   760 */   124,  124,  122,  123,  115,  124,  117,  124,  119,  120,
 /*   770 */   121,    1,  115,    3,  117,    5,  119,  120,  121,  116,
 /*   780 */   117,  118,  116,  117,  118,  118,  123,  124,  121,  123,
 /*   790 */   116,  117,  118,    9,   10,   11,  124,  123,  124,   15,
};
#define YY_SHIFT_USE_DFLT (800)
#define YY_SHIFT_COUNT    (30)
#define YY_SHIFT_MIN      (-6)
#define YY_SHIFT_MAX      (784)
static const short yy_shift_ofst[] = {
 /*     0 */    -6,   86,  404,  439,  168,  474,  509,  253,  315,  540,
 /*    10 */   567,  567,  594,  576,  697,  321,  737,  784,  505,  473,
 /*    20 */   770,  437,  551,  480,  513,  544,  512,  673,  678,  558,
 /*    30 */   689,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (15)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (674)
static const short yy_reduce_ofst[] = {
 /*     0 */   557,  164,  574,  589,  607,  620,  640,  649,  657,  663,
 /*    10 */   666,  674,  667,  146,  299,  350,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   452,  455,  321,  327,  455,  333,  339,  346,  455,  361,
 /*    10 */   455,  455,  368,  368,  455,  310,  455,  455,  363,  455,
 /*    20 */   317,  455,  455,  322,  328,  334,  340,  455,  363,  312,
 /*    30 */   455,
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
  "HALF",          "HALVES",        "ZERO",          "TRILLION",    
  "NUMBER",        "BILLION",       "MILLION",       "THOUSAND",    
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
  "one_to_999999999999999",  "first_to_999th",  "trillions",     "one_to_999999999999",
  "billions",      "one_to_999999999",  "millions",      "one_to_999999",
  "thousands",     "one_to_999",    "hundredths",    "first_to_99th",
  "one_to_99",     "tens",          "one_to_9",      "tenths",      
  "tenth_to_19th",  "first_to_9th",  "hundreds",      "ten_to_19",   
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
 /*  10 */ "final_number ::= first_to_999th",
 /*  11 */ "final_number ::= ZERO",
 /*  12 */ "one_to_999999999999999 ::= trillions one_to_999999999999",
 /*  13 */ "one_to_999999999999999 ::= trillions",
 /*  14 */ "one_to_999999999999999 ::= one_to_999999999999",
 /*  15 */ "trillions ::= one_to_999999999999 TRILLION",
 /*  16 */ "trillions ::= NUMBER TRILLION",
 /*  17 */ "trillions ::= TRILLION",
 /*  18 */ "one_to_999999999999 ::= billions one_to_999999999",
 /*  19 */ "one_to_999999999999 ::= billions",
 /*  20 */ "one_to_999999999999 ::= one_to_999999999",
 /*  21 */ "billions ::= one_to_999999999 BILLION",
 /*  22 */ "billions ::= NUMBER BILLION",
 /*  23 */ "billions ::= BILLION",
 /*  24 */ "one_to_999999999 ::= millions one_to_999999",
 /*  25 */ "one_to_999999999 ::= millions",
 /*  26 */ "one_to_999999999 ::= one_to_999999",
 /*  27 */ "millions ::= one_to_999999 MILLION",
 /*  28 */ "millions ::= NUMBER MILLION",
 /*  29 */ "millions ::= MILLION",
 /*  30 */ "one_to_999999 ::= thousands one_to_999",
 /*  31 */ "one_to_999999 ::= thousands",
 /*  32 */ "one_to_999999 ::= one_to_999",
 /*  33 */ "thousands ::= one_to_999 THOUSAND",
 /*  34 */ "thousands ::= NUMBER THOUSAND",
 /*  35 */ "thousands ::= THOUSAND",
 /*  36 */ "first_to_999th ::= hundredths AND first_to_99th",
 /*  37 */ "first_to_999th ::= hundredths first_to_99th",
 /*  38 */ "first_to_999th ::= hundredths",
 /*  39 */ "first_to_999th ::= AND first_to_99th",
 /*  40 */ "first_to_999th ::= first_to_99th",
 /*  41 */ "hundredths ::= one_to_99 HUNDREDTH",
 /*  42 */ "hundredths ::= one_to_99 HUNDREDTHS",
 /*  43 */ "hundredths ::= NUMBER HUNDREDTH",
 /*  44 */ "hundredths ::= NUMBER HUNDREDTHS",
 /*  45 */ "hundredths ::= HUNDREDTH",
 /*  46 */ "hundredths ::= HUNDREDTHS",
 /*  47 */ "first_to_99th ::= tens one_to_9",
 /*  48 */ "first_to_99th ::= tenths",
 /*  49 */ "first_to_99th ::= tenth_to_19th",
 /*  50 */ "first_to_99th ::= first_to_9th",
 /*  51 */ "one_to_999 ::= hundreds AND one_to_99",
 /*  52 */ "one_to_999 ::= hundreds one_to_99",
 /*  53 */ "one_to_999 ::= hundreds",
 /*  54 */ "one_to_999 ::= AND one_to_99",
 /*  55 */ "one_to_999 ::= one_to_99",
 /*  56 */ "hundreds ::= one_to_99 HUNDRED",
 /*  57 */ "hundreds ::= NUMBER HUNDRED",
 /*  58 */ "hundreds ::= HUNDRED",
 /*  59 */ "one_to_99 ::= tens first_to_9th",
 /*  60 */ "one_to_99 ::= tens",
 /*  61 */ "one_to_99 ::= ten_to_19",
 /*  62 */ "one_to_99 ::= one_to_9",
 /*  63 */ "one_to_9 ::= ONE",
 /*  64 */ "one_to_9 ::= TWO",
 /*  65 */ "one_to_9 ::= THREE",
 /*  66 */ "one_to_9 ::= FOUR",
 /*  67 */ "one_to_9 ::= FIVE",
 /*  68 */ "one_to_9 ::= SIX",
 /*  69 */ "one_to_9 ::= SEVEN",
 /*  70 */ "one_to_9 ::= EIGHT",
 /*  71 */ "one_to_9 ::= NINE",
 /*  72 */ "ten_to_19 ::= TEN",
 /*  73 */ "ten_to_19 ::= ELEVEN",
 /*  74 */ "ten_to_19 ::= TWELVE",
 /*  75 */ "ten_to_19 ::= THIRTEEN",
 /*  76 */ "ten_to_19 ::= FOURTEEN",
 /*  77 */ "ten_to_19 ::= FIFTEEN",
 /*  78 */ "ten_to_19 ::= SIXTEEN",
 /*  79 */ "ten_to_19 ::= SEVENTEEN",
 /*  80 */ "ten_to_19 ::= EIGHTEEN",
 /*  81 */ "ten_to_19 ::= NINETEEN",
 /*  82 */ "tens ::= TWENTY",
 /*  83 */ "tens ::= THIRTY",
 /*  84 */ "tens ::= FORTY",
 /*  85 */ "tens ::= FIFTY",
 /*  86 */ "tens ::= SIXTY",
 /*  87 */ "tens ::= SEVENTY",
 /*  88 */ "tens ::= EIGHTY",
 /*  89 */ "tens ::= NINETY",
 /*  90 */ "first_to_9th ::= FIRST",
 /*  91 */ "first_to_9th ::= FIRSTS",
 /*  92 */ "first_to_9th ::= SECOND",
 /*  93 */ "first_to_9th ::= SECONDS",
 /*  94 */ "first_to_9th ::= THIRD",
 /*  95 */ "first_to_9th ::= THIRDS",
 /*  96 */ "first_to_9th ::= FOURTH",
 /*  97 */ "first_to_9th ::= FOURTHS",
 /*  98 */ "first_to_9th ::= FIFTH",
 /*  99 */ "first_to_9th ::= FIFTHS",
 /* 100 */ "first_to_9th ::= SIXTH",
 /* 101 */ "first_to_9th ::= SIXTHS",
 /* 102 */ "first_to_9th ::= SEVENTH",
 /* 103 */ "first_to_9th ::= SEVENTHS",
 /* 104 */ "first_to_9th ::= EIGHTH",
 /* 105 */ "first_to_9th ::= EIGHTHS",
 /* 106 */ "first_to_9th ::= NINTH",
 /* 107 */ "first_to_9th ::= NINTHS",
 /* 108 */ "tenth_to_19th ::= TENTH",
 /* 109 */ "tenth_to_19th ::= TENTHS",
 /* 110 */ "tenth_to_19th ::= ELEVENTH",
 /* 111 */ "tenth_to_19th ::= ELEVENTHS",
 /* 112 */ "tenth_to_19th ::= TWELFTH",
 /* 113 */ "tenth_to_19th ::= TWELFTHS",
 /* 114 */ "tenth_to_19th ::= THIRTEENTH",
 /* 115 */ "tenth_to_19th ::= THIRTEENTHS",
 /* 116 */ "tenth_to_19th ::= FOURTEENTH",
 /* 117 */ "tenth_to_19th ::= FOURTEENTHS",
 /* 118 */ "tenth_to_19th ::= FIFTEENTH",
 /* 119 */ "tenth_to_19th ::= FIFTEENTHS",
 /* 120 */ "tenth_to_19th ::= SIXTEENTH",
 /* 121 */ "tenth_to_19th ::= SIXTEENTHS",
 /* 122 */ "tenth_to_19th ::= SEVENTEENTH",
 /* 123 */ "tenth_to_19th ::= SEVENTEENTHS",
 /* 124 */ "tenth_to_19th ::= EIGHTEENTH",
 /* 125 */ "tenth_to_19th ::= EIGHTEENTHS",
 /* 126 */ "tenth_to_19th ::= NINETEENTH",
 /* 127 */ "tenth_to_19th ::= NINETEENTHS",
 /* 128 */ "tenths ::= TWENTIETH",
 /* 129 */ "tenths ::= TWENTIETHS",
 /* 130 */ "tenths ::= THIRTIETH",
 /* 131 */ "tenths ::= THIRTIETHS",
 /* 132 */ "tenths ::= FOURTIETH",
 /* 133 */ "tenths ::= FOURTIETHS",
 /* 134 */ "tenths ::= FIFTIETH",
 /* 135 */ "tenths ::= FIFTIETHS",
 /* 136 */ "tenths ::= SIXTIETH",
 /* 137 */ "tenths ::= SIXTIETHS",
 /* 138 */ "tenths ::= SEVENTIETH",
 /* 139 */ "tenths ::= SEVENTIETHS",
 /* 140 */ "tenths ::= EIGHTIETH",
 /* 141 */ "tenths ::= EIGHTIETHS",
 /* 142 */ "tenths ::= NINETIETH",
 /* 143 */ "tenths ::= NINETIETHS",
 /* 144 */ "expr ::=",
 /* 145 */ "identifiers ::= identifiers CHARACTERS",
 /* 146 */ "identifiers ::= CHARACTERS",
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
  { 99, 1 },
  { 100, 1 },
  { 100, 1 },
  { 101, 2 },
  { 101, 2 },
  { 102, 3 },
  { 102, 2 },
  { 102, 3 },
  { 102, 2 },
  { 102, 1 },
  { 102, 1 },
  { 102, 1 },
  { 104, 2 },
  { 104, 1 },
  { 104, 1 },
  { 106, 2 },
  { 106, 2 },
  { 106, 1 },
  { 107, 2 },
  { 107, 1 },
  { 107, 1 },
  { 108, 2 },
  { 108, 2 },
  { 108, 1 },
  { 109, 2 },
  { 109, 1 },
  { 109, 1 },
  { 110, 2 },
  { 110, 2 },
  { 110, 1 },
  { 111, 2 },
  { 111, 1 },
  { 111, 1 },
  { 112, 2 },
  { 112, 2 },
  { 112, 1 },
  { 105, 3 },
  { 105, 2 },
  { 105, 1 },
  { 105, 2 },
  { 105, 1 },
  { 114, 2 },
  { 114, 2 },
  { 114, 2 },
  { 114, 2 },
  { 114, 1 },
  { 114, 1 },
  { 115, 2 },
  { 115, 1 },
  { 115, 1 },
  { 115, 1 },
  { 113, 3 },
  { 113, 2 },
  { 113, 1 },
  { 113, 2 },
  { 113, 1 },
  { 122, 2 },
  { 122, 2 },
  { 122, 1 },
  { 116, 2 },
  { 116, 1 },
  { 116, 1 },
  { 116, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 123, 1 },
  { 123, 1 },
  { 123, 1 },
  { 123, 1 },
  { 123, 1 },
  { 123, 1 },
  { 123, 1 },
  { 123, 1 },
  { 123, 1 },
  { 123, 1 },
  { 117, 1 },
  { 117, 1 },
  { 117, 1 },
  { 117, 1 },
  { 117, 1 },
  { 117, 1 },
  { 117, 1 },
  { 117, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 119, 1 },
  { 100, 0 },
  { 103, 2 },
  { 103, 1 },
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
#line 1261 "parser.c"
        break;
      case 1: /* expr ::= sentence */
      case 2: /* expr ::= final_number */ yytestcase(yyruleno==2);
      case 10: /* final_number ::= first_to_999th */ yytestcase(yyruleno==10);
      case 38: /* first_to_999th ::= hundredths */ yytestcase(yyruleno==38);
      case 40: /* first_to_999th ::= first_to_99th */ yytestcase(yyruleno==40);
      case 48: /* first_to_99th ::= tenths */ yytestcase(yyruleno==48);
      case 49: /* first_to_99th ::= tenth_to_19th */ yytestcase(yyruleno==49);
      case 50: /* first_to_99th ::= first_to_9th */ yytestcase(yyruleno==50);
#line 60 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1273 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 3: /* sentence ::= identifiers final_number */
      case 39: /* first_to_999th ::= AND first_to_99th */ yytestcase(yyruleno==39);
#line 64 "parser.yy"
{ yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; yymsp[-1].minor.yy0.suffix = yymsp[0].minor.yy0.suffix; }
#line 1280 "parser.c"
        break;
      case 4: /* sentence ::= final_number identifiers */
#line 65 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[-1].minor.yy0.suffix; }
#line 1285 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 5: /* final_number ::= one_to_999999999999999 AND_A QUARTER */
#line 67 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.25; }
#line 1291 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 6: /* final_number ::= one_to_999999999999999 QUARTERS */
#line 68 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 4.0; }
#line 1297 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 7: /* final_number ::= one_to_999999999999999 AND_A HALF */
#line 69 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + 0.5; }
#line 1303 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 8: /* final_number ::= one_to_999999999999999 HALVES */
#line 70 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value / 2.0; }
#line 1309 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 9: /* final_number ::= one_to_999999999999999 */
      case 13: /* one_to_999999999999999 ::= trillions */ yytestcase(yyruleno==13);
      case 14: /* one_to_999999999999999 ::= one_to_999999999999 */ yytestcase(yyruleno==14);
      case 19: /* one_to_999999999999 ::= billions */ yytestcase(yyruleno==19);
      case 20: /* one_to_999999999999 ::= one_to_999999999 */ yytestcase(yyruleno==20);
      case 25: /* one_to_999999999 ::= millions */ yytestcase(yyruleno==25);
      case 26: /* one_to_999999999 ::= one_to_999999 */ yytestcase(yyruleno==26);
      case 31: /* one_to_999999 ::= thousands */ yytestcase(yyruleno==31);
      case 32: /* one_to_999999 ::= one_to_999 */ yytestcase(yyruleno==32);
      case 53: /* one_to_999 ::= hundreds */ yytestcase(yyruleno==53);
      case 55: /* one_to_999 ::= one_to_99 */ yytestcase(yyruleno==55);
      case 60: /* one_to_99 ::= tens */ yytestcase(yyruleno==60);
      case 61: /* one_to_99 ::= ten_to_19 */ yytestcase(yyruleno==61);
      case 62: /* one_to_99 ::= one_to_9 */ yytestcase(yyruleno==62);
#line 71 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1328 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 11: /* final_number ::= ZERO */
#line 73 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 0.0; }
#line 1334 "parser.c"
        break;
      case 12: /* one_to_999999999999999 ::= trillions one_to_999999999999 */
      case 18: /* one_to_999999999999 ::= billions one_to_999999999 */ yytestcase(yyruleno==18);
      case 24: /* one_to_999999999 ::= millions one_to_999999 */ yytestcase(yyruleno==24);
      case 30: /* one_to_999999 ::= thousands one_to_999 */ yytestcase(yyruleno==30);
      case 52: /* one_to_999 ::= hundreds one_to_99 */ yytestcase(yyruleno==52);
      case 59: /* one_to_99 ::= tens first_to_9th */ yytestcase(yyruleno==59);
#line 75 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1344 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 15: /* trillions ::= one_to_999999999999 TRILLION */
      case 16: /* trillions ::= NUMBER TRILLION */ yytestcase(yyruleno==16);
#line 79 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000000.0; }
#line 1351 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 17: /* trillions ::= TRILLION */
#line 81 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000000000.0; }
#line 1357 "parser.c"
        break;
      case 21: /* billions ::= one_to_999999999 BILLION */
      case 22: /* billions ::= NUMBER BILLION */ yytestcase(yyruleno==22);
#line 89 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000000.0; }
#line 1363 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 23: /* billions ::= BILLION */
#line 91 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000000.0; }
#line 1369 "parser.c"
        break;
      case 27: /* millions ::= one_to_999999 MILLION */
      case 28: /* millions ::= NUMBER MILLION */ yytestcase(yyruleno==28);
#line 99 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000000.0; }
#line 1375 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 29: /* millions ::= MILLION */
#line 101 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000000.0; }
#line 1381 "parser.c"
        break;
      case 33: /* thousands ::= one_to_999 THOUSAND */
      case 34: /* thousands ::= NUMBER THOUSAND */ yytestcase(yyruleno==34);
#line 109 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 1000.0; }
#line 1387 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 35: /* thousands ::= THOUSAND */
#line 111 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1000.0; }
#line 1393 "parser.c"
        break;
      case 36: /* first_to_999th ::= hundredths AND first_to_99th */
#line 117 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[-2].minor.yy0.suffix; }
#line 1398 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 37: /* first_to_999th ::= hundredths first_to_99th */
      case 47: /* first_to_99th ::= tens one_to_9 */ yytestcase(yyruleno==47);
#line 118 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; yylhsminor.yy0.suffix = yymsp[-1].minor.yy0.suffix; }
#line 1405 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 41: /* hundredths ::= one_to_99 HUNDREDTH */
      case 43: /* hundredths ::= NUMBER HUNDREDTH */ yytestcase(yyruleno==43);
#line 123 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; yylhsminor.yy0.suffix = TH; }
#line 1412 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 42: /* hundredths ::= one_to_99 HUNDREDTHS */
      case 44: /* hundredths ::= NUMBER HUNDREDTHS */ yytestcase(yyruleno==44);
#line 124 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; yylhsminor.yy0.suffix = THS; }
#line 1419 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 45: /* hundredths ::= HUNDREDTH */
#line 127 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 100.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1425 "parser.c"
        break;
      case 46: /* hundredths ::= HUNDREDTHS */
#line 128 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 100.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1430 "parser.c"
        break;
      case 51: /* one_to_999 ::= hundreds AND one_to_99 */
#line 139 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 1435 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 54: /* one_to_999 ::= AND one_to_99 */
#line 142 "parser.yy"
{ yymsp[-1].minor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 1441 "parser.c"
        break;
      case 56: /* hundreds ::= one_to_99 HUNDRED */
      case 57: /* hundreds ::= NUMBER HUNDRED */ yytestcase(yyruleno==57);
#line 145 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-1].minor.yy0.double_value * 100.0; }
#line 1447 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 58: /* hundreds ::= HUNDRED */
#line 147 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 100.0; }
#line 1453 "parser.c"
        break;
      case 63: /* one_to_9 ::= ONE */
#line 158 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1.0; }
#line 1458 "parser.c"
        break;
      case 64: /* one_to_9 ::= TWO */
#line 159 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 2.0; }
#line 1463 "parser.c"
        break;
      case 65: /* one_to_9 ::= THREE */
#line 160 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 3.0; }
#line 1468 "parser.c"
        break;
      case 66: /* one_to_9 ::= FOUR */
#line 161 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 4.0; }
#line 1473 "parser.c"
        break;
      case 67: /* one_to_9 ::= FIVE */
#line 162 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 5.0; }
#line 1478 "parser.c"
        break;
      case 68: /* one_to_9 ::= SIX */
#line 163 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 6.0; }
#line 1483 "parser.c"
        break;
      case 69: /* one_to_9 ::= SEVEN */
#line 164 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 7.0; }
#line 1488 "parser.c"
        break;
      case 70: /* one_to_9 ::= EIGHT */
#line 165 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 8.0; }
#line 1493 "parser.c"
        break;
      case 71: /* one_to_9 ::= NINE */
#line 166 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 9.0; }
#line 1498 "parser.c"
        break;
      case 72: /* ten_to_19 ::= TEN */
#line 168 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 10.0; }
#line 1503 "parser.c"
        break;
      case 73: /* ten_to_19 ::= ELEVEN */
#line 169 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 11.0; }
#line 1508 "parser.c"
        break;
      case 74: /* ten_to_19 ::= TWELVE */
#line 170 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 12.0; }
#line 1513 "parser.c"
        break;
      case 75: /* ten_to_19 ::= THIRTEEN */
#line 171 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 13.0; }
#line 1518 "parser.c"
        break;
      case 76: /* ten_to_19 ::= FOURTEEN */
#line 172 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 14.0; }
#line 1523 "parser.c"
        break;
      case 77: /* ten_to_19 ::= FIFTEEN */
#line 173 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 15.0; }
#line 1528 "parser.c"
        break;
      case 78: /* ten_to_19 ::= SIXTEEN */
#line 174 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 16.0; }
#line 1533 "parser.c"
        break;
      case 79: /* ten_to_19 ::= SEVENTEEN */
#line 175 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 17.0; }
#line 1538 "parser.c"
        break;
      case 80: /* ten_to_19 ::= EIGHTEEN */
#line 176 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 18.0; }
#line 1543 "parser.c"
        break;
      case 81: /* ten_to_19 ::= NINETEEN */
#line 177 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 19.0; }
#line 1548 "parser.c"
        break;
      case 82: /* tens ::= TWENTY */
#line 179 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 20.0; }
#line 1553 "parser.c"
        break;
      case 83: /* tens ::= THIRTY */
#line 180 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 30.0; }
#line 1558 "parser.c"
        break;
      case 84: /* tens ::= FORTY */
#line 181 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 40.0; }
#line 1563 "parser.c"
        break;
      case 85: /* tens ::= FIFTY */
#line 182 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 50.0; }
#line 1568 "parser.c"
        break;
      case 86: /* tens ::= SIXTY */
#line 183 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 60.0; }
#line 1573 "parser.c"
        break;
      case 87: /* tens ::= SEVENTY */
#line 184 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 70.0; }
#line 1578 "parser.c"
        break;
      case 88: /* tens ::= EIGHTY */
#line 185 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 80.0; }
#line 1583 "parser.c"
        break;
      case 89: /* tens ::= NINETY */
#line 186 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 90.0; }
#line 1588 "parser.c"
        break;
      case 90: /* first_to_9th ::= FIRST */
#line 188 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1.0; yymsp[0].minor.yy0.suffix = ST; }
#line 1593 "parser.c"
        break;
      case 91: /* first_to_9th ::= FIRSTS */
#line 189 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 1.0; yymsp[0].minor.yy0.suffix = STS; }
#line 1598 "parser.c"
        break;
      case 92: /* first_to_9th ::= SECOND */
#line 190 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 2.0; yymsp[0].minor.yy0.suffix = ND; }
#line 1603 "parser.c"
        break;
      case 93: /* first_to_9th ::= SECONDS */
#line 191 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 2.0; yymsp[0].minor.yy0.suffix = NDS; }
#line 1608 "parser.c"
        break;
      case 94: /* first_to_9th ::= THIRD */
#line 192 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 3.0; yymsp[0].minor.yy0.suffix = RD; }
#line 1613 "parser.c"
        break;
      case 95: /* first_to_9th ::= THIRDS */
#line 193 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 3.0; yymsp[0].minor.yy0.suffix = RDS; }
#line 1618 "parser.c"
        break;
      case 96: /* first_to_9th ::= FOURTH */
#line 194 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 4.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1623 "parser.c"
        break;
      case 97: /* first_to_9th ::= FOURTHS */
#line 195 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 4.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1628 "parser.c"
        break;
      case 98: /* first_to_9th ::= FIFTH */
#line 196 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 5.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1633 "parser.c"
        break;
      case 99: /* first_to_9th ::= FIFTHS */
#line 197 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 5.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1638 "parser.c"
        break;
      case 100: /* first_to_9th ::= SIXTH */
#line 198 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 6.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1643 "parser.c"
        break;
      case 101: /* first_to_9th ::= SIXTHS */
#line 199 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 6.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1648 "parser.c"
        break;
      case 102: /* first_to_9th ::= SEVENTH */
#line 200 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 7.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1653 "parser.c"
        break;
      case 103: /* first_to_9th ::= SEVENTHS */
#line 201 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 7.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1658 "parser.c"
        break;
      case 104: /* first_to_9th ::= EIGHTH */
#line 202 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 8.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1663 "parser.c"
        break;
      case 105: /* first_to_9th ::= EIGHTHS */
#line 203 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 8.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1668 "parser.c"
        break;
      case 106: /* first_to_9th ::= NINTH */
#line 204 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 9.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1673 "parser.c"
        break;
      case 107: /* first_to_9th ::= NINTHS */
#line 205 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 9.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1678 "parser.c"
        break;
      case 108: /* tenth_to_19th ::= TENTH */
#line 207 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 10.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1683 "parser.c"
        break;
      case 109: /* tenth_to_19th ::= TENTHS */
#line 208 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 10.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1688 "parser.c"
        break;
      case 110: /* tenth_to_19th ::= ELEVENTH */
#line 209 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 11.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1693 "parser.c"
        break;
      case 111: /* tenth_to_19th ::= ELEVENTHS */
#line 210 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 11.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1698 "parser.c"
        break;
      case 112: /* tenth_to_19th ::= TWELFTH */
#line 211 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 12.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1703 "parser.c"
        break;
      case 113: /* tenth_to_19th ::= TWELFTHS */
#line 212 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 12.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1708 "parser.c"
        break;
      case 114: /* tenth_to_19th ::= THIRTEENTH */
#line 213 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 13.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1713 "parser.c"
        break;
      case 115: /* tenth_to_19th ::= THIRTEENTHS */
#line 214 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 13.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1718 "parser.c"
        break;
      case 116: /* tenth_to_19th ::= FOURTEENTH */
#line 215 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 14.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1723 "parser.c"
        break;
      case 117: /* tenth_to_19th ::= FOURTEENTHS */
#line 216 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 14.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1728 "parser.c"
        break;
      case 118: /* tenth_to_19th ::= FIFTEENTH */
#line 217 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 15.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1733 "parser.c"
        break;
      case 119: /* tenth_to_19th ::= FIFTEENTHS */
#line 218 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 15.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1738 "parser.c"
        break;
      case 120: /* tenth_to_19th ::= SIXTEENTH */
#line 219 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 16.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1743 "parser.c"
        break;
      case 121: /* tenth_to_19th ::= SIXTEENTHS */
#line 220 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 16.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1748 "parser.c"
        break;
      case 122: /* tenth_to_19th ::= SEVENTEENTH */
#line 221 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 17.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1753 "parser.c"
        break;
      case 123: /* tenth_to_19th ::= SEVENTEENTHS */
#line 222 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 17.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1758 "parser.c"
        break;
      case 124: /* tenth_to_19th ::= EIGHTEENTH */
#line 223 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 18.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1763 "parser.c"
        break;
      case 125: /* tenth_to_19th ::= EIGHTEENTHS */
#line 224 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 18.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1768 "parser.c"
        break;
      case 126: /* tenth_to_19th ::= NINETEENTH */
#line 225 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 19.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1773 "parser.c"
        break;
      case 127: /* tenth_to_19th ::= NINETEENTHS */
#line 226 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 19.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1778 "parser.c"
        break;
      case 128: /* tenths ::= TWENTIETH */
#line 228 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 20.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1783 "parser.c"
        break;
      case 129: /* tenths ::= TWENTIETHS */
#line 229 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 20.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1788 "parser.c"
        break;
      case 130: /* tenths ::= THIRTIETH */
#line 230 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 30.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1793 "parser.c"
        break;
      case 131: /* tenths ::= THIRTIETHS */
#line 231 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 30.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1798 "parser.c"
        break;
      case 132: /* tenths ::= FOURTIETH */
#line 232 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 40.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1803 "parser.c"
        break;
      case 133: /* tenths ::= FOURTIETHS */
#line 233 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 40.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1808 "parser.c"
        break;
      case 134: /* tenths ::= FIFTIETH */
#line 234 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 50.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1813 "parser.c"
        break;
      case 135: /* tenths ::= FIFTIETHS */
#line 235 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 50.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1818 "parser.c"
        break;
      case 136: /* tenths ::= SIXTIETH */
#line 236 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 60.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1823 "parser.c"
        break;
      case 137: /* tenths ::= SIXTIETHS */
#line 237 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 60.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1828 "parser.c"
        break;
      case 138: /* tenths ::= SEVENTIETH */
#line 238 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 70.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1833 "parser.c"
        break;
      case 139: /* tenths ::= SEVENTIETHS */
#line 239 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 70.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1838 "parser.c"
        break;
      case 140: /* tenths ::= EIGHTIETH */
#line 240 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 80.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1843 "parser.c"
        break;
      case 141: /* tenths ::= EIGHTIETHS */
#line 241 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 80.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1848 "parser.c"
        break;
      case 142: /* tenths ::= NINETIETH */
#line 242 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 90.0; yymsp[0].minor.yy0.suffix = TH; }
#line 1853 "parser.c"
        break;
      case 143: /* tenths ::= NINETIETHS */
#line 243 "parser.yy"
{ yymsp[0].minor.yy0.double_value = 90.0; yymsp[0].minor.yy0.suffix = THS; }
#line 1858 "parser.c"
        break;
      default:
      /* (144) expr ::= (OPTIMIZED OUT) */ assert(yyruleno!=144);
      /* (145) identifiers ::= identifiers CHARACTERS */ yytestcase(yyruleno==145);
      /* (146) identifiers ::= CHARACTERS */ yytestcase(yyruleno==146);
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
#line 1907 "parser.c"
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
#line 1927 "parser.c"
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
