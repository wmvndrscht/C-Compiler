%code requires{

	#include ast.hpp

	extern const Expression *g_root;

	int yylex(void);
	void yyerror(const char*);

}


%union{
	const Expression *expr;
	double number;
	std::string *string;
}

/* token terminal */


/* non-terminal */


/* start symbol */

%start Root




const Expression *ast_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  ast_root=0;
  yyparse();
  return ast_root;
}
