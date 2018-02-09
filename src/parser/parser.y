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

%token T_INT T_ID T_Return
%token T_LBracket T_RBracket T_LBrace T_RBrace
%token T_Comma
%token T_ADD

%type <exp> Function_Declaration Argument 
%type <exp> Statement Compound_Statement ReturnStatement
%type <exp> Expression Addition_Expression
%type <exp> TypeIdentifier
%type <string> TypeIdentifier

%start ROOT

Root 	:Function_Declaration

Function_Declaration : TypeIdentifier Identifier T_LBracket Arguement T_RBracket Statement

Argument : TypeIdentifier T_ID
					| TypeIdentifier T_ID T_Comma Argument

Statement: T_LBrace CompoundStatement T_RBrace 

Compound_Statement : ReturnStatement
									| IfStatement
									|	CompoundStatement

Return_Statement : T_Return Expression

Expression: T_ID
					| ADDITION_EXPRESSION
					| SUBTRACT_EXPRESSION

Addition_Expression: T_ID T_ADD T_ID

TypeIdentifier: T_INT


