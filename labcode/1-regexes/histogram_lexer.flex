%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "histogram.hpp"


// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);

/* End the embedded code section. */

#include <string>

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


%%

<<<<<<< HEAD
[-]?[0-9]+[/][1-9]+ 					{ fprintf(stderr, "Fraction : %s\n", yytext); yyfractioncase();  return Number; }


[-]?[0-9]+([.][0-9]*)?        { fprintf(stderr, "Number : %s\n", yytext);  yylval.numberValue = atof(yytext);  																	return Number; }
=======
[0-9]+          { fprintf(stderr, "Number : %s\n", yytext); /* TODO: get value out of yytext and into yylval.numberValue */;  return Number; }
>>>>>>> 7dad724fc372a16e7b37fa2901418ffef73ab24d

[A-Za-z]+          						{ fprintf(stderr, "Word : %s\n", yytext);   yyconvertchar_to_string(); return 																		Word; }

[[][^\n\]]*[]] 								{ fprintf(stderr, "Bracket Word : %s\n", yytext);  remove_bracket(); return Word; }

.															{ fprintf(stderr, "Anything\n"); }
\n 														{ fprintf(stderr, "Newline \n");}



%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}

/* void bracketword(){
	for(i = 1; i++; i < (yyval.wordValue).length() -2){

	}
} */
