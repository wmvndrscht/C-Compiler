%code requires{

	#include "ast.hpp"
	#include <cassert>

	extern const Node *ast_root;

	int yylex(void);
	void yyerror(const char*);

}


%union{
	const Node *node;
	std::string *str;
}

/* token terminal */
%token T_INT
%token T_SEMICOLON


/* non-terminal */
%type<node> ROOT Translation_Unit External_Declaration 
%type<node> Declaration 
%type<str> Declaration_Specifiers 



%%

ROOT:	Translation_Unit 	{ ast_root = $1; }

Translation_Unit	:	External_Declaration 	{$$ = $1;}
									| Translation_Unit External_Declaration	{$$ = new TranslationUnit($2, $1);}

External_Declaration	:	Declaration {$$ = $1;}

Declaration 	: 	Declaration_Specifiers T_SEMICOLON {$$ = new LoneDeclaration(*$1);}

Declaration_Specifiers	:	T_INT {$$ = new std::string("int");}


%%

const Node *ast_root; // Definition of variable (to match declaration earlier)

const Node *parseAST()
{
  ast_root=NULL;
  yyparse();
  return ast_root;
}
