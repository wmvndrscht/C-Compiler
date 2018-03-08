#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <iostream>


#include "../ast.hpp"
#include "ast_node.hpp"

class ReturnStatement : public Node {
public:
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ReturnExprStatement : public Node {
private:
	const NodePtr retexprstat;
public:
	ReturnExprStatement(const NodePtr _retexprstat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class CompoundStatement : public Node{
private:
	const NodePtr statlist;
	const NodePtr declist;
public:
	CompoundStatement(const NodePtr _statlist, const NodePtr _declist);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class StatementList : public Node{
private:
	const NodePtr statlist;
	const NodePtr stat;
public:
	StatementList(const NodePtr _statlist, const NodePtr _stat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class WhileStatement : public Node{
private:
	const NodePtr expr;
	const NodePtr stat;
public:
	WhileStatement(const NodePtr _expr, const NodePtr _stat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};


class IfStatement : public Node{
private:
	const NodePtr expr;
	const NodePtr stat;
public:
	IfStatement(const NodePtr _expr, const NodePtr _stat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class IfElseStatement : public Node{
private:
	const NodePtr expr;
	const NodePtr ifstat;
	const NodePtr elsestat;
public:
	IfElseStatement(const NodePtr _expr, const NodePtr _ifstat, const NodePtr _elsestat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ExprStatement : public Node{
private:
	const NodePtr expr;
public:
	ExprStatement(const NodePtr _expr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

#endif