#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <iostream>


#include "../ast.hpp"
#include "ast_node.hpp"


class ReturnStatement : public Statement {
public:
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ReturnExprStatement : public Statement {
private:
	const NodePtr retexprstat;
public:
	ReturnExprStatement(const NodePtr _retexprstat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class CompoundStatement : public Statement{
private:
	const Statement* statlist;
	const Declaration* declist;
public:
	CompoundStatement(const Statement* _statlist, const Declaration* _declist);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class StatementList : public Statement{
private:
	const Statement* statlist;
	const Statement* stat;
public:
	StatementList(const Statement* _statlist, const Statement* _stat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class WhileStatement : public Statement{
private:
	const NodePtr expr;
	const Statement* stat;
public:
	WhileStatement(const NodePtr _expr, const Statement* _stat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};


class IfStatement : public Statement{
private:
	const NodePtr expr;
	const Statement* stat;
public:
	IfStatement(const NodePtr _expr, const Statement* _stat);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
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
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ExprStatement : public Statement{
private:
	const NodePtr expr;
public:
	ExprStatement(const NodePtr _expr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ForStatStatExpr : public Statement{
private:
	const Statement* stat1;
	const Statement* stat2;
	const Expression* expr;
	const Statement* body;
public:
	ForStatStatExpr(const Statement* _stat1,const Statement* _stat2,const Expression* _expr,
		const Statement* _body);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ForDecStatExpr : public Statement{
private:
	const Declaration* dec;
	const Statement* stat1;
	const Expression* expr;
	const Statement* body;
public:
	ForDecStatExpr(const Declaration* _dec,const Statement* _stat1,const Expression* _expr,
		const Statement* _body);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};



class DoWhileStatement : public Statement { 
private:
	const Statement* stat;
	const Expression* cond;
public:
	DoWhileStatement(const Statement* _stat, const Expression* _cond);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};




#endif