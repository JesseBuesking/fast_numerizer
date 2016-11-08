/* Generated by re2c 0.16 on Tue Nov  8 01:59:11 2016 */
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
	if ((YYLIMIT - YYCURSOR) < 12) YYFILL(12);
	yych = *YYCURSOR;
	switch (yych) {
	case 0x00:	goto yy2;
	case '\t':
	case '\n':
	case '\f':
	case '\r':
	case ' ':
	case '-':	goto yy6;
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy9;
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
#line 140 "scanner.re"
	{ return 0; }
#line 70 "scanner.c"
yy4:
	++YYCURSOR;
yy5:
#line 142 "scanner.re"
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
#line 138 "scanner.re"
	{ return TOKEN_SEPARATOR; }
#line 93 "scanner.c"
yy9:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy9;
	default:	goto yy11;
	}
yy11:
#line 18 "scanner.re"
	{ return TOKEN_NUMBER; }
#line 115 "scanner.c"
yy12:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'N':
	case 'n':	goto yy24;
	default:	goto yy5;
	}
yy13:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'I':
	case 'i':	goto yy26;
	default:	goto yy5;
	}
yy14:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'I':
	case 'i':	goto yy27;
	case 'L':
	case 'l':	goto yy28;
	default:	goto yy5;
	}
yy15:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'I':
	case 'i':	goto yy29;
	case 'O':
	case 'o':	goto yy30;
	default:	goto yy5;
	}
yy16:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'A':
	case 'a':	goto yy31;
	case 'U':
	case 'u':	goto yy32;
	default:	goto yy5;
	}
yy17:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'I':
	case 'i':	goto yy33;
	default:	goto yy5;
	}
yy18:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'I':
	case 'i':	goto yy34;
	default:	goto yy5;
	}
yy19:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'N':
	case 'n':	goto yy35;
	default:	goto yy5;
	}
yy20:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'U':
	case 'u':	goto yy36;
	default:	goto yy5;
	}
yy21:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'E':
	case 'e':	goto yy37;
	case 'I':
	case 'i':	goto yy38;
	default:	goto yy5;
	}
yy22:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'E':
	case 'e':	goto yy39;
	case 'H':
	case 'h':	goto yy40;
	case 'R':
	case 'r':	goto yy41;
	case 'W':
	case 'w':	goto yy42;
	default:	goto yy5;
	}
yy23:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'E':
	case 'e':	goto yy43;
	default:	goto yy5;
	}
yy24:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy44;
	default:	goto yy25;
	}
yy25:
	YYCURSOR = YYMARKER;
	switch (yyaccept) {
	case 0: 	goto yy5;
	case 1: 	goto yy45;
	case 2: 	goto yy64;
	case 3: 	goto yy66;
	case 4: 	goto yy85;
	case 5: 	goto yy92;
	case 6: 	goto yy111;
	case 7: 	goto yy134;
	case 8: 	goto yy161;
	case 9: 	goto yy219;
	case 10: 	goto yy246;
	case 11: 	goto yy256;
	case 12: 	goto yy264;
	case 13: 	goto yy267;
	case 14: 	goto yy279;
	default:	goto yy304;
	}
yy26:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy46;
	default:	goto yy25;
	}
yy27:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'G':
	case 'g':	goto yy47;
	default:	goto yy25;
	}
yy28:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy48;
	default:	goto yy25;
	}
yy29:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'F':
	case 'f':	goto yy49;
	case 'R':
	case 'r':	goto yy50;
	case 'V':
	case 'v':	goto yy51;
	default:	goto yy25;
	}
yy30:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy52;
	case 'U':
	case 'u':	goto yy53;
	default:	goto yy25;
	}
yy31:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy54;
	default:	goto yy25;
	}
yy32:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy55;
	default:	goto yy25;
	}
yy33:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy56;
	default:	goto yy25;
	}
yy34:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy57;
	default:	goto yy25;
	}
yy35:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy58;
	default:	goto yy25;
	}
yy36:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy60;
	default:	goto yy25;
	}
yy37:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy61;
	case 'V':
	case 'v':	goto yy62;
	default:	goto yy25;
	}
yy38:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'X':
	case 'x':	goto yy63;
	default:	goto yy25;
	}
yy39:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy65;
	default:	goto yy25;
	}
yy40:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy67;
	case 'O':
	case 'o':	goto yy68;
	case 'R':
	case 'r':	goto yy69;
	default:	goto yy25;
	}
yy41:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy70;
	default:	goto yy25;
	}
yy42:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy71;
	case 'O':
	case 'o':	goto yy72;
	default:	goto yy25;
	}
yy43:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy74;
	default:	goto yy25;
	}
yy44:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case ' ':	goto yy75;
	default:	goto yy45;
	}
yy45:
#line 20 "scanner.re"
	{ return TOKEN_AND; }
#line 403 "scanner.c"
yy46:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy76;
	default:	goto yy25;
	}
yy47:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy77;
	default:	goto yy25;
	}
yy48:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'V':
	case 'v':	goto yy78;
	default:	goto yy25;
	}
yy49:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy79;
	default:	goto yy25;
	}
yy50:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy80;
	default:	goto yy25;
	}
yy51:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy81;
	default:	goto yy25;
	}
yy52:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy83;
	default:	goto yy25;
	}
yy53:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy84;
	default:	goto yy25;
	}
yy54:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'F':
	case 'f':	goto yy86;
	case 'V':
	case 'v':	goto yy88;
	default:	goto yy25;
	}
yy55:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy89;
	default:	goto yy25;
	}
yy56:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy90;
	default:	goto yy25;
	}
yy57:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy91;
	case 'T':
	case 't':	goto yy93;
	default:	goto yy25;
	}
yy58:
	++YYCURSOR;
#line 24 "scanner.re"
	{ return TOKEN_ONE; }
#line 496 "scanner.c"
yy60:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy94;
	default:	goto yy25;
	}
yy61:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy95;
	default:	goto yy25;
	}
yy62:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy96;
	default:	goto yy25;
	}
yy63:
	yyaccept = 2;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy97;
	default:	goto yy64;
	}
yy64:
#line 29 "scanner.re"
	{ return TOKEN_SIX; }
#line 529 "scanner.c"
yy65:
	yyaccept = 3;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy98;
	default:	goto yy66;
	}
yy66:
#line 33 "scanner.re"
	{ return TOKEN_TEN; }
#line 541 "scanner.c"
yy67:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy99;
	default:	goto yy25;
	}
yy68:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'U':
	case 'u':	goto yy100;
	default:	goto yy25;
	}
yy69:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy101;
	default:	goto yy25;
	}
yy70:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy102;
	default:	goto yy25;
	}
yy71:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy103;
	case 'N':
	case 'n':	goto yy104;
	default:	goto yy25;
	}
yy72:
	++YYCURSOR;
#line 25 "scanner.re"
	{ return TOKEN_TWO; }
#line 583 "scanner.c"
yy74:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy105;
	default:	goto yy25;
	}
yy75:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy107;
	default:	goto yy25;
	}
yy76:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy109;
	default:	goto yy25;
	}
yy77:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy110;
	default:	goto yy25;
	}
yy78:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy112;
	default:	goto yy25;
	}
yy79:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy113;
	case 'H':
	case 'h':	goto yy114;
	case 'I':
	case 'i':	goto yy116;
	case 'Y':
	case 'y':	goto yy117;
	default:	goto yy25;
	}
yy80:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy119;
	default:	goto yy25;
	}
yy81:
	++YYCURSOR;
#line 28 "scanner.re"
	{ return TOKEN_FIVE; }
#line 643 "scanner.c"
yy83:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'Y':
	case 'y':	goto yy121;
	default:	goto yy25;
	}
yy84:
	yyaccept = 4;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy123;
	default:	goto yy85;
	}
yy85:
#line 27 "scanner.re"
	{ return TOKEN_FOUR; }
#line 662 "scanner.c"
yy86:
	++YYCURSOR;
#line 134 "scanner.re"
	{ return TOKEN_HALF; }
#line 667 "scanner.c"
yy88:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy124;
	default:	goto yy25;
	}
yy89:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy125;
	default:	goto yy25;
	}
yy90:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy126;
	default:	goto yy25;
	}
yy91:
	yyaccept = 5;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy127;
	default:	goto yy92;
	}
yy92:
#line 32 "scanner.re"
	{ return TOKEN_NINE; }
#line 700 "scanner.c"
yy93:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy128;
	case 'H':
	case 'h':	goto yy129;
	default:	goto yy25;
	}
yy94:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy131;
	default:	goto yy25;
	}
yy95:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy132;
	default:	goto yy25;
	}
yy96:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy133;
	default:	goto yy25;
	}
yy97:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy135;
	case 'H':
	case 'h':	goto yy136;
	case 'I':
	case 'i':	goto yy138;
	case 'Y':
	case 'y':	goto yy139;
	default:	goto yy25;
	}
yy98:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy141;
	default:	goto yy25;
	}
yy99:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy143;
	case 'T':
	case 't':	goto yy145;
	default:	goto yy25;
	}
yy100:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy146;
	default:	goto yy25;
	}
yy101:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy147;
	default:	goto yy25;
	}
yy102:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy149;
	default:	goto yy25;
	}
yy103:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'F':
	case 'f':	goto yy150;
	case 'V':
	case 'v':	goto yy151;
	default:	goto yy25;
	}
yy104:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy152;
	default:	goto yy25;
	}
yy105:
	++YYCURSOR;
#line 23 "scanner.re"
	{ return TOKEN_ZERO; }
#line 801 "scanner.c"
yy107:
	++YYCURSOR;
#line 21 "scanner.re"
	{ return TOKEN_AND_A; }
#line 806 "scanner.c"
yy109:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy153;
	default:	goto yy25;
	}
yy110:
	yyaccept = 6;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'E':
	case 'e':	goto yy154;
	case 'H':
	case 'h':	goto yy155;
	case 'I':
	case 'i':	goto yy157;
	case 'Y':
	case 'y':	goto yy158;
	default:	goto yy111;
	}
yy111:
#line 31 "scanner.re"
	{ return TOKEN_EIGHT; }
#line 831 "scanner.c"
yy112:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy160;
	default:	goto yy25;
	}
yy113:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy162;
	default:	goto yy25;
	}
yy114:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy163;
	default:	goto yy115;
	}
yy115:
#line 69 "scanner.re"
	{ return TOKEN_FIFTH; }
#line 856 "scanner.c"
yy116:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy165;
	default:	goto yy25;
	}
yy117:
	++YYCURSOR;
#line 49 "scanner.re"
	{ return TOKEN_FIFTY; }
#line 868 "scanner.c"
yy119:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy166;
	default:	goto yy120;
	}
yy120:
#line 61 "scanner.re"
	{ return TOKEN_FIRST; }
#line 879 "scanner.c"
yy121:
	++YYCURSOR;
#line 47 "scanner.re"
	{ return TOKEN_FORTY; }
#line 884 "scanner.c"
yy123:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy168;
	case 'H':
	case 'h':	goto yy169;
	case 'I':
	case 'i':	goto yy171;
	case 'Y':
	case 'y':	goto yy172;
	default:	goto yy25;
	}
yy124:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy174;
	default:	goto yy25;
	}
yy125:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy176;
	default:	goto yy25;
	}
yy126:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy177;
	default:	goto yy25;
	}
yy127:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy178;
	case 'H':
	case 'h':	goto yy179;
	case 'I':
	case 'i':	goto yy181;
	case 'Y':
	case 'y':	goto yy182;
	default:	goto yy25;
	}
yy128:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy184;
	default:	goto yy25;
	}
yy129:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy185;
	default:	goto yy130;
	}
yy130:
#line 79 "scanner.re"
	{ return TOKEN_NINTH; }
#line 949 "scanner.c"
yy131:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy187;
	default:	goto yy25;
	}
yy132:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy188;
	default:	goto yy25;
	}
yy133:
	yyaccept = 7;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy190;
	default:	goto yy134;
	}
yy134:
#line 30 "scanner.re"
	{ return TOKEN_SEVEN; }
#line 975 "scanner.c"
yy135:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy191;
	default:	goto yy25;
	}
yy136:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy192;
	default:	goto yy137;
	}
yy137:
#line 71 "scanner.re"
	{ return TOKEN_SIXTH; }
#line 993 "scanner.c"
yy138:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy194;
	default:	goto yy25;
	}
yy139:
	++YYCURSOR;
#line 50 "scanner.re"
	{ return TOKEN_SIXTY; }
#line 1005 "scanner.c"
yy141:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy195;
	default:	goto yy142;
	}
yy142:
#line 82 "scanner.re"
	{ return TOKEN_TENTH; }
#line 1016 "scanner.c"
yy143:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy197;
	default:	goto yy144;
	}
yy144:
#line 65 "scanner.re"
	{ return TOKEN_THIRD; }
#line 1027 "scanner.c"
yy145:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy199;
	case 'I':
	case 'i':	goto yy200;
	case 'Y':
	case 'y':	goto yy201;
	default:	goto yy25;
	}
yy146:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy203;
	default:	goto yy25;
	}
yy147:
	++YYCURSOR;
#line 26 "scanner.re"
	{ return TOKEN_THREE; }
#line 1050 "scanner.c"
yy149:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy204;
	default:	goto yy25;
	}
yy150:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy205;
	default:	goto yy25;
	}
yy151:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy206;
	default:	goto yy25;
	}
yy152:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy208;
	case 'Y':
	case 'y':	goto yy209;
	default:	goto yy25;
	}
yy153:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy211;
	default:	goto yy25;
	}
yy154:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy213;
	default:	goto yy25;
	}
yy155:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy214;
	default:	goto yy156;
	}
yy156:
#line 75 "scanner.re"
	{ return TOKEN_EIGHTH; }
#line 1105 "scanner.c"
yy157:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy216;
	default:	goto yy25;
	}
yy158:
	++YYCURSOR;
#line 52 "scanner.re"
	{ return TOKEN_EIGHTY; }
#line 1117 "scanner.c"
yy160:
	yyaccept = 8;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy217;
	default:	goto yy161;
	}
yy161:
#line 34 "scanner.re"
	{ return TOKEN_ELEVEN; }
#line 1129 "scanner.c"
yy162:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy218;
	default:	goto yy25;
	}
yy163:
	++YYCURSOR;
#line 70 "scanner.re"
	{ return TOKEN_FIFTHS; }
#line 1141 "scanner.c"
yy165:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy220;
	default:	goto yy25;
	}
yy166:
	++YYCURSOR;
#line 62 "scanner.re"
	{ return TOKEN_FIRSTS; }
#line 1153 "scanner.c"
yy168:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy221;
	default:	goto yy25;
	}
yy169:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy222;
	default:	goto yy170;
	}
yy170:
#line 67 "scanner.re"
	{ return TOKEN_FOURTH; }
#line 1171 "scanner.c"
yy171:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy224;
	default:	goto yy25;
	}
yy172:
	++YYCURSOR;
#line 48 "scanner.re"
	{ return TOKEN_FORTY; }
#line 1183 "scanner.c"
yy174:
	++YYCURSOR;
#line 135 "scanner.re"
	{ return TOKEN_HALVES; }
#line 1188 "scanner.c"
yy176:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy225;
	default:	goto yy25;
	}
yy177:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy227;
	default:	goto yy25;
	}
yy178:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy229;
	default:	goto yy25;
	}
yy179:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy230;
	default:	goto yy180;
	}
yy180:
#line 77 "scanner.re"
	{ return TOKEN_NINTH; }
#line 1220 "scanner.c"
yy181:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy232;
	default:	goto yy25;
	}
yy182:
	++YYCURSOR;
#line 53 "scanner.re"
	{ return TOKEN_NINETY; }
#line 1232 "scanner.c"
yy184:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy233;
	default:	goto yy25;
	}
yy185:
	++YYCURSOR;
#line 80 "scanner.re"
	{ return TOKEN_NINTHS; }
#line 1244 "scanner.c"
yy187:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy235;
	default:	goto yy25;
	}
yy188:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy237;
	default:	goto yy189;
	}
yy189:
#line 63 "scanner.re"
	{ return TOKEN_SECOND; }
#line 1262 "scanner.c"
yy190:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy239;
	case 'H':
	case 'h':	goto yy240;
	case 'I':
	case 'i':	goto yy242;
	case 'Y':
	case 'y':	goto yy243;
	default:	goto yy25;
	}
yy191:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy245;
	default:	goto yy25;
	}
yy192:
	++YYCURSOR;
#line 72 "scanner.re"
	{ return TOKEN_SIXTHS; }
#line 1287 "scanner.c"
yy194:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy247;
	default:	goto yy25;
	}
yy195:
	++YYCURSOR;
#line 83 "scanner.re"
	{ return TOKEN_TENTHS; }
#line 1299 "scanner.c"
yy197:
	++YYCURSOR;
#line 66 "scanner.re"
	{ return TOKEN_THIRDS; }
#line 1304 "scanner.c"
yy199:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy248;
	default:	goto yy25;
	}
yy200:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy249;
	default:	goto yy25;
	}
yy201:
	++YYCURSOR;
#line 46 "scanner.re"
	{ return TOKEN_THIRTY; }
#line 1323 "scanner.c"
yy203:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy250;
	default:	goto yy25;
	}
yy204:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy251;
	default:	goto yy25;
	}
yy205:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy252;
	default:	goto yy25;
	}
yy206:
	++YYCURSOR;
#line 35 "scanner.re"
	{ return TOKEN_TWELVE; }
#line 1349 "scanner.c"
yy208:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy254;
	default:	goto yy25;
	}
yy209:
	++YYCURSOR;
#line 45 "scanner.re"
	{ return TOKEN_TWENTY; }
#line 1361 "scanner.c"
yy211:
	++YYCURSOR;
#line 58 "scanner.re"
	{ return TOKEN_BILLION; }
#line 1366 "scanner.c"
yy213:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy255;
	default:	goto yy25;
	}
yy214:
	++YYCURSOR;
#line 76 "scanner.re"
	{ return TOKEN_EIGHTHS; }
#line 1378 "scanner.c"
yy216:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy257;
	default:	goto yy25;
	}
yy217:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy258;
	default:	goto yy25;
	}
yy218:
	yyaccept = 9;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy260;
	default:	goto yy219;
	}
yy219:
#line 38 "scanner.re"
	{ return TOKEN_FIFTEEN; }
#line 1404 "scanner.c"
yy220:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy261;
	default:	goto yy25;
	}
yy221:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy263;
	default:	goto yy25;
	}
yy222:
	++YYCURSOR;
#line 68 "scanner.re"
	{ return TOKEN_FOURTHS; }
#line 1423 "scanner.c"
yy224:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy265;
	default:	goto yy25;
	}
yy225:
	++YYCURSOR;
#line 55 "scanner.re"
	{ return TOKEN_HUNDRED; }
#line 1435 "scanner.c"
yy227:
	++YYCURSOR;
#line 57 "scanner.re"
	{ return TOKEN_MILLION; }
#line 1440 "scanner.c"
yy229:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy266;
	default:	goto yy25;
	}
yy230:
	++YYCURSOR;
#line 78 "scanner.re"
	{ return TOKEN_NINTHS; }
#line 1452 "scanner.c"
yy232:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy268;
	default:	goto yy25;
	}
yy233:
	++YYCURSOR;
#line 43 "scanner.re"
	{ return TOKEN_NINETEEN; }
#line 1464 "scanner.c"
yy235:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy269;
	default:	goto yy236;
	}
yy236:
#line 131 "scanner.re"
	{ return TOKEN_QUARTER; }
#line 1475 "scanner.c"
yy237:
	++YYCURSOR;
#line 64 "scanner.re"
	{ return TOKEN_SECONDS; }
#line 1480 "scanner.c"
yy239:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy271;
	default:	goto yy25;
	}
yy240:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy272;
	default:	goto yy241;
	}
yy241:
#line 73 "scanner.re"
	{ return TOKEN_SEVENTH; }
#line 1498 "scanner.c"
yy242:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy274;
	default:	goto yy25;
	}
yy243:
	++YYCURSOR;
#line 51 "scanner.re"
	{ return TOKEN_SEVENTY; }
#line 1510 "scanner.c"
yy245:
	yyaccept = 10;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy275;
	default:	goto yy246;
	}
yy246:
#line 39 "scanner.re"
	{ return TOKEN_SIXTEEN; }
#line 1522 "scanner.c"
yy247:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy276;
	default:	goto yy25;
	}
yy248:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy278;
	default:	goto yy25;
	}
yy249:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy280;
	default:	goto yy25;
	}
yy250:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy281;
	default:	goto yy25;
	}
yy251:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy283;
	default:	goto yy25;
	}
yy252:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy285;
	default:	goto yy253;
	}
yy253:
#line 86 "scanner.re"
	{ return TOKEN_TWELFTH; }
#line 1568 "scanner.c"
yy254:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy287;
	default:	goto yy25;
	}
yy255:
	yyaccept = 11;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy288;
	default:	goto yy256;
	}
yy256:
#line 41 "scanner.re"
	{ return TOKEN_EIGHTEEN; }
#line 1587 "scanner.c"
yy257:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy289;
	default:	goto yy25;
	}
yy258:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy291;
	default:	goto yy259;
	}
yy259:
#line 84 "scanner.re"
	{ return TOKEN_ELEVENTH; }
#line 1605 "scanner.c"
yy260:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy293;
	default:	goto yy25;
	}
yy261:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy295;
	default:	goto yy262;
	}
yy262:
#line 109 "scanner.re"
	{ return TOKEN_FIFTIETH; }
#line 1623 "scanner.c"
yy263:
	yyaccept = 12;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy297;
	default:	goto yy264;
	}
yy264:
#line 37 "scanner.re"
	{ return TOKEN_FOURTEEN; }
#line 1635 "scanner.c"
yy265:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy298;
	default:	goto yy25;
	}
yy266:
	yyaccept = 13;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy300;
	default:	goto yy267;
	}
yy267:
#line 42 "scanner.re"
	{ return TOKEN_NINETEEN; }
#line 1654 "scanner.c"
yy268:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy301;
	default:	goto yy25;
	}
yy269:
	++YYCURSOR;
#line 132 "scanner.re"
	{ return TOKEN_QUARTERS; }
#line 1666 "scanner.c"
yy271:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy303;
	default:	goto yy25;
	}
yy272:
	++YYCURSOR;
#line 74 "scanner.re"
	{ return TOKEN_SEVENTHS; }
#line 1678 "scanner.c"
yy274:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy305;
	default:	goto yy25;
	}
yy275:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy306;
	default:	goto yy25;
	}
yy276:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy308;
	default:	goto yy277;
	}
yy277:
#line 111 "scanner.re"
	{ return TOKEN_SIXTIETH; }
#line 1703 "scanner.c"
yy278:
	yyaccept = 14;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy310;
	default:	goto yy279;
	}
yy279:
#line 36 "scanner.re"
	{ return TOKEN_THIRTEEN; }
#line 1715 "scanner.c"
yy280:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy311;
	default:	goto yy25;
	}
yy281:
	++YYCURSOR;
#line 56 "scanner.re"
	{ return TOKEN_THOUSAND; }
#line 1727 "scanner.c"
yy283:
	++YYCURSOR;
#line 59 "scanner.re"
	{ return TOKEN_TRILLION; }
#line 1732 "scanner.c"
yy285:
	++YYCURSOR;
#line 87 "scanner.re"
	{ return TOKEN_TWELFTHS; }
#line 1737 "scanner.c"
yy287:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy313;
	default:	goto yy25;
	}
yy288:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy315;
	default:	goto yy25;
	}
yy289:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy317;
	default:	goto yy290;
	}
yy290:
#line 115 "scanner.re"
	{ return TOKEN_EIGHTIETH; }
#line 1762 "scanner.c"
yy291:
	++YYCURSOR;
#line 85 "scanner.re"
	{ return TOKEN_ELEVENTHS; }
#line 1767 "scanner.c"
yy293:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy319;
	default:	goto yy294;
	}
yy294:
#line 92 "scanner.re"
	{ return TOKEN_FIFTEENTH; }
#line 1778 "scanner.c"
yy295:
	++YYCURSOR;
#line 110 "scanner.re"
	{ return TOKEN_FIFTIETHS; }
#line 1783 "scanner.c"
yy297:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy321;
	default:	goto yy25;
	}
yy298:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy323;
	default:	goto yy299;
	}
yy299:
#line 107 "scanner.re"
	{ return TOKEN_FOURTIETH; }
#line 1801 "scanner.c"
yy300:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy325;
	default:	goto yy25;
	}
yy301:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy327;
	default:	goto yy302;
	}
yy302:
#line 117 "scanner.re"
	{ return TOKEN_NINETIETH; }
#line 1819 "scanner.c"
yy303:
	yyaccept = 15;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'T':
	case 't':	goto yy329;
	default:	goto yy304;
	}
yy304:
#line 40 "scanner.re"
	{ return TOKEN_SEVENTEEN; }
#line 1831 "scanner.c"
yy305:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy330;
	default:	goto yy25;
	}
yy306:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy332;
	default:	goto yy307;
	}
yy307:
#line 94 "scanner.re"
	{ return TOKEN_SIXTEENTH; }
#line 1849 "scanner.c"
yy308:
	++YYCURSOR;
#line 112 "scanner.re"
	{ return TOKEN_SIXTIETHS; }
#line 1854 "scanner.c"
yy310:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy334;
	default:	goto yy25;
	}
yy311:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy336;
	default:	goto yy312;
	}
yy312:
#line 105 "scanner.re"
	{ return TOKEN_THIRTIETH; }
#line 1872 "scanner.c"
yy313:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy338;
	default:	goto yy314;
	}
yy314:
#line 103 "scanner.re"
	{ return TOKEN_TWENTIETH; }
#line 1883 "scanner.c"
yy315:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy340;
	default:	goto yy316;
	}
yy316:
#line 98 "scanner.re"
	{ return TOKEN_EIGHTEENTH; }
#line 1894 "scanner.c"
yy317:
	++YYCURSOR;
#line 116 "scanner.re"
	{ return TOKEN_EIGHTIETHS; }
#line 1899 "scanner.c"
yy319:
	++YYCURSOR;
#line 93 "scanner.re"
	{ return TOKEN_FIFTEENTHS; }
#line 1904 "scanner.c"
yy321:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy342;
	default:	goto yy322;
	}
yy322:
#line 90 "scanner.re"
	{ return TOKEN_FOURTEENTH; }
#line 1915 "scanner.c"
yy323:
	++YYCURSOR;
#line 108 "scanner.re"
	{ return TOKEN_FOURTIETHS; }
#line 1920 "scanner.c"
yy325:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy344;
	default:	goto yy326;
	}
yy326:
#line 100 "scanner.re"
	{ return TOKEN_NINETEENTH; }
#line 1931 "scanner.c"
yy327:
	++YYCURSOR;
#line 118 "scanner.re"
	{ return TOKEN_NINETIETHS; }
#line 1936 "scanner.c"
yy329:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy346;
	default:	goto yy25;
	}
yy330:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy348;
	default:	goto yy331;
	}
yy331:
#line 113 "scanner.re"
	{ return TOKEN_SEVENTIETH; }
#line 1954 "scanner.c"
yy332:
	++YYCURSOR;
#line 95 "scanner.re"
	{ return TOKEN_SIXTEENTHS; }
#line 1959 "scanner.c"
yy334:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy350;
	default:	goto yy335;
	}
yy335:
#line 88 "scanner.re"
	{ return TOKEN_THIRTEENTH; }
#line 1970 "scanner.c"
yy336:
	++YYCURSOR;
#line 106 "scanner.re"
	{ return TOKEN_THIRTIETHS; }
#line 1975 "scanner.c"
yy338:
	++YYCURSOR;
#line 104 "scanner.re"
	{ return TOKEN_TWENTIETHS; }
#line 1980 "scanner.c"
yy340:
	++YYCURSOR;
#line 99 "scanner.re"
	{ return TOKEN_EIGHTEENTHS; }
#line 1985 "scanner.c"
yy342:
	++YYCURSOR;
#line 91 "scanner.re"
	{ return TOKEN_FOURTEENTHS; }
#line 1990 "scanner.c"
yy344:
	++YYCURSOR;
#line 101 "scanner.re"
	{ return TOKEN_NINETEENTHS; }
#line 1995 "scanner.c"
yy346:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'S':
	case 's':	goto yy352;
	default:	goto yy347;
	}
yy347:
#line 96 "scanner.re"
	{ return TOKEN_SEVENTEENTH; }
#line 2006 "scanner.c"
yy348:
	++YYCURSOR;
#line 114 "scanner.re"
	{ return TOKEN_SEVENTIETHS; }
#line 2011 "scanner.c"
yy350:
	++YYCURSOR;
#line 89 "scanner.re"
	{ return TOKEN_THIRTEENTHS; }
#line 2016 "scanner.c"
yy352:
	++YYCURSOR;
#line 97 "scanner.re"
	{ return TOKEN_SEVENTEENTHS; }
#line 2021 "scanner.c"
}
#line 143 "scanner.re"

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
