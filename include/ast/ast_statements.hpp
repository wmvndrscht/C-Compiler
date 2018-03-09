#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <iostream>


#include "../ast.hpp"
#include "ast_node.hpp"


class ReturnStatement : public Statement {
public:
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ReturnExprStatement : public Statement {
private:
	const NodePtr retexprstat;
public:
	ReturnExprStatement(const NodePtr _retexprstat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class CompoundStatement : public Statement{
private:
	const Statement* statlist;
	const Declaration* declist;
public:
	CompoundStatement(const Statement* _statlist, const Declaration* _declist);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class StatementList : public Statement{
private:
	const Statement* statlist;
	const Statement* stat;
public:
	StatementList(const Statement* _statlist, const Statement* _stat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class WhileStatement : public Statement{
private:
	const NodePtr expr;
	const Statement* stat;
public:
	WhileStatement(const NodePtr _expr, const Statement* _stat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};


class IfStatement : public Statement{
private:
	const NodePtr expr;
	const Statement* stat;
public:
	IfStatement(const NodePtr _expr, const Statement* _stat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class IfElseStatement : public Statement{
private:
	const NodePtr expr;
	const Statement* ifstat;
	const Statement* elsestat;
public:
	IfElseStatement(const NodePtr _expr, const Statement* _ifstat, const Statement* _elsestat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ExprStatement : public Statement{
private:
	const NodePtr expr;
public:
	ExprStatement(const NodePtr _expr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

#endif