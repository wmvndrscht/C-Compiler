%option noyywrap

%{
	extern "C" int fileno(FILE *stream);

	#include "parser.tab.hpp"
	#include <string>

%}

IDENTIFIER [a-zA-Z_][0-9a-zA-Z_]*
 /*include mutiple constants eg hex, oct */
NUMBER 		 [0-9]+
HEX 			 [0][xX][0-9a-fA-F]+
OCTAL 		 [0][0-7]+

%%

"typedef"						{return T_TYPEDEF;}
"extern"						{return T_EXTERN;}
"static"						{return T_STATIC;}
"auto"							{return T_AUTO;}
"register"					{return T_REGISTER;}

"void"							{return T_VOID;}
"char"							{return T_CHAR;}
"short"							{return T_SHORT;}
"int"								{return T_INT;}
"long"							{return T_LONG;}
"float"							{return T_FLOAT;}
"double"						{return T_DOUBLE;}
"signed"						{return T_SIGNED;}

"const"							{return T_CONST;}
"volatile"					{return T_VOLATILE;}	

"return"						{return T_RETURN;}

"while"							{return T_WHILE;}
"if"								{return T_IF;}
"else"							{return T_ELSE;}
"for"								{return T_FOR;}
"do"								{return T_DO;}

{IDENTIFIER}				{yylval.str=new std::string(yytext);return T_IDENTIFIER;}
{NUMBER}						{yylval.number= new double(strtod(yytext, 0)); return T_NUMBER; }
{HEX}								{yylval.number = new double(strtol(yytext,NULL,16)); return T_NUMBER;}
{OCTAL}							{yylval.number = new double(strtol(yytext,NULL,8)); return T_NUMBER;}

"="									{yylval.str=new std::string(yytext);return T_EQUAL;}
";"									{return T_SEMICOLON;}
"{"									{return T_LCBRACK;}
"}"									{return T_RCBRACK;}
"("									{return T_LRBRACK;}
")"									{return T_RRBRACK;}
","									{return T_COMMA;}

"*"									{return T_TIMES;}
"+"									{return T_PLUS;}
"-"									{return T_MINUS;}
"=="								{return T_EQ;}
"||"								{return T_OR;}
"&&"								{return T_AND;}
"<"									{return T_LTHAN;}
">"									{return T_GTHAN;}
"&"									{return T_BAND;}

"/"									{return T_FSLASH;}
"%"									{return T_MODULO;}
"<<"								{return T_LSHIFT;}
">>"								{return T_RSHIFT;}
"<="								{return T_LTEQ;}
">="								{return T_GTEQ;}
"!="								{return T_NEQ;}
"^"									{return T_EXOR;}
"|"									{return T_BOR;}

"++"								{return T_INCR;}
"--"								{return T_DECR;}

"+="								{return T_PLUSEQUAL;}
"-="								{return T_SUBEQUAL;}
"*="								{return T_MULTEQUAL;}
"/="								{return T_DIVEQUAL;}
"%="								{return T_MODEQUAL;}
"<<="								{return T_LEFTEQUAL;}
">>="								{return T_RIGHTEQUAL;}
"&="								{return T_ANDEQUAL;}
"^="								{return T_EXEQUAL;}
"|="								{return T_OREQUAL;}
"["								{return T_LSQBRACK;}
"]"								{return T_RSQBRACK;}

"//".*		{;}

[ \t\r\n]+ 				{;}

.									{fprintf(stderr, "Invalid token\n"); fflush(stderr); exit(1); }

%%

void yyerror(char const *s){
	fprintf(stderr, "Parse error : %s\n", s);
	exit(1);
}
