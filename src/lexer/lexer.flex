%option noyywrap


%{
	extern "C" int fileno(FILE *stream);
%}

%%

"int" 						{return T_INT;}
( 								{return T_LBracket; }
) 								{return T_RBracket; }
[a-zA-Z_]+ 				{return T_ID;}
,									{return T_Comma;}
{ 								{return T_LBrace;}
}									{return T_RBrace;}
"return"					{return T_Return;}
+									{return T_ADD;}


[ \t\r\n]+ 				{;}

.									{;}

%%

void yyerror(char const *s){
	fpritnf(stderr, "Parse error : %s\n, s");
	exit(1);
}