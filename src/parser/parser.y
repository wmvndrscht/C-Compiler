%code requires{
	#include ast.hpp

	extern const Expression *g_root;

	int yylex(void);
	void yyerror(const char*);
}

/*int f(int x, int y){
		return x + y;
} 
*/

%union{
	const Expression *expr;
	double number;
	std::string *string;
}

/* token terminal */
%token T_INT T_ID T_Return
%token T_LBracket T_RBracket T_LBrace T_RBrace
%token T_Comma
%token T_ADD

/* non-terminal */
%type <exp> Function_Declaration Declaration_List
%type <exp> Statement Compound_Statement ReturnStatement
%type <exp> Expression Addition_Expression
%type <exp> TypeIdentifier
%type <exp> Program
%type <string> TypeIdentifier

/* start symbol */
%start Root

Root 	:	Program {ast_root = $1}

Program : Function_Declaration {$$ = $1}

Function_Declaration : TypeIdentifier Identifier T_LBracket Argument_List T_RBracket Statement {$$ = new Function_Declaration($1, $2, $4, $6);}

Declaration_List 	: Parameter	{$$ = $1}
									| Parameter T_Comma Declaration_List {$$ = $3}

Parameter: TypeIdentifier T_ID { $$ = new Parameter($1, $2);}

TypeIdentifier: T_INT { $$ = new TypeIdentifier($1);}

Statement: T_LBrace CompoundStatement T_RBrace {$$ = $2}

Compound_Statement : T_Return Expression {$$ = new ReturnStatement($1);}

Expression: Addition_Expression {$$ = $1}

Addition_Expression: T_ID T_ADD T_ID {$$ = new Addition_Expression($1, $3);}

const Expression *ast_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  ast_root=0;
  yyparse();
  return ast_root;
}
