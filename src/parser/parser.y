%code requires{

	#include ast.hpp

	extern const Node *ast_root;

	int yylex(void);
	void yyerror(const char*);

}


%union{
	const Node *node;
	const Declaration *declaration;
	std::string *str;


}

/* token terminal */
%token T_INT
%token T_SEMICOLON


/* non-terminal */


/* start symbol */
%start Root


ROOT:	Translation_Unit 	{ ast_root = $1; }

Translation_Unit:
	External_Declaration 	{$$ = $1;}
	| Translation_Unit External_Declaration	{$$ = new TranslationUnit($2, $1)}

External_Declaration:
	| Declaration {$$ = $1;}

Declaration: 
	Declaration_Specifiers T_SEMICOLON {$$ = new DeclarationSpecifier{$1};}

Declaration_Specifiers:
	Type_Specifier { $$ = $1;}

Type_Specifier:
	T_INT {$$ = new std::string("int");}




const Node *ast_root; // Definition of variable (to match declaration earlier)

const Node *parseAST()
{
  ast_root=0;
  yyparse();
  return ast_root;
}
