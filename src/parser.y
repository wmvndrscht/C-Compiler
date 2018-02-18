%code requires{

	#include "ast.hpp"
	#include <cassert>

	extern const Node *ast_root;

	int yylex(void);
	void yyerror(const char*);

}


%union{
	const Node *node;
	const Declaration_Specifier *decspec;
	std::string *str;
}

/* token terminal */
%token T_TYPEDEF T_EXTERN T_STATIC T_AUTO T_REGISTER
%token T_VOID T_CHAR T_SHORT T_INT T_LONG T_FLOAT T_DOUBLE T_SIGNED T_UNSIGNED
%token T_CONST T_VOLATILE
%token T_SEMICOLON


/* non-terminal */
%type<node> ROOT Translation_Unit External_Declaration 
%type<node> Declaration 
%type<decspec> Declaration_Specifiers
%type<str> Storage_Class_Specifier Type_Qualifier Type_Specifier



%%

ROOT:	Translation_Unit 	{ ast_root = $1; }

Translation_Unit	:	External_Declaration 	{$$ = $1;}
									| Translation_Unit External_Declaration	{$$ = new TranslationUnit($1, $2);}

External_Declaration	:	Declaration {$$ = $1;}

Declaration 	:	Declaration_Specifiers T_SEMICOLON {$$ = new LoneDeclaration($1);}
							|	Declaration_Specifiers Init_Declarator_List T_SEMICOLON

Init_Declarator_List 	: Declarator T_EQUAL INITIALIZER
											| Declarator

Declarator 	:	Direct_Declarator

Direct_Declarator	:	T_IDENTIFIER
									| T_LPAREN Declarator T_RPAREN 
									| Direct_Declarator T_LBRACK T_RBRACK
									| Direct_Declarator T_LBRACK Conditional_Expression T_RBRACK

Conditional_Expression	: Logical_OR_Expression

Logical_OR_Expression	: Logical_AND_Expression

Logical_AND_Expression	: Inclusive_OR_Expressoin

Inclusive_OR_Expressoin	: Exclusive_OR_Expression



Declaration_Specifiers	:	Storage_Class_Specifier Declaration_Specifiers 	{$$ = new Declaration_Specifier(*$1,$2); }
												|	Storage_Class_Specifier													{$$ = new Declaration_Specifier(*$1,NULL); }
												| Type_Specifier Declaration_Specifiers						{$$ = new Declaration_Specifier(*$1,$2); }				 
												| Type_Specifier																	{$$ = new Declaration_Specifier(*$1,NULL); }	
												| Type_Qualifier Declaration_Specifiers						{$$ = new Declaration_Specifier(*$1,$2); }
												| Type_Qualifier																	{$$ = new Declaration_Specifier(*$1,NULL); }

Storage_Class_Specifier	:	T_TYPEDEF		{$$ = new std::string("typedef");}	
												| T_EXTERN		{$$ = new std::string("extern");}
												| T_STATIC		{$$ = new std::string("static");}
												| T_AUTO			{$$ = new std::string("auto");}
												| T_REGISTER	{$$ = new std::string("register");}

Type_Specifier	:	T_VOID			{$$ = new std::string("void");}
								| T_CHAR			{$$ = new std::string("char");}
								| T_SHORT			{$$ = new std::string("short");}
								| T_INT				{$$ = new std::string("int");}
								| T_LONG			{$$ = new std::string("long");}
								| T_FLOAT			{$$ = new std::string("float");}
								| T_DOUBLE		{$$ = new std::string("double");}
								| T_SIGNED 		{$$ = new std::string("signed");}
								| T_UNSIGNED	{$$ = new std::string("unsigned");}

Type_Qualifier	:	T_CONST			{$$ = new std::string("const");}
								| T_VOLATILE	{$$ = new std::string("volatile");}

%%

const Node *ast_root; // Definition of variable (to match declaration earlier)

const Node *parseAST()
{
  ast_root=NULL;
  yyparse();
  return ast_root;
}
