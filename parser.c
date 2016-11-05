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
#define YYNOCODE 64
#define YYACTIONTYPE unsigned char
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
#define YYNSTATE             10
#define YYNRULE              69
#define YY_MAX_SHIFT         9
#define YY_MIN_SHIFTREDUCE   73
#define YY_MAX_SHIFTREDUCE   141
#define YY_MIN_REDUCE        142
#define YY_MAX_REDUCE        210
#define YY_ERROR_ACTION      211
#define YY_ACCEPT_ACTION     212
#define YY_NO_ACTION         213
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
#define YY_ACTTAB_COUNT (193)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*    10 */    99,  100,  101,  102,  103,  104,  105,  106,  107,  108,
 /*    20 */   109,  110,  111,  112,  113,  114,  115,  116,  117,  118,
 /*    30 */   119,  120,  121,  122,  123,  124,  125,  126,  127,  128,
 /*    40 */   129,  130,  131,  132,   89,   90,   91,   92,   93,   94,
 /*    50 */    95,   96,   97,   98,   99,  100,  101,  102,  103,  104,
 /*    60 */   105,  106,  107,  108,  109,  110,  111,  112,  113,  114,
 /*    70 */   115,  116,  145,  139,  140,   84,   85,  122,  123,  124,
 /*    80 */   125,  126,  127,  128,  129,  130,  131,  133,   89,   90,
 /*    90 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   100 */   101,  102,  103,  104,  105,  106,  107,  108,  109,  110,
 /*   110 */   111,  112,  113,  114,  115,  116,  143,  139,  140,  139,
 /*   120 */   140,  122,  123,  124,  125,  126,  127,  128,  129,  130,
 /*   130 */   131,   89,   90,   91,   92,   93,   94,   95,   96,   97,
 /*   140 */   212,    9,    7,   81,    5,    2,    4,   80,    1,   82,
 /*   150 */    83,    8,   86,   88,   87,   77,    3,   77,  142,  144,
 /*   160 */    77,   77,   77,   77,  122,  123,  124,  125,  126,  127,
 /*   170 */   128,  129,  130,  131,    6,  144,  144,   79,  144,   82,
 /*   180 */    83,    8,   86,   88,   87,  117,  118,  119,  120,  121,
 /*   190 */   144,  139,  140,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*    10 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*    20 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*    30 */    33,   34,   35,   36,   37,   38,   39,   40,   41,   42,
 /*    40 */    43,   44,   45,   46,    3,    4,    5,    6,    7,    8,
 /*    50 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*    60 */    19,   20,   21,   22,   23,   24,   25,   26,   27,   28,
 /*    70 */    29,   30,    0,    1,    2,   60,   61,   36,   37,   38,
 /*    80 */    39,   40,   41,   42,   43,   44,   45,   46,    3,    4,
 /*    90 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   100 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*   110 */    25,   26,   27,   28,   29,   30,    0,    1,    2,    1,
 /*   120 */     2,   36,   37,   38,   39,   40,   41,   42,   43,   44,
 /*   130 */    45,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*   140 */    48,   49,   50,   56,   52,   53,   51,   55,   51,   57,
 /*   150 */    58,   59,   60,   61,   62,   54,   51,   56,    0,   63,
 /*   160 */    59,   60,   61,   62,   36,   37,   38,   39,   40,   41,
 /*   170 */    42,   43,   44,   45,   52,   63,   63,   55,   63,   57,
 /*   180 */    58,   59,   60,   61,   62,   31,   32,   33,   34,   35,
 /*   190 */     0,    1,    2,
};
#define YY_SHIFT_USE_DFLT (193)
#define YY_SHIFT_COUNT    (9)
#define YY_SHIFT_MIN      (-3)
#define YY_SHIFT_MAX      (190)
static const short yy_shift_ofst[] = {
 /*     0 */    41,   85,   -3,  128,  154,   72,  116,  190,  118,  158,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (8)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (122)
static const signed char yy_reduce_ofst[] = {
 /*     0 */    92,  122,  101,   15,   87,   95,   95,   97,  105,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   211,  211,  147,  211,  211,  210,  210,  210,  210,  211,
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
  "$",             "WHITESPACE",    "HYPHEN",        "ONE",         
  "TWO",           "THREE",         "FOUR",          "FIVE",        
  "SIX",           "SEVEN",         "EIGHT",         "NINE",        
  "ZERO",          "TEN",           "ELEVEN",        "TWELVE",      
  "THIRTEEN",      "FOURTEEN",      "FIFTEEN",       "SIXTEEN",     
  "SEVENTEEN",     "EIGHTEEN",      "NINETEEN",      "TWENTY",      
  "THIRTY",        "FORTY",         "FIFTY",         "SIXTY",       
  "SEVENTY",       "EIGHTY",        "NINETY",        "HUNDRED",     
  "THOUSAND",      "MILLION",       "BILLION",       "TRILLION",    
  "FIRST",         "THIRD",         "FOURTH",        "FIFTH",       
  "SIXTH",         "SEVENTH",       "EIGHTH",        "NINTH",       
  "HALF",          "QUARTER",       "CHARACTER",     "error",       
  "program",       "expr",          "combo",         "separator",   
  "prefix",        "identifier",    "any_token",     "group",       
  "place",         "double_digit",  "single_digit",  "ten_prefix",  
  "single_num",    "single_ordinal",  "direct_num",  
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= expr",
 /*   1 */ "expr ::= combo separator prefix",
 /*   2 */ "expr ::= combo",
 /*   3 */ "expr ::= prefix",
 /*   4 */ "expr ::= identifier any_token",
 /*   5 */ "expr ::= identifier",
 /*   6 */ "combo ::= combo separator group",
 /*   7 */ "combo ::= group",
 /*   8 */ "group ::= prefix separator place",
 /*   9 */ "prefix ::= double_digit",
 /*  10 */ "prefix ::= single_digit",
 /*  11 */ "double_digit ::= ten_prefix separator single_num",
 /*  12 */ "double_digit ::= ten_prefix separator single_ordinal",
 /*  13 */ "single_digit ::= single_num",
 /*  14 */ "single_digit ::= direct_num",
 /*  15 */ "single_digit ::= single_ordinal",
 /*  16 */ "single_num ::= ONE",
 /*  17 */ "single_num ::= TWO",
 /*  18 */ "single_num ::= THREE",
 /*  19 */ "single_num ::= FOUR",
 /*  20 */ "single_num ::= FIVE",
 /*  21 */ "single_num ::= SIX",
 /*  22 */ "single_num ::= SEVEN",
 /*  23 */ "single_num ::= EIGHT",
 /*  24 */ "single_num ::= NINE",
 /*  25 */ "direct_num ::= ZERO",
 /*  26 */ "direct_num ::= TEN",
 /*  27 */ "direct_num ::= ELEVEN",
 /*  28 */ "direct_num ::= TWELVE",
 /*  29 */ "direct_num ::= THIRTEEN",
 /*  30 */ "direct_num ::= FOURTEEN",
 /*  31 */ "direct_num ::= FIFTEEN",
 /*  32 */ "direct_num ::= SIXTEEN",
 /*  33 */ "direct_num ::= SEVENTEEN",
 /*  34 */ "direct_num ::= EIGHTEEN",
 /*  35 */ "direct_num ::= NINETEEN",
 /*  36 */ "ten_prefix ::= TWENTY",
 /*  37 */ "ten_prefix ::= THIRTY",
 /*  38 */ "ten_prefix ::= FORTY",
 /*  39 */ "ten_prefix ::= FIFTY",
 /*  40 */ "ten_prefix ::= SIXTY",
 /*  41 */ "ten_prefix ::= SEVENTY",
 /*  42 */ "ten_prefix ::= EIGHTY",
 /*  43 */ "ten_prefix ::= NINETY",
 /*  44 */ "place ::= HUNDRED",
 /*  45 */ "place ::= THOUSAND",
 /*  46 */ "place ::= MILLION",
 /*  47 */ "place ::= BILLION",
 /*  48 */ "place ::= TRILLION",
 /*  49 */ "single_ordinal ::= FIRST",
 /*  50 */ "single_ordinal ::= THIRD",
 /*  51 */ "single_ordinal ::= FOURTH",
 /*  52 */ "single_ordinal ::= FIFTH",
 /*  53 */ "single_ordinal ::= SIXTH",
 /*  54 */ "single_ordinal ::= SEVENTH",
 /*  55 */ "single_ordinal ::= EIGHTH",
 /*  56 */ "single_ordinal ::= NINTH",
 /*  57 */ "single_ordinal ::= HALF",
 /*  58 */ "single_ordinal ::= QUARTER",
 /*  59 */ "identifier ::= identifier CHARACTER",
 /*  60 */ "identifier ::= CHARACTER",
 /*  61 */ "any_token ::= single_num",
 /*  62 */ "any_token ::= direct_num",
 /*  63 */ "any_token ::= ten_prefix",
 /*  64 */ "any_token ::= place",
 /*  65 */ "any_token ::= single_ordinal",
 /*  66 */ "separator ::= WHITESPACE",
 /*  67 */ "separator ::= HYPHEN",
 /*  68 */ "separator ::=",
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
  { 48, 1 },
  { 49, 3 },
  { 49, 1 },
  { 49, 1 },
  { 49, 2 },
  { 49, 1 },
  { 50, 3 },
  { 50, 1 },
  { 55, 3 },
  { 52, 1 },
  { 52, 1 },
  { 57, 3 },
  { 57, 3 },
  { 58, 1 },
  { 58, 1 },
  { 58, 1 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 62, 1 },
  { 59, 1 },
  { 59, 1 },
  { 59, 1 },
  { 59, 1 },
  { 59, 1 },
  { 59, 1 },
  { 59, 1 },
  { 59, 1 },
  { 56, 1 },
  { 56, 1 },
  { 56, 1 },
  { 56, 1 },
  { 56, 1 },
  { 61, 1 },
  { 61, 1 },
  { 61, 1 },
  { 61, 1 },
  { 61, 1 },
  { 61, 1 },
  { 61, 1 },
  { 61, 1 },
  { 61, 1 },
  { 61, 1 },
  { 53, 2 },
  { 53, 1 },
  { 54, 1 },
  { 54, 1 },
  { 54, 1 },
  { 54, 1 },
  { 54, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 0 },
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
    if (yymsp[0].minor.yy0.value != NULL) {
        state->result = yymsp[0].minor.yy0.value;
    } else {
        state->result = sdsnewlen("", 1024); // TODO stop specifying buffer
        doubleToString(state->result, yymsp[0].minor.yy0.double_value, state->precision);

        state->result = sdsRemoveFreeSpace(state->result);

        if (yymsp[0].minor.yy0.has_suffix) {
            sds tmp = sdscpy(sdsempty(), state->result);
            /*sdsfree(state->result);*/
            /*state->result = sdscatsds(tmp, yymsp[0].minor.yy0.suffix);*/
            /*sdsfree(yymsp[0].minor.yy0.suffix);*/
        }

        state->result = sdsRemoveFreeSpace(state->result);
    }
}
#line 950 "parser.c"
        break;
      case 1: /* expr ::= combo separator prefix */
#line 47 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; }
#line 955 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 2: /* expr ::= combo */
      case 3: /* expr ::= prefix */ yytestcase(yyruleno==3);
#line 48 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; }
#line 962 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 4: /* expr ::= identifier any_token */
      case 59: /* identifier ::= identifier CHARACTER */ yytestcase(yyruleno==59);
#line 52 "parser.yy"
{
    yymsp[-1].minor.yy0.value = sdscat(yymsp[-1].minor.yy0.value, yymsp[0].minor.yy0.value);
    sdsfree(yymsp[0].minor.yy0.value);
    yylhsminor.yy0.value = sdsempty();
    yylhsminor.yy0.value = sdscat(yylhsminor.yy0.value, yymsp[-1].minor.yy0.value);
    sdsfree(yymsp[-1].minor.yy0.value);
}
#line 975 "parser.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 5: /* expr ::= identifier */
#line 60 "parser.yy"
{
    if (yymsp[0].minor.yy0.value == NULL) {
        printf("yymsp[0].minor.yy0.value is NULL");
    } else {
        yylhsminor.yy0.value = yymsp[0].minor.yy0.value;
        printf("identifer(yylhsminor.yy0): %s\n", yylhsminor.yy0.value);
    }
}
#line 988 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 6: /* combo ::= combo separator group */
      case 11: /* double_digit ::= ten_prefix separator single_num */ yytestcase(yyruleno==11);
      case 12: /* double_digit ::= ten_prefix separator single_ordinal */ yytestcase(yyruleno==12);
#line 69 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value + yymsp[0].minor.yy0.double_value; printf("yylhsminor.yy0 is %lf\n.", yylhsminor.yy0.double_value); }
#line 996 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 7: /* combo ::= group */
      case 9: /* prefix ::= double_digit */ yytestcase(yyruleno==9);
      case 10: /* prefix ::= single_digit */ yytestcase(yyruleno==10);
      case 13: /* single_digit ::= single_num */ yytestcase(yyruleno==13);
      case 14: /* single_digit ::= direct_num */ yytestcase(yyruleno==14);
      case 15: /* single_digit ::= single_ordinal */ yytestcase(yyruleno==15);
#line 71 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[0].minor.yy0.double_value; printf("yylhsminor.yy0 is %lf\n.", yylhsminor.yy0.double_value); }
#line 1007 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 8: /* group ::= prefix separator place */
#line 74 "parser.yy"
{ yylhsminor.yy0.double_value = yymsp[-2].minor.yy0.double_value * yymsp[0].minor.yy0.double_value; printf("yylhsminor.yy0 is %lf\n.", yylhsminor.yy0.double_value); }
#line 1013 "parser.c"
  yymsp[-2].minor.yy0 = yylhsminor.yy0;
        break;
      case 16: /* single_num ::= ONE */
#line 105 "parser.yy"
{ yylhsminor.yy0.double_value = 1.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1019 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 17: /* single_num ::= TWO */
      case 57: /* single_ordinal ::= HALF */ yytestcase(yyruleno==57);
#line 106 "parser.yy"
{ yylhsminor.yy0.double_value = 2.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1026 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 18: /* single_num ::= THREE */
#line 107 "parser.yy"
{ yylhsminor.yy0.double_value = 3.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1032 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 19: /* single_num ::= FOUR */
      case 58: /* single_ordinal ::= QUARTER */ yytestcase(yyruleno==58);
#line 108 "parser.yy"
{ yylhsminor.yy0.double_value = 4.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1039 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 20: /* single_num ::= FIVE */
#line 109 "parser.yy"
{ yylhsminor.yy0.double_value = 5.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1045 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 21: /* single_num ::= SIX */
#line 110 "parser.yy"
{ yylhsminor.yy0.double_value = 6.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1051 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 22: /* single_num ::= SEVEN */
#line 111 "parser.yy"
{ yylhsminor.yy0.double_value = 7.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1057 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 23: /* single_num ::= EIGHT */
#line 112 "parser.yy"
{ yylhsminor.yy0.double_value = 8.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1063 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 24: /* single_num ::= NINE */
#line 113 "parser.yy"
{ yylhsminor.yy0.double_value = 9.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1069 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 25: /* direct_num ::= ZERO */
#line 115 "parser.yy"
{ yylhsminor.yy0.double_value = 0.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1075 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 26: /* direct_num ::= TEN */
#line 116 "parser.yy"
{ yylhsminor.yy0.double_value = 10.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1081 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 27: /* direct_num ::= ELEVEN */
#line 117 "parser.yy"
{ yylhsminor.yy0.double_value = 11.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1087 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 28: /* direct_num ::= TWELVE */
#line 118 "parser.yy"
{ yylhsminor.yy0.double_value = 12.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1093 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 29: /* direct_num ::= THIRTEEN */
#line 119 "parser.yy"
{ yylhsminor.yy0.double_value = 13.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1099 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 30: /* direct_num ::= FOURTEEN */
#line 120 "parser.yy"
{ yylhsminor.yy0.double_value = 14.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1105 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 31: /* direct_num ::= FIFTEEN */
#line 121 "parser.yy"
{ yylhsminor.yy0.double_value = 15.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1111 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 32: /* direct_num ::= SIXTEEN */
#line 122 "parser.yy"
{ yylhsminor.yy0.double_value = 16.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1117 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 33: /* direct_num ::= SEVENTEEN */
#line 123 "parser.yy"
{ yylhsminor.yy0.double_value = 17.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1123 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 34: /* direct_num ::= EIGHTEEN */
#line 124 "parser.yy"
{ yylhsminor.yy0.double_value = 18.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1129 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 35: /* direct_num ::= NINETEEN */
#line 125 "parser.yy"
{ yylhsminor.yy0.double_value = 19.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1135 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 36: /* ten_prefix ::= TWENTY */
#line 127 "parser.yy"
{ yylhsminor.yy0.double_value = 20.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1141 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 37: /* ten_prefix ::= THIRTY */
#line 128 "parser.yy"
{ yylhsminor.yy0.double_value = 30.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1147 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 38: /* ten_prefix ::= FORTY */
#line 129 "parser.yy"
{ yylhsminor.yy0.double_value = 40.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1153 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 39: /* ten_prefix ::= FIFTY */
#line 130 "parser.yy"
{ yylhsminor.yy0.double_value = 50.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1159 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 40: /* ten_prefix ::= SIXTY */
#line 131 "parser.yy"
{ yylhsminor.yy0.double_value = 60.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1165 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 41: /* ten_prefix ::= SEVENTY */
#line 132 "parser.yy"
{ yylhsminor.yy0.double_value = 70.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1171 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 42: /* ten_prefix ::= EIGHTY */
#line 133 "parser.yy"
{ yylhsminor.yy0.double_value = 80.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1177 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 43: /* ten_prefix ::= NINETY */
#line 134 "parser.yy"
{ yylhsminor.yy0.double_value = 90.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1183 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 44: /* place ::= HUNDRED */
#line 136 "parser.yy"
{ yylhsminor.yy0.double_value = 100.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1189 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 45: /* place ::= THOUSAND */
#line 137 "parser.yy"
{ yylhsminor.yy0.double_value = 1000.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1195 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 46: /* place ::= MILLION */
#line 138 "parser.yy"
{ yylhsminor.yy0.double_value = 1000000.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1201 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 47: /* place ::= BILLION */
#line 139 "parser.yy"
{ yylhsminor.yy0.double_value = 1000000000.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1207 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 48: /* place ::= TRILLION */
#line 140 "parser.yy"
{ yylhsminor.yy0.double_value = 1000000000000.0; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1213 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 49: /* single_ordinal ::= FIRST */
#line 142 "parser.yy"
{ yylhsminor.yy0.double_value = 1.0; yylhsminor.yy0.suffix = sdsnew("st"); yylhsminor.yy0.has_suffix = true; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1219 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 50: /* single_ordinal ::= THIRD */
#line 143 "parser.yy"
{ yylhsminor.yy0.double_value = 3.0; yylhsminor.yy0.suffix = sdsnew("nd"); yylhsminor.yy0.has_suffix = true; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1225 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 51: /* single_ordinal ::= FOURTH */
#line 144 "parser.yy"
{ yylhsminor.yy0.double_value = 4.0; yylhsminor.yy0.suffix = sdsnew("rd"); yylhsminor.yy0.has_suffix = true; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1231 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 52: /* single_ordinal ::= FIFTH */
#line 145 "parser.yy"
{ yylhsminor.yy0.double_value = 5.0; yylhsminor.yy0.suffix = sdsnew("th"); yylhsminor.yy0.has_suffix = true; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1237 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 53: /* single_ordinal ::= SIXTH */
#line 146 "parser.yy"
{ yylhsminor.yy0.double_value = 6.0; yylhsminor.yy0.suffix = sdsnew("th"); yylhsminor.yy0.has_suffix = true; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1243 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 54: /* single_ordinal ::= SEVENTH */
#line 147 "parser.yy"
{ yylhsminor.yy0.double_value = 7.0; yylhsminor.yy0.suffix = sdsnew("th"); yylhsminor.yy0.has_suffix = true; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1249 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 55: /* single_ordinal ::= EIGHTH */
#line 148 "parser.yy"
{ yylhsminor.yy0.double_value = 8.0; yylhsminor.yy0.suffix = sdsnew("th"); yylhsminor.yy0.has_suffix = true; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1255 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 56: /* single_ordinal ::= NINTH */
#line 149 "parser.yy"
{ yylhsminor.yy0.double_value = 9.0; yylhsminor.yy0.suffix = sdsnew("th"); yylhsminor.yy0.has_suffix = true; yylhsminor.yy0.value = yymsp[0].minor.yy0.value; }
#line 1261 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 60: /* identifier ::= CHARACTER */
#line 162 "parser.yy"
{
    yylhsminor.yy0.value = yymsp[0].minor.yy0.value;
}
#line 1269 "parser.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      default:
      /* (61) any_token ::= single_num (OPTIMIZED OUT) */ assert(yyruleno!=61);
      /* (62) any_token ::= direct_num (OPTIMIZED OUT) */ assert(yyruleno!=62);
      /* (63) any_token ::= ten_prefix (OPTIMIZED OUT) */ assert(yyruleno!=63);
      /* (64) any_token ::= place (OPTIMIZED OUT) */ assert(yyruleno!=64);
      /* (65) any_token ::= single_ordinal (OPTIMIZED OUT) */ assert(yyruleno!=65);
      /* (66) separator ::= WHITESPACE */ yytestcase(yyruleno==66);
      /* (67) separator ::= HYPHEN */ yytestcase(yyruleno==67);
      /* (68) separator ::= */ yytestcase(yyruleno==68);
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
#line 1324 "parser.c"
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
#line 1344 "parser.c"
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
