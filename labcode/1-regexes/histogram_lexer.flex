/* 

This is the main lexer file consisting of 3 parts:
	-Declarations: defined named patterns
	-Pattern matching rules: mapping patterns to actions
	-User functions

The user function section can be surrounded by %{ }% to ensure it appears
embedded at top of output file

The whole idea is to list all the different categories (tokens) so that when
passed to the parser the parser has to do much less + it is easier understand

*/


%option noyywrap  /* ensures no wrap around after lexer finishes*/

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "histogram.hpp"


// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream); /* don't think it will affect me*/

/* End the embedded code section. */

#include <string>

/* yytext is a char* (pointer to a char), also there is int yyleng*/
void yyconvertchar_to_string(){
	std::string *str = new std::string(yytext);
	yylval.wordValue = str;
}


void yyfractioncase(){
	char* endptr;
	double first = strtod(yytext, &endptr);
	std::string str = std::string(endptr);
	str.erase (0,1);
	const char *end = str.c_str();;
	double last = strtod(end, NULL);
	yylval.numberValue = first/last;
}


void remove_bracket(){
	std::string *str = new std::string(yytext);
	str->erase (0,1);
	str->erase (strlen(yytext)-2,1);
	yylval.wordValue = str;
}



%}

/* the 3 parts are seperated by %% */

%%

[-]?[0-9]+[/][1-9]+ 					{ fprintf(stderr, "Fraction : %s\n", yytext); yyfractioncase();  return Number; }


[-]?[0-9]+([.][0-9]*)?        { fprintf(stderr, "Number : %s\n", yytext);  yylval.numberValue = atof(yytext);  return Number; }

[A-Za-z]+          						{ fprintf(stderr, "Word : %s\n", yytext);   yyconvertchar_to_string(); return Word; }

[[][^\n\]]*[]] 								{ fprintf(stderr, "Bracket Word : %s\n", yytext);  remove_bracket(); return Word; }

.															{ fprintf(stderr, "Anything\n"); }
\n 														{ fprintf(stderr, "Newline \n");}

/* . captures everything else *except* for newline */


%%

/* Error handler. This will get called if none of the rules match. */
/* This should never really be called */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}

