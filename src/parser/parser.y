

int f(int x, int y){
		return x + y;
}




Root : FunctionDeclaration
		| Declaration

FunctionDeclaration : T_TypeIdentifier Identifier T_LBracket Arguement T_RBracket Statement

Arguement : T_TypeIdentifier T_ID
					| T_TypeIdentifier T_ID T_Comma Arguement

Statement: T_LBrace CompoundStatement T_RBrace 

CompoundStatement : ReturnStatement
					| IfStatement
					|	CompoundStatement

ReturnStatement : T_Return Expression

Expression: T_ID
					| ADDITION_EXPRESSION
					| SUBTRACT_EXPRESSION

ADDITION_EXPRESSION: T_ID T_ADD T_ID


