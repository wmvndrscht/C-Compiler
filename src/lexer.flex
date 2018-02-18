%option noyywrap

%{
	extern "C" int fileno(FILE *stream);

	#include "parser.tab.hpp"
%}

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

";"									{return T_SEMICOLON;}


[ \t\r\n]+ 				{;}

.									{fprintf(stderr, "Invalid token\n"); exit(1); }

%%

void yyerror(char const *s){
	fprintf(stderr, "Parse error : %s\n, s");
	exit(1);
}