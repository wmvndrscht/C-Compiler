%option noyywrap


%{
	extern "C" int fileno(FILE *stream);
%}

%%

"int" 							{return T_INT;}
";"									{return T_SEMICOLON}

[ \t\r\n]+ 				{;}

.									{;}

%%

void yyerror(char const *s){
	fpritnf(stderr, "Parse error : %s\n, s");
	exit(1);
}