/* Generated by re2c 0.16 on Mon Nov 14 00:18:13 2016 */
#line 1 "scanner.re"
#include "scanner.def.h"
#include "parser.h"
#include "scan.h"
#include "readmem.h"

#define TOKEN_SEPARATOR 10000

int numerizer_start(scanstate *ss) {
    scanner_enter(ss);
//std:
    
#line 15 "scanner.c"
{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	if ((YYLIMIT - YYCURSOR) < 14) YYFILL(14);
	yych = *YYCURSOR;
	switch (yych) {
	case 0x00:	goto yy2;
	case '\t':
	case '\n':
	case '\f':
	case '\r':
	case ' ':
	case '-':	goto yy6;
	case '.':	goto yy9;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy10;
	case 'A':
	case 'a':	goto yy12;
	case 'B':
	case 'b':	goto yy13;
	case 'E':
	case 'e':	goto yy14;
	case 'F':
	case 'f':	goto yy15;
	case 'H':
	case 'h':	goto yy16;
	case 'M':
	case 'm':	goto yy17;
	case 'N':
	case 'n':	goto yy18;
	case 'O':
	case 'o':	goto yy19;
	case 'Q':
	case 'q':	goto yy20;
	case 'S':
	case 's':	goto yy21;
	case 'T':
	case 't':	goto yy22;
	case 'Z':
	case 'z':	goto yy23;
	default:	goto yy4;
	}
yy2:
	++YYCURSOR;
#line 155 "scanner.re"
	{ return 0; }
#line 70 "scanner.c"
yy4:
	++YYCURSOR;
yy5:
#line 157 "scanner.re"
	{ return TOKEN_CHARACTERS; }
#line 76 "scanner.c"
yy6:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case '\t':
	case '\n':
	case '\f':
	case '\r':
	case ' ':
	case '-':	goto yy6;
	default:	goto yy8;
	}
yy8:
#line 153 "scanner.re"
	{ return TOKEN_SEPARATOR; }
#line 93 "scanner.c"
yy9:
	yych = *++YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy24;
	default:	goto yy5;
	}
yy10:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '.':	goto yy26;
	case '/':	goto yy28;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy29;
	default:	goto yy11;
	}
yy11:
#line 24 "scanner.re"
	{ return TOKEN_NUMBER; }
#line 130 "scanner.c"
yy12:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case ' ':	goto yy30;
	case 'N':
	case 'n':	goto yy31;
	default:	goto yy5;
	}
yy13:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'I':
	case 'i':	goto yy32;
	default:	goto yy5;
	}
yy14:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'I':
	case 'i':	goto yy33;
	case 'L':
	case 'l':	goto yy34;
	default:	goto yy5;
	}
yy15:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'I':
	case 'i':	goto yy35;
	case 'O':
	case 'o':	goto yy36;
	default:	goto yy5;
	}
yy16:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'A':
	case 'a':	goto yy37;
	case 'U':
	case 'u':	goto yy38;
	default:	goto yy5;
	}
yy17:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'I':
	case 'i':	goto yy39;
	default:	goto yy5;
	}
yy18:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'I':
	case 'i':	goto yy40;
	default:	goto yy5;
	}
yy19:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'N':
	case 'n':	goto yy41;
	default:	goto yy5;
	}
yy20:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'U':
	case 'u':	goto yy42;
	default:	goto yy5;
	}
yy21:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'E':
	case 'e':	goto yy43;
	case 'I':
	case 'i':	goto yy44;
	default:	goto yy5;
	}
yy22:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'E':
	case 'e':	goto yy45;
	case 'H':
	case 'h':	goto yy46;
	case 'R':
	case 'r':	goto yy47;
	case 'W':
	case 'w':	goto yy48;
	default:	goto yy5;
	}
yy23:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'E':
	case 'e':	goto yy49;
	default:	goto yy5;
	}
yy24:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy24;
	default:	goto yy11;
	}
yy26:
	yych = *++YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy24;
	default:	goto yy27;
	}
yy27:
	YYCURSOR = YYMARKER;
	switch (yyaccept) {
	case 0: 	goto yy11;
	case 1: 	goto yy5;
	case 2: 	goto yy60;
	case 3: 	goto yy79;
	case 4: 	goto yy81;
	case 5: 	goto yy107;
	case 6: 	goto yy113;
	case 7: 	goto yy52;
	case 8: 	goto yy140;
	case 9: 	goto yy162;
	case 10: 	goto yy196;
	case 11: 	goto yy240;
	case 12: 	goto yy245;
	case 13: 	goto yy250;
	case 14: 	goto yy252;
	case 15: 	goto yy266;
	case 16: 	goto yy284;
	case 17: 	goto yy292;
	case 18: 	goto yy297;
	case 19: 	goto yy305;
	case 20: 	goto yy308;
	case 21: 	goto yy310;
	default:	goto yy339;
	}
yy28:
	yych = *++YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy50;
	default:	goto yy27;
	}
yy29:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '.':	goto yy26;
	case '/':	goto yy53;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy54;
	default:	goto yy11;
	}
yy30:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'B':
	case 'b':	goto yy55;
	case 'H':
	case 'h':	goto yy56;
	case 'M':
	case 'm':	goto yy57;
	case 'T':
	case 't':	goto yy58;
	default:	goto yy27;
	}
yy31:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy59;
	default:	goto yy27;
	}
yy32:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy61;
	default:	goto yy27;
	}
yy33:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'G':
	case 'g':	goto yy62;
	default:	goto yy27;
	}
yy34:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy63;
	default:	goto yy27;
	}
yy35:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'F':
	case 'f':	goto yy64;
	case 'R':
	case 'r':	goto yy65;
	case 'V':
	case 'v':	goto yy66;
	default:	goto yy27;
	}
yy36:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy67;
	case 'U':
	case 'u':	goto yy68;
	default:	goto yy27;
	}
yy37:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy69;
	default:	goto yy27;
	}
yy38:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy70;
	default:	goto yy27;
	}
yy39:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy71;
	default:	goto yy27;
	}
yy40:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy72;
	default:	goto yy27;
	}
yy41:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy73;
	default:	goto yy27;
	}
yy42:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy75;
	default:	goto yy27;
	}
yy43:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy76;
	case 'V':
	case 'v':	goto yy77;
	default:	goto yy27;
	}
yy44:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'X':
	case 'x':	goto yy78;
	default:	goto yy27;
	}
yy45:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy80;
	default:	goto yy27;
	}
yy46:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy82;
	case 'O':
	case 'o':	goto yy83;
	case 'R':
	case 'r':	goto yy84;
	default:	goto yy27;
	}
yy47:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy85;
	default:	goto yy27;
	}
yy48:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy86;
	case 'O':
	case 'o':	goto yy87;
	default:	goto yy27;
	}
yy49:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy89;
	default:	goto yy27;
	}
yy50:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy51:
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy50;
	default:	goto yy52;
	}
yy52:
#line 23 "scanner.re"
	{ return TOKEN_CHARACTERS; }
#line 515 "scanner.c"
yy53:
	yych = *++YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy90;
	default:	goto yy27;
	}
yy54:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '.':	goto yy26;
	case '/':	goto yy53;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy91;
	default:	goto yy11;
	}
yy55:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy92;
	default:	goto yy27;
	}
yy56:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'U':
	case 'u':	goto yy93;
	default:	goto yy27;
	}
yy57:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy94;
	default:	goto yy27;
	}
yy58:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy95;
	case 'R':
	case 'r':	goto yy96;
	default:	goto yy27;
	}
yy59:
	yyaccept = 2;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case ' ':	goto yy97;
	default:	goto yy60;
	}
yy60:
#line 26 "scanner.re"
	{ return TOKEN_AND; }
#line 589 "scanner.c"
yy61:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy98;
	default:	goto yy27;
	}
yy62:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy99;
	default:	goto yy27;
	}
yy63:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'V':
	case 'v':	goto yy100;
	default:	goto yy27;
	}
yy64:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy101;
	default:	goto yy27;
	}
yy65:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy102;
	default:	goto yy27;
	}
yy66:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy103;
	default:	goto yy27;
	}
yy67:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy105;
	default:	goto yy27;
	}
yy68:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy106;
	default:	goto yy27;
	}
yy69:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'F':
	case 'f':	goto yy108;
	default:	goto yy27;
	}
yy70:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy110;
	default:	goto yy27;
	}
yy71:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy111;
	default:	goto yy27;
	}
yy72:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy112;
	case 'T':
	case 't':	goto yy114;
	default:	goto yy27;
	}
yy73:
	++YYCURSOR;
#line 30 "scanner.re"
	{ return TOKEN_ONE; }
#line 680 "scanner.c"
yy75:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy115;
	default:	goto yy27;
	}
yy76:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy116;
	default:	goto yy27;
	}
yy77:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy117;
	default:	goto yy27;
	}
yy78:
	yyaccept = 3;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy118;
	default:	goto yy79;
	}
yy79:
#line 35 "scanner.re"
	{ return TOKEN_SIX; }
#line 713 "scanner.c"
yy80:
	yyaccept = 4;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy119;
	default:	goto yy81;
	}
yy81:
#line 39 "scanner.re"
	{ return TOKEN_TEN; }
#line 725 "scanner.c"
yy82:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy120;
	default:	goto yy27;
	}
yy83:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'U':
	case 'u':	goto yy121;
	default:	goto yy27;
	}
yy84:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy122;
	default:	goto yy27;
	}
yy85:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy123;
	default:	goto yy27;
	}
yy86:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy124;
	case 'N':
	case 'n':	goto yy125;
	default:	goto yy27;
	}
yy87:
	++YYCURSOR;
#line 31 "scanner.re"
	{ return TOKEN_TWO; }
#line 767 "scanner.c"
yy89:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy126;
	default:	goto yy27;
	}
yy90:
	yych = *++YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy128;
	default:	goto yy52;
	}
yy91:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '/':	goto yy53;
	default:	goto yy130;
	}
yy92:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy131;
	default:	goto yy27;
	}
yy93:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy132;
	default:	goto yy27;
	}
yy94:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy133;
	default:	goto yy27;
	}
yy95:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy134;
	default:	goto yy27;
	}
yy96:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy135;
	default:	goto yy27;
	}
yy97:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy136;
	default:	goto yy27;
	}
yy98:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy138;
	default:	goto yy27;
	}
yy99:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy139;
	default:	goto yy27;
	}
yy100:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy141;
	default:	goto yy27;
	}
yy101:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy142;
	case 'H':
	case 'h':	goto yy143;
	case 'I':
	case 'i':	goto yy145;
	case 'Y':
	case 'y':	goto yy146;
	default:	goto yy27;
	}
yy102:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy148;
	default:	goto yy27;
	}
yy103:
	++YYCURSOR;
#line 34 "scanner.re"
	{ return TOKEN_FIVE; }
#line 884 "scanner.c"
yy105:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'Y':
	case 'y':	goto yy150;
	default:	goto yy27;
	}
yy106:
	yyaccept = 5;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy152;
	default:	goto yy107;
	}
yy107:
#line 33 "scanner.re"
	{ return TOKEN_FOUR; }
#line 903 "scanner.c"
yy108:
	++YYCURSOR;
#line 110 "scanner.re"
	{ return TOKEN_HALF; }
#line 908 "scanner.c"
yy110:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy153;
	default:	goto yy27;
	}
yy111:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy154;
	default:	goto yy27;
	}
yy112:
	yyaccept = 6;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy155;
	default:	goto yy113;
	}
yy113:
#line 38 "scanner.re"
	{ return TOKEN_NINE; }
#line 934 "scanner.c"
yy114:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy156;
	case 'H':
	case 'h':	goto yy157;
	default:	goto yy27;
	}
yy115:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy159;
	default:	goto yy27;
	}
yy116:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy160;
	default:	goto yy27;
	}
yy117:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy161;
	default:	goto yy27;
	}
yy118:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy163;
	case 'H':
	case 'h':	goto yy164;
	case 'I':
	case 'i':	goto yy166;
	case 'Y':
	case 'y':	goto yy167;
	default:	goto yy27;
	}
yy119:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy169;
	default:	goto yy27;
	}
yy120:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy171;
	case 'T':
	case 't':	goto yy173;
	default:	goto yy27;
	}
yy121:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy174;
	default:	goto yy27;
	}
yy122:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy175;
	default:	goto yy27;
	}
yy123:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy177;
	default:	goto yy27;
	}
yy124:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'F':
	case 'f':	goto yy178;
	case 'V':
	case 'v':	goto yy179;
	default:	goto yy27;
	}
yy125:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy180;
	default:	goto yy27;
	}
yy126:
	++YYCURSOR;
#line 29 "scanner.re"
	{ return TOKEN_ZERO; }
#line 1035 "scanner.c"
yy128:
	yyaccept = 7;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '/':	goto yy181;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy182;
	default:	goto yy52;
	}
yy129:
	yyaccept = 0;
	YYMARKER = ++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
yy130:
	switch (yych) {
	case '.':	goto yy26;
	case '/':	goto yy28;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy129;
	default:	goto yy11;
	}
yy131:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy183;
	default:	goto yy27;
	}
yy132:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy184;
	default:	goto yy27;
	}
yy133:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy185;
	default:	goto yy27;
	}
yy134:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'U':
	case 'u':	goto yy186;
	default:	goto yy27;
	}
yy135:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy187;
	default:	goto yy27;
	}
yy136:
	++YYCURSOR;
#line 27 "scanner.re"
	{ return TOKEN_AND_A; }
#line 1113 "scanner.c"
yy138:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy188;
	default:	goto yy27;
	}
yy139:
	yyaccept = 8;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'E':
	case 'e':	goto yy189;
	case 'H':
	case 'h':	goto yy190;
	case 'I':
	case 'i':	goto yy192;
	case 'Y':
	case 'y':	goto yy193;
	default:	goto yy140;
	}
yy140:
#line 37 "scanner.re"
	{ return TOKEN_EIGHT; }
#line 1138 "scanner.c"
yy141:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy195;
	default:	goto yy27;
	}
yy142:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy197;
	default:	goto yy27;
	}
yy143:
	++YYCURSOR;
#line 76 "scanner.re"
	{ return TOKEN_FIFTH; }
#line 1157 "scanner.c"
yy145:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy198;
	default:	goto yy27;
	}
yy146:
	++YYCURSOR;
#line 55 "scanner.re"
	{ return TOKEN_FIFTY; }
#line 1169 "scanner.c"
yy148:
	++YYCURSOR;
#line 72 "scanner.re"
	{ return TOKEN_FIRST; }
#line 1174 "scanner.c"
yy150:
	++YYCURSOR;
#line 53 "scanner.re"
	{ return TOKEN_FORTY; }
#line 1179 "scanner.c"
yy152:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy199;
	case 'H':
	case 'h':	goto yy200;
	case 'I':
	case 'i':	goto yy202;
	case 'Y':
	case 'y':	goto yy203;
	default:	goto yy27;
	}
yy153:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy205;
	default:	goto yy27;
	}
yy154:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy206;
	default:	goto yy27;
	}
yy155:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy207;
	case 'H':
	case 'h':	goto yy208;
	case 'I':
	case 'i':	goto yy210;
	case 'Y':
	case 'y':	goto yy211;
	default:	goto yy27;
	}
yy156:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy213;
	default:	goto yy27;
	}
yy157:
	++YYCURSOR;
#line 81 "scanner.re"
	{ return TOKEN_NINTH; }
#line 1231 "scanner.c"
yy159:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy214;
	default:	goto yy27;
	}
yy160:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy215;
	default:	goto yy27;
	}
yy161:
	yyaccept = 9;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy217;
	default:	goto yy162;
	}
yy162:
#line 36 "scanner.re"
	{ return TOKEN_SEVEN; }
#line 1257 "scanner.c"
yy163:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy218;
	default:	goto yy27;
	}
yy164:
	++YYCURSOR;
#line 77 "scanner.re"
	{ return TOKEN_SIXTH; }
#line 1269 "scanner.c"
yy166:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy219;
	default:	goto yy27;
	}
yy167:
	++YYCURSOR;
#line 56 "scanner.re"
	{ return TOKEN_SIXTY; }
#line 1281 "scanner.c"
yy169:
	++YYCURSOR;
#line 83 "scanner.re"
	{ return TOKEN_TENTH; }
#line 1286 "scanner.c"
yy171:
	++YYCURSOR;
#line 74 "scanner.re"
	{ return TOKEN_THIRD; }
#line 1291 "scanner.c"
yy173:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy220;
	case 'I':
	case 'i':	goto yy221;
	case 'Y':
	case 'y':	goto yy222;
	default:	goto yy27;
	}
yy174:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy224;
	default:	goto yy27;
	}
yy175:
	++YYCURSOR;
#line 32 "scanner.re"
	{ return TOKEN_THREE; }
#line 1314 "scanner.c"
yy177:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy225;
	default:	goto yy27;
	}
yy178:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy226;
	default:	goto yy27;
	}
yy179:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy227;
	default:	goto yy27;
	}
yy180:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy229;
	case 'Y':
	case 'y':	goto yy230;
	default:	goto yy27;
	}
yy181:
	yych = *++YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy232;
	default:	goto yy27;
	}
yy182:
	yyaccept = 7;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '/':	goto yy181;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy233;
	default:	goto yy52;
	}
yy183:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy234;
	default:	goto yy27;
	}
yy184:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy235;
	default:	goto yy27;
	}
yy185:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy236;
	default:	goto yy27;
	}
yy186:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy237;
	default:	goto yy27;
	}
yy187:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy238;
	default:	goto yy27;
	}
yy188:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy239;
	default:	goto yy27;
	}
yy189:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy241;
	default:	goto yy27;
	}
yy190:
	++YYCURSOR;
#line 79 "scanner.re"
	{ return TOKEN_EIGHTH; }
#line 1430 "scanner.c"
yy192:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy242;
	default:	goto yy27;
	}
yy193:
	++YYCURSOR;
#line 58 "scanner.re"
	{ return TOKEN_EIGHTY; }
#line 1442 "scanner.c"
yy195:
	yyaccept = 10;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy243;
	default:	goto yy196;
	}
yy196:
#line 40 "scanner.re"
	{ return TOKEN_ELEVEN; }
#line 1454 "scanner.c"
yy197:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy244;
	default:	goto yy27;
	}
yy198:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy246;
	default:	goto yy27;
	}
yy199:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy247;
	default:	goto yy27;
	}
yy200:
	++YYCURSOR;
#line 75 "scanner.re"
	{ return TOKEN_FOURTH; }
#line 1480 "scanner.c"
yy202:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy248;
	default:	goto yy27;
	}
yy203:
	++YYCURSOR;
#line 54 "scanner.re"
	{ return TOKEN_FORTY; }
#line 1492 "scanner.c"
yy205:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy249;
	default:	goto yy27;
	}
yy206:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy251;
	default:	goto yy27;
	}
yy207:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy253;
	default:	goto yy27;
	}
yy208:
	++YYCURSOR;
#line 80 "scanner.re"
	{ return TOKEN_NINTH; }
#line 1518 "scanner.c"
yy210:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy254;
	default:	goto yy27;
	}
yy211:
	++YYCURSOR;
#line 59 "scanner.re"
	{ return TOKEN_NINETY; }
#line 1530 "scanner.c"
yy213:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy255;
	default:	goto yy27;
	}
yy214:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy257;
	default:	goto yy27;
	}
yy215:
	++YYCURSOR;
#line 73 "scanner.re"
	{ return TOKEN_SECOND; }
#line 1549 "scanner.c"
yy217:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy259;
	case 'H':
	case 'h':	goto yy260;
	case 'I':
	case 'i':	goto yy262;
	case 'Y':
	case 'y':	goto yy263;
	default:	goto yy27;
	}
yy218:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy265;
	default:	goto yy27;
	}
yy219:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy267;
	default:	goto yy27;
	}
yy220:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy268;
	default:	goto yy27;
	}
yy221:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy269;
	default:	goto yy27;
	}
yy222:
	++YYCURSOR;
#line 52 "scanner.re"
	{ return TOKEN_THIRTY; }
#line 1595 "scanner.c"
yy224:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy270;
	default:	goto yy27;
	}
yy225:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy271;
	default:	goto yy27;
	}
yy226:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy272;
	default:	goto yy27;
	}
yy227:
	++YYCURSOR;
#line 41 "scanner.re"
	{ return TOKEN_TWELVE; }
#line 1621 "scanner.c"
yy229:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy274;
	default:	goto yy27;
	}
yy230:
	++YYCURSOR;
#line 51 "scanner.re"
	{ return TOKEN_TWENTY; }
#line 1633 "scanner.c"
yy232:
	yych = *++YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy275;
	default:	goto yy27;
	}
yy233:
	yyaccept = 7;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '/':	goto yy181;
	default:	goto yy51;
	}
yy234:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy277;
	default:	goto yy27;
	}
yy235:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy278;
	default:	goto yy27;
	}
yy236:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy279;
	default:	goto yy27;
	}
yy237:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy280;
	default:	goto yy27;
	}
yy238:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy281;
	default:	goto yy27;
	}
yy239:
	yyaccept = 11;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy282;
	default:	goto yy240;
	}
yy240:
#line 68 "scanner.re"
	{ return TOKEN_BILLION; }
#line 1702 "scanner.c"
yy241:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy283;
	default:	goto yy27;
	}
yy242:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy285;
	default:	goto yy27;
	}
yy243:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy286;
	default:	goto yy27;
	}
yy244:
	yyaccept = 12;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy288;
	default:	goto yy245;
	}
yy245:
#line 44 "scanner.re"
	{ return TOKEN_FIFTEEN; }
#line 1735 "scanner.c"
yy246:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy289;
	default:	goto yy27;
	}
yy247:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy291;
	default:	goto yy27;
	}
yy248:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy293;
	default:	goto yy27;
	}
yy249:
	yyaccept = 13;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy294;
	default:	goto yy250;
	}
yy250:
#line 62 "scanner.re"
	{ return TOKEN_HUNDRED; }
#line 1768 "scanner.c"
yy251:
	yyaccept = 14;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy295;
	default:	goto yy252;
	}
yy252:
#line 66 "scanner.re"
	{ return TOKEN_MILLION; }
#line 1780 "scanner.c"
yy253:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy296;
	default:	goto yy27;
	}
yy254:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy298;
	default:	goto yy27;
	}
yy255:
	++YYCURSOR;
#line 49 "scanner.re"
	{ return TOKEN_NINETEEN; }
#line 1799 "scanner.c"
yy257:
	++YYCURSOR;
#line 109 "scanner.re"
	{ return TOKEN_QUARTER; }
#line 1804 "scanner.c"
yy259:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy299;
	default:	goto yy27;
	}
yy260:
	++YYCURSOR;
#line 78 "scanner.re"
	{ return TOKEN_SEVENTH; }
#line 1816 "scanner.c"
yy262:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy300;
	default:	goto yy27;
	}
yy263:
	++YYCURSOR;
#line 57 "scanner.re"
	{ return TOKEN_SEVENTY; }
#line 1828 "scanner.c"
yy265:
	yyaccept = 15;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy301;
	default:	goto yy266;
	}
yy266:
#line 45 "scanner.re"
	{ return TOKEN_SIXTEEN; }
#line 1840 "scanner.c"
yy267:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy302;
	default:	goto yy27;
	}
yy268:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy304;
	default:	goto yy27;
	}
yy269:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy306;
	default:	goto yy27;
	}
yy270:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy307;
	default:	goto yy27;
	}
yy271:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy309;
	default:	goto yy27;
	}
yy272:
	++YYCURSOR;
#line 85 "scanner.re"
	{ return TOKEN_TWELFTH; }
#line 1880 "scanner.c"
yy274:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy311;
	default:	goto yy27;
	}
yy275:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy312;
	default:	goto yy276;
	}
yy276:
#line 22 "scanner.re"
	{ return TOKEN_CHARACTERS; }
#line 1906 "scanner.c"
yy277:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy313;
	default:	goto yy27;
	}
yy278:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy315;
	default:	goto yy27;
	}
yy279:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy317;
	default:	goto yy27;
	}
yy280:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy319;
	default:	goto yy27;
	}
yy281:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy320;
	default:	goto yy27;
	}
yy282:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy321;
	default:	goto yy27;
	}
yy283:
	yyaccept = 16;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy323;
	default:	goto yy284;
	}
yy284:
#line 47 "scanner.re"
	{ return TOKEN_EIGHTEEN; }
#line 1960 "scanner.c"
yy285:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy324;
	default:	goto yy27;
	}
yy286:
	++YYCURSOR;
#line 84 "scanner.re"
	{ return TOKEN_ELEVENTH; }
#line 1972 "scanner.c"
yy288:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy326;
	default:	goto yy27;
	}
yy289:
	++YYCURSOR;
#line 97 "scanner.re"
	{ return TOKEN_FIFTIETH; }
#line 1984 "scanner.c"
yy291:
	yyaccept = 17;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy328;
	default:	goto yy292;
	}
yy292:
#line 43 "scanner.re"
	{ return TOKEN_FOURTEEN; }
#line 1996 "scanner.c"
yy293:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy329;
	default:	goto yy27;
	}
yy294:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy331;
	default:	goto yy27;
	}
yy295:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy333;
	default:	goto yy27;
	}
yy296:
	yyaccept = 18;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy335;
	default:	goto yy297;
	}
yy297:
#line 48 "scanner.re"
	{ return TOKEN_NINETEEN; }
#line 2029 "scanner.c"
yy298:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy336;
	default:	goto yy27;
	}
yy299:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy338;
	default:	goto yy27;
	}
yy300:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy340;
	default:	goto yy27;
	}
yy301:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy341;
	default:	goto yy27;
	}
yy302:
	++YYCURSOR;
#line 98 "scanner.re"
	{ return TOKEN_SIXTIETH; }
#line 2062 "scanner.c"
yy304:
	yyaccept = 19;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy343;
	default:	goto yy305;
	}
yy305:
#line 42 "scanner.re"
	{ return TOKEN_THIRTEEN; }
#line 2074 "scanner.c"
yy306:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy344;
	default:	goto yy27;
	}
yy307:
	yyaccept = 20;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy346;
	default:	goto yy308;
	}
yy308:
#line 64 "scanner.re"
	{ return TOKEN_THOUSAND; }
#line 2093 "scanner.c"
yy309:
	yyaccept = 21;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy347;
	default:	goto yy310;
	}
yy310:
#line 70 "scanner.re"
	{ return TOKEN_TRILLION; }
#line 2105 "scanner.c"
yy311:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy348;
	default:	goto yy27;
	}
yy312:
	yych = *++YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy350;
	default:	goto yy276;
	}
yy313:
	++YYCURSOR;
#line 67 "scanner.re"
	{ return TOKEN_BILLION; }
#line 2132 "scanner.c"
yy315:
	++YYCURSOR;
#line 61 "scanner.re"
	{ return TOKEN_HUNDRED; }
#line 2137 "scanner.c"
yy317:
	++YYCURSOR;
#line 65 "scanner.re"
	{ return TOKEN_MILLION; }
#line 2142 "scanner.c"
yy319:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy351;
	default:	goto yy27;
	}
yy320:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy353;
	default:	goto yy27;
	}
yy321:
	++YYCURSOR;
#line 106 "scanner.re"
	{ return TOKEN_BILLIONTH; }
#line 2161 "scanner.c"
yy323:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy355;
	default:	goto yy27;
	}
yy324:
	++YYCURSOR;
#line 100 "scanner.re"
	{ return TOKEN_EIGHTIETH; }
#line 2173 "scanner.c"
yy326:
	++YYCURSOR;
#line 88 "scanner.re"
	{ return TOKEN_FIFTEENTH; }
#line 2178 "scanner.c"
yy328:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy357;
	default:	goto yy27;
	}
yy329:
	++YYCURSOR;
#line 96 "scanner.re"
	{ return TOKEN_FOURTIETH; }
#line 2190 "scanner.c"
yy331:
	++YYCURSOR;
#line 103 "scanner.re"
	{ return TOKEN_HUNDREDTH; }
#line 2195 "scanner.c"
yy333:
	++YYCURSOR;
#line 105 "scanner.re"
	{ return TOKEN_MILLIONTH; }
#line 2200 "scanner.c"
yy335:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy359;
	default:	goto yy27;
	}
yy336:
	++YYCURSOR;
#line 101 "scanner.re"
	{ return TOKEN_NINETIETH; }
#line 2212 "scanner.c"
yy338:
	yyaccept = 22;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy361;
	default:	goto yy339;
	}
yy339:
#line 46 "scanner.re"
	{ return TOKEN_SEVENTEEN; }
#line 2224 "scanner.c"
yy340:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy362;
	default:	goto yy27;
	}
yy341:
	++YYCURSOR;
#line 89 "scanner.re"
	{ return TOKEN_SIXTEENTH; }
#line 2236 "scanner.c"
yy343:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy364;
	default:	goto yy27;
	}
yy344:
	++YYCURSOR;
#line 95 "scanner.re"
	{ return TOKEN_THIRTIETH; }
#line 2248 "scanner.c"
yy346:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy366;
	default:	goto yy27;
	}
yy347:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy368;
	default:	goto yy27;
	}
yy348:
	++YYCURSOR;
#line 94 "scanner.re"
	{ return TOKEN_TWENTIETH; }
#line 2267 "scanner.c"
yy350:
	yych = *++YYCURSOR;
	goto yy276;
yy351:
	++YYCURSOR;
#line 63 "scanner.re"
	{ return TOKEN_THOUSAND; }
#line 2275 "scanner.c"
yy353:
	++YYCURSOR;
#line 69 "scanner.re"
	{ return TOKEN_TRILLION; }
#line 2280 "scanner.c"
yy355:
	++YYCURSOR;
#line 91 "scanner.re"
	{ return TOKEN_EIGHTEENTH; }
#line 2285 "scanner.c"
yy357:
	++YYCURSOR;
#line 87 "scanner.re"
	{ return TOKEN_FOURTEENTH; }
#line 2290 "scanner.c"
yy359:
	++YYCURSOR;
#line 92 "scanner.re"
	{ return TOKEN_NINETEENTH; }
#line 2295 "scanner.c"
yy361:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy370;
	default:	goto yy27;
	}
yy362:
	++YYCURSOR;
#line 99 "scanner.re"
	{ return TOKEN_SEVENTIETH; }
#line 2307 "scanner.c"
yy364:
	++YYCURSOR;
#line 86 "scanner.re"
	{ return TOKEN_THIRTEENTH; }
#line 2312 "scanner.c"
yy366:
	++YYCURSOR;
#line 104 "scanner.re"
	{ return TOKEN_THOUSANDTH; }
#line 2317 "scanner.c"
yy368:
	++YYCURSOR;
#line 107 "scanner.re"
	{ return TOKEN_TRILLIONTH; }
#line 2322 "scanner.c"
yy370:
	++YYCURSOR;
#line 90 "scanner.re"
	{ return TOKEN_SEVENTEENTH; }
#line 2327 "scanner.c"
}
#line 158 "scanner.re"

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
