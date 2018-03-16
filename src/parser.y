%code requires{

	#include "ast.hpp"
	#include "ast/ast_node.hpp"
	#include "ast/ast_statements.hpp"
	#include "ast/ast_declarations.hpp"
	#include "ast/ast_expressions.hpp"
	#include <cassert>

	extern const Node *ast_root;

	int yylex(void);
	void yyerror(const char*);

	extern FILE* yyin;
}


%union{
	const Node *node;
	const Declaration *dec;
	const Statement* stat;
	const Expression* expr;
	const Identify* id;

	const DeclarationSpecifier *decspec;
	// const CompoundStatement* cstatement;
	std::string *str;
	double *number;

}

/* token terminal */
%token T_TYPEDEF T_EXTERN T_STATIC T_AUTO T_REGISTER
%token T_VOID T_CHAR T_SHORT T_INT T_LONG T_FLOAT T_DOUBLE T_SIGNED T_UNSIGNED
%token T_CONST T_VOLATILE
%token T_SEMICOLON T_EQUAL 
%token T_LCBRACK T_RCBRACK T_LRBRACK T_RRBRACK
%token T_IDENTIFIER
%token T_RETURN T_WHILE T_FOR T_DO
%token T_NUMBER
%token T_COMMA T_IF T_ELSE
%token T_TIMES T_PLUS T_MINUS T_EQ T_OR T_AND T_LTHAN T_GTHAN T_BAND
%token T_FSLASH T_MODULO T_LSHIFT T_RSHIFT T_LTEQ T_GTEQ T_NEQ T_EXOR T_BOR
%token T_INCR 


/* non-terminal */
/* --------------------------- Start node  ------------------------------- */
%type<node> ROOT Translation_Unit External_Declaration 
/* Statement */

/* --------------------------- Declaration ------------------------------- */
%type<dec> Function_Definition
%type<dec> Declaration_List
%type<dec> Declaration 
%type<dec> Init_Declarator_List Init_Declarator
%type<dec> Declarator
%type<dec> Direct_Declarator
%type<decspec> Declaration_Specifiers
%type<dec> Parameter_Type_List Parameter_List Parameter_Declaration


/* --------------------------- Statement ------------------------------- */
%type<stat> Compound_Statement
%type<stat> Statement_List Statement Return_Statement Iteration_Statement
%type<stat> Selection_Statement Expression_Statement

/* --------------------------- Expression ------------------------------- */

%type<expr> Expression Initializer
%type<expr> Assignment_Expression Conditional_Expression Logical_OR_Expression
%type<expr> Logical_AND_Expression Inclusive_OR_Expression Exclusive_OR_Expression
%type<expr> AND_Expression Equality_Expression Relational_Expression Shift_Expression
%type<expr> Additive_Expression Multiplicative_Expression Cast_Expression
%type<expr> Unary_Expression   Unary_Operator
%type<expr> Argument_Expression_List

/* --------------------------- Identify ------------------------------- */

%type<id> Postfix_Expression Primary_Expression

/* --------------------------- Other ------------------------------- */

%type<str> Storage_Class_Specifier Type_Qualifier Type_Specifier
%type<str> T_IDENTIFIER T_EQUAL
%type<number> T_NUMBER

/* Begin the parse tree!!!!!!!!!! */

%%

/* --------------------------- START NODE  ------------------------------- */


ROOT:	Translation_Unit 	{ ast_root = $1; }

Translation_Unit	:	External_Declaration 	{$$ = $1;}
									| Translation_Unit External_Declaration	{$$ = new TranslationUnit($1, $2);}




/* --------------------------- DECLARATION ------------------------------- */


External_Declaration	:	Declaration 				{$$ = $1;}
											| Function_Definition	{$$ = $1;}

Function_Definition	:	Declaration_Specifiers Declarator Compound_Statement {$$ = new FunctionDefinition($1,$2,$3);}

Declaration_List	: Declaration 	{$$ = $1;}
									| Declaration_List Declaration {$$ = new DeclarationList($1,$2);}

Declaration 	:	Declaration_Specifiers T_SEMICOLON {$$ = new LoneDeclaration($1);}
							|	Declaration_Specifiers Init_Declarator_List T_SEMICOLON	{$$ = new TheDeclaration($1,$2); }


Parameter_Type_List : Parameter_List {$$ = $1;}

Parameter_List 	: Parameter_Declaration	{$$ = $1;}
								| Parameter_List T_COMMA  Parameter_Declaration {$$ = new ParamList($1,$3);}

Parameter_Declaration : Declaration_Specifiers Declarator {$$ = new ParamDeclaration($1,$2);}

Init_Declarator_List 	: Init_Declarator {$$ = $1;}
											| Init_Declarator_List T_COMMA Init_Declarator {$$ = new InitDeclaratorList($1,$3);}

Init_Declarator :	Declarator T_EQUAL Initializer 	{$$ = new InitDeclarator($1,$3);}
								|	Declarator 											{$$ = new LoneInitDeclarator($1);} //Here make sure py_translate =0 

Declarator 	:	Direct_Declarator		{$$ = $1;}

Direct_Declarator	:	T_IDENTIFIER	{$$ = new VariableDeclarator(*$1);}
									|	Direct_Declarator T_LRBRACK T_RRBRACK {$$ = new EmptyDeclarator($1);}
									| Direct_Declarator T_LRBRACK Parameter_Type_List T_RRBRACK {$$ = new ParamListDeclarator($1,$3);}


Declaration_Specifiers	:	Storage_Class_Specifier Declaration_Specifiers 	{$$ = new DeclarationSpecifier(*$1,$2); }
												|	Storage_Class_Specifier													{$$ = new DeclarationSpecifier(*$1,NULL); }
												| Type_Specifier Declaration_Specifiers						{$$ = new DeclarationSpecifier(*$1,$2); }				 
												| Type_Specifier																	{$$ = new DeclarationSpecifier(*$1,NULL); }	
												| Type_Qualifier Declaration_Specifiers						{$$ = new DeclarationSpecifier(*$1,$2); }
												| Type_Qualifier																	{$$ = new DeclarationSpecifier(*$1,NULL); }

Storage_Class_Specifier	:	T_TYPEDEF		{$$ = new std::string("typedef");}	
												| T_EXTERN		{$$ = new std::string("extern");}
												| T_STATIC		{$$ = new std::string("static");}
												| T_AUTO			{$$ = new std::string("auto");}
												| T_REGISTER	{$$ = new std::string("register");}

Type_Specifier	:	T_VOID			{$$ = new std::string("void");}
								| T_CHAR			{$$ = new std::string("char");}
								| T_SHORT			{$$ = new std::string("short");}
								| T_INT				{$$ = new std::string("int");}							| T_LONG			{$$ = new std::string("long");}
								| T_FLOAT			{$$ = new std::string("float");}
								| T_DOUBLE		{$$ = new std::string("double");}
								| T_SIGNED 		{$$ = new std::string("signed");}
								| T_UNSIGNED	{$$ = new std::string("unsigned");}

Type_Qualifier	:	T_CONST			{$$ = new std::string("const");}
								| T_VOLATILE	{$$ = new std::string("volatile");}




/* --------------------------- STATEMENT ------------------------------- */


Compound_Statement	: T_LCBRACK T_RCBRACK	{$$ = new CompoundStatement(NULL, NULL);}
										| T_LCBRACK Statement_List T_RCBRACK	{$$ = new CompoundStatement($2, NULL);}
										| T_LCBRACK Declaration_List T_RCBRACK {$$ = new CompoundStatement(NULL, $2);}
									  | T_LCBRACK Declaration_List Statement_List T_RCBRACK {$$ = new CompoundStatement($3,$2);}



Statement_List	: Statement {$$ = $1;}
								| Statement_List Statement {$$ = new StatementList($1,$2);}

Statement : Compound_Statement	{$$ = $1;}
					| Selection_Statement {$$ = $1;}
					| Iteration_Statement	{$$ = $1;}
					| Expression_Statement {$$ = $1;}
					| Return_Statement	{$$ = $1;}

Expression_Statement : Expression T_SEMICOLON { $$ = new ExprStatement($1);}

Selection_Statement : T_IF T_LRBRACK Expression T_RRBRACK Statement T_ELSE Statement {$$ = new IfElseStatement($3,$5,$7);} //need to cover if-else crux
										| T_IF T_LRBRACK Expression T_RRBRACK Statement {$$ = new IfStatement($3,$5);}

Iteration_Statement : T_WHILE T_LRBRACK Expression T_RRBRACK Statement {$$ = new WhileStatement($3,$5);}
										| T_DO Statement T_WHILE T_LRBRACK Expression T_RRBRACK T_SEMICOLON {$$ = new DoWhileStatement($2,$5);}
										| T_FOR T_LRBRACK Expression_Statement Expression_Statement Expression T_RRBRACK Statement {$$ = new ForStatStatExpr($3,$4,$5,$7);}
										| T_FOR T_LRBRACK Declaration Expression_Statement Expression T_RRBRACK Statement {$$ = new ForDecStatExpr($3,$4,$5,$7);}


Return_Statement	:	T_RETURN T_SEMICOLON	{ $$ = new ReturnStatement(); }
									| T_RETURN Expression T_SEMICOLON {$$ = new ReturnExprStatement($2);}



/* --------------------------- EXPRESSION ------------------------------- */


Expression 	: Assignment_Expression {$$ = $1;}


Initializer	: Assignment_Expression	{$$ = $1;}

Assignment_Expression	:	Conditional_Expression {$$ = $1;}
											| Unary_Expression T_EQUAL Assignment_Expression {$$ = new AssignEqExpr($1,$3);}

// Assignment_Operator : T_EQUAL { $$ = new AssignmentOperator($1);}

Conditional_Expression	: Logical_OR_Expression {$$ = $1;}

Logical_OR_Expression	: Logical_AND_Expression {$$ = $1;}
											| Logical_OR_Expression T_OR Logical_AND_Expression { $$ = new ORExpression($1,$3);}

Logical_AND_Expression	: Inclusive_OR_Expression {$$ = $1;}
												| Logical_AND_Expression T_AND Logical_OR_Expression { $$ = new ANDExpression($1,$3);}

Inclusive_OR_Expression	: Exclusive_OR_Expression {$$ = $1;}
												| Inclusive_OR_Expression T_EXOR Exclusive_OR_Expression {$$ = new ExclusiveORExpression($1,$3);}


Exclusive_OR_Expression	:	AND_Expression {$$ = $1;}
												| Exclusive_OR_Expression T_BOR AND_Expression {$$ = new InclusiveORExpression($1,$3);}

AND_Expression :	Equality_Expression {$$ = $1;}
							 |  AND_Expression T_BAND Equality_Expression {$$ = new BANDExpression($1,$3);}

Equality_Expression	:	Relational_Expression {$$ = $1;}
										| Equality_Expression T_EQ Relational_Expression {$$ = new EqualityExpression($1,$3);}
										| Equality_Expression T_NEQ Relational_Expression {$$ = new NEQExpression($1,$3);}

Relational_Expression	: Shift_Expression {$$ = $1;}
											| Relational_Expression T_LTHAN Shift_Expression {$$ = new LessThanExpression($1,$3);}
											| Relational_Expression T_GTHAN Shift_Expression {$$ = new GreaterThanExpression($1,$3);}
											| Relational_Expression T_LTEQ Shift_Expression {$$ = new LTEQExpression($1,$3);}
											| Relational_Expression T_GTEQ Shift_Expression {$$ = new GTEQExpression($1,$3);}


Shift_Expression : Additive_Expression {$$ = $1;}
								 | Shift_Expression T_LSHIFT Additive_Expression {$$ = new LshiftExpression($1,$3);}
								 | Shift_Expression T_RSHIFT Additive_Expression {$$ = new RshiftExpression($1,$3);}

Unary_Expression	: Postfix_Expression {$$ = $1;}
									| Unary_Operator Cast_Expression {$$ = new UnaryOpExpr($1,$2);}

Unary_Operator : T_BAND	{$$ = new UnaryOp(std::string("&"));} //;new std::string("&");}
							 | T_TIMES {$$ = new UnaryOp(std::string("*"));} //{$$ = new std::string("*");}
							 | T_PLUS {$$ = new UnaryOp(std::string("+"));} //{$$ = new std::string("+");}
							 | T_MINUS {$$ = new UnaryOp(std::string("-"));} //{$$ = new std::string("-");}

Cast_Expression :	Unary_Expression {$$ = $1;}

Multiplicative_Expression : Cast_Expression {$$ = $1;} 
													| Multiplicative_Expression T_TIMES Cast_Expression {$$ = new MultExpression($1,$3);}
													| Multiplicative_Expression T_FSLASH Cast_Expression {$$ = new DivExpression($1,$3);}
													| Multiplicative_Expression T_MODULO Cast_Expression {$$ = new ModExpression($1,$3);}

Additive_Expression	: Multiplicative_Expression {$$ = $1;}
										| Additive_Expression T_PLUS  Multiplicative_Expression {$$ = new AddExpression($1,$3);}
										| Additive_Expression T_MINUS Multiplicative_Expression {$$ = new SubExpression($1,$3);} //positive vs neg num


Postfix_Expression	: Primary_Expression {$$ = $1;}
										| Postfix_Expression T_LRBRACK T_RRBRACK {$$ = new LonePostfixExpression($1);}
										| Postfix_Expression T_LRBRACK Argument_Expression_List T_RRBRACK {$$ = new PostfixArguExpression($1,$3);}
										| Postfix_Expression T_INCR {$$ = new PostIncrementExpr($1);}

Argument_Expression_List 	: Assignment_Expression 	{$$ = $1;}
													| Argument_Expression_List T_COMMA Assignment_Expression {$$ = new AssignExprList($1,$3);}

Primary_Expression	: T_IDENTIFIER	{$$ = new ExpressionVariable($1);}
										| T_NUMBER				{$$ = new Value($1);}
										| T_LRBRACK Expression T_RRBRACK {$$ = new ParenExpr($2);}







	/*
		Init_Declarator :	Declarator T_EQUAL Initializer
									| T_LPAREN Declarator T_RPAREN 
									| Direct_Declarator T_LBRACK T_RBRACK
									| Direct_Declarator T_LBRACK Constant_Expression T_RBRACK */


%%

const Node *ast_root; // Definition of variable (to match declaration earlier)

const Node *parseAST(const char file[])
{
  ast_root=NULL;

  yyin = fopen(file, "r");
  yyparse();
  return ast_root;
}

