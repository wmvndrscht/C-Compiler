#ifndef ast_expressions_hpp
#define ast_expressions_hpp

#include "../ast.hpp"
#include "ast_node.hpp"

class ExpressionVariable : public Node {
private:
	const std::string *variable;
public:
	ExpressionVariable(const std::string* _variable);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

class Value : public Node {
private:
	const double *number;
public:
	Value(const double* _number);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

class MultExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	MultExpression(const NodePtr _lhs, const NodePtr _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

class AssignExpr : public Node {
private:
	const NodePtr unaryexpr;
	const NodePtr assignop;
	const NodePtr assignexpr;
public:
	AssignExpr(const NodePtr _unaryexpr, const NodePtr _assignop,
	  const NodePtr _assignexpr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};


class AddExpression : public Node{
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	AddExpression(const NodePtr _lhs, const NodePtr _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

class SubExpression : public Node{
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	SubExpression(const NodePtr _lhs, const NodePtr _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

//Reduce this by inheriting lhs and rhs??
class ORExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	ORExpression(const NodePtr _lhs, const NodePtr _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

class ANDExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	ANDExpression(const NodePtr _lhs, const NodePtr _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

class LessThanExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	LessThanExpression(const NodePtr _lhs, const NodePtr _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

class GreaterThanExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	GreaterThanExpression(const NodePtr _lhs, const NodePtr _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

class EqualityExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	EqualityExpression(const NodePtr _lhs, const NodePtr _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};


class LonePostfixExpression : public Node{
private:
	const NodePtr expr;
public:
	LonePostfixExpression(const NodePtr _expr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

class PostfixArguExpression : public Node{
private:
	const NodePtr expr;
	const NodePtr arguexpr;
public:
	PostfixArguExpression(const NodePtr _expr, const NodePtr _arguexpr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

class AssignExprList : public Node{
private:
	const NodePtr exprlist;
	const NodePtr expr;
public:
	AssignExprList(const NodePtr _exprlist, const NodePtr _expr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

class UnaryOpExpr : public Node{
private:
	const NodePtr op;
	const NodePtr expr;
public:
	UnaryOpExpr(const NodePtr _op, const NodePtr _expr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};


class UnaryOp : public Node{
private:
	const std::string op;
public:
	UnaryOp(const std::string _op);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst) const override;
};

#endif
