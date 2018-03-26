#ifndef ast_expressions_hpp
#define ast_expressions_hpp

#include "../ast.hpp"
#include "ast_node.hpp"

class ExpressionVariable : public Identify {
private:
	const std::string *variable;
public:
	ExpressionVariable(const std::string* _variable);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_ID() const override;
};



class Value : public Identify {
private:
	const double *number;
public:
	Value(const double* _number);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_ID() const override;
};

class MultExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	MultExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class AssignEqExpr : public Expression {
private:
	const Expression* unaryexpr;
	// const Declaration* assignop;
	const Expression* assignexpr;
public:
	AssignEqExpr(const Expression* _unaryexpr, const Expression* _assignexpr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class AssignOpEqExpr : public Expression {
private:
	const Expression* unaryexpr;
	// const Declaration* assignop;
	const Expression* assignexpr;
	const std::string op;
public:
	AssignOpEqExpr(const Expression* _unaryexpr, const Expression* _assignexpr, const std::string _op);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};



class AddExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	AddExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class SubExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	SubExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

//Reduce this by inheriting lhs and rhs??
class ORExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	ORExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ANDExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	ANDExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class LessThanExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	LessThanExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class GreaterThanExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	GreaterThanExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class EqualityExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	EqualityExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};


class LonePostfixExpression : public Identify {
private:
	const Identify* expr;
public:
	LonePostfixExpression(const Identify* _expr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_ID() const override;
};

class PostfixArguExpression : public Identify {
private:
	const Identify* expr;
	const Expression* arguexpr;
public:
	PostfixArguExpression(const Identify* _expr, const Expression* _arguexpr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_ID() const override;
};


class PostArrayExpr : public Identify {
private:
	const Identify* expr;
	const Expression* arguexpr;
public:
	PostArrayExpr(const Identify* _expr, const Expression* _arguexpr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_ID() const override;
};




class AssignExprList : public Expression {
private:
	const Expression* exprlist;
	const Expression* expr;
public:
	AssignExprList(const Expression* _exprlist, const Expression* _expr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

// class UnaryOpExpr : public Identify {
// private:
// 	const Expression* op;
// 	const Expression* expr;
// public:
// 	UnaryOpExpr(const Expression* _op, const Expression* _expr);
// 	virtual void print_c(std::ostream &dst) const override;
// 	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
// 	virtual void print_mips(std::ostream &dst, context &program) const override;
// 	virtual std::string get_ID() const override;
// };


// class UnaryOp : public Expression {
// private:
// 	const std::string op;
// public:
// 	UnaryOp(const std::string _op);
// 	virtual void print_c(std::ostream &dst) const override;
// 	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
// 	virtual void print_mips(std::ostream &dst, context &program) const override;
// };


class UnaryCastExpr : public Identify {
private:
	const std::string op;
	const Identify* castexpr;
public:
	UnaryCastExpr(const std::string _op, const Identify* _castexpr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_ID() const override;
};




class ParenExpr : public Identify {
private:
	const Expression* expr;
public:
	ParenExpr(const Expression* _expr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_ID() const override;
};


class DivExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	DivExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ModExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	ModExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

//

class LshiftExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	LshiftExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};


class RshiftExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	RshiftExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class LTEQExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	LTEQExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class GTEQExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	GTEQExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class NEQExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	NEQExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class BANDExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	BANDExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ExclusiveORExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	ExclusiveORExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class InclusiveORExpression : public Expression {
private:
	const Expression* lhs;
	const Expression* rhs;
public:
	InclusiveORExpression(const Expression* _lhs, const Expression* _rhs);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};


class PostIncrementExpr : public Identify {
private:
	const Identify* postfixexpr;
public:
	PostIncrementExpr(const Identify* _postfixexpr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_ID() const override;
};

class PostDecrementExpr : public Identify {
private:
	const Identify* postfixexpr;
public:
	PostDecrementExpr(const Identify* _postfixexpr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_ID() const override;
};

class PreIncrementExpr : public Identify {
private:
	const Identify* Prefixexpr;
public:
	PreIncrementExpr(const Identify* _Prefixexpr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_ID() const override;
};


class PreDecrementExpr : public Identify {
private:
	const Identify* Prefixexpr;
public:
	PreDecrementExpr(const Identify* _Prefixexpr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_ID() const override;
};



#endif
