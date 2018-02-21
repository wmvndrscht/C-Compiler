%option noyywrap

%{
	extern "C" int fileno(FILE *stream);

	#include "parser.tab.hpp"
	#include <string>
%}

IDENTIFIER [a-zA-Z_][0-9a-zA-Z]*

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

{IDENTIFIER}				{yylval.str=new std::string(yytext);return T_IDENTIFIER;}

"="									{return T_EQUAL;}
";"									{return T_SEMICOLON;}
"{"									{return T_LCBRACK;}
"}"									{return T_RCBRACK;}
"("									{return T_LRBRACK;}
")"									{return T_RRBRACK;}


[ \t\r\n]+ 				{;}

.									{fprintf(stderr, "Invalid token\n"); exit(1); }

%%

void yyerror(char const *s){
	fprintf(stderr, "Parse error : %s\n, s");
	exit(1);
}