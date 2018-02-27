#ifndef ast_expressions_hpp
#define ast_expressions_hpp

class ExpressionVariable : public Node {
private:
	const std::string *variable;
public:
	ExpressionVariable(const std::string* _variable) : variable(_variable){}
	virtual void print(std::ostream &dst) const override{
		dst << *variable;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << *variable;
	}
};

class Value : public Node {
private:
	const double *number;
public:
	Value(const double* _number) : number(_number){}
	virtual void print(std::ostream &dst) const override{
		dst << *number;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << *number;
	}
};

class MultExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	MultExpression(const NodePtr _lhs, const NodePtr _rhs) : lhs(_lhs),rhs(_rhs){}
	virtual void print(std::ostream &dst) const override{
		std::cerr << "multexpr";
		lhs->print(dst);
		dst << "*";
		rhs->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		lhs->py_translate(dst);
		dst << "*";
		rhs->py_translate(dst);
	}

};

class AssignExpr : public Node {
private:
	const NodePtr unaryexpr;
	const NodePtr assignop;
	const NodePtr assignexpr;
public:
	AssignExpr(const NodePtr _unaryexpr, const NodePtr _assignop,
	  const NodePtr _assignexpr) : unaryexpr(_unaryexpr), assignop(_assignop),
		assignexpr(_assignexpr){}
	virtual void print(std::ostream &dst) const override{
		std::cerr << "assignexpr";
		unaryexpr->print(dst);
		dst << " ";
		assignop->print(dst);
		dst << " ";
		assignexpr->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		unaryexpr->py_translate(dst);
		dst << "";
		assignop->py_translate(dst);
		dst << " ";
		assignexpr->py_translate(dst);
	}

};


class AddExpression : public Node{
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	AddExpression(const NodePtr _lhs, const NodePtr _rhs) : lhs(_lhs),rhs(_rhs){}
	virtual void print(std::ostream &dst) const override{
		std::cerr << "addexpr";
		lhs->print(dst);
		dst << "+";
		rhs->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		lhs->py_translate(dst);
		dst << "+";
		rhs->py_translate(dst);
	}
	
};

class SubExpression : public Node{
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	SubExpression(const NodePtr _lhs, const NodePtr _rhs) : lhs(_lhs),rhs(_rhs){}
	virtual void print(std::ostream &dst) const override{
		std::cerr << "subexpr";
		lhs->print(dst);
		dst << "-";
		rhs->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		lhs->py_translate(dst);
		dst << "-";
		rhs->py_translate(dst);
	}

};

//Reduce this by inheriting lhs and rhs??
class ORExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	ORExpression(const NodePtr _lhs, const NodePtr _rhs) : lhs(_lhs),rhs(_rhs){}
	virtual void print(std::ostream &dst) const override{
		lhs->print(dst);
		dst << "||";
		rhs->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		lhs->py_translate(dst);
		dst << " or ";
		rhs->py_translate(dst);
	}
};

class ANDExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	ANDExpression(const NodePtr _lhs, const NodePtr _rhs) : lhs(_lhs),rhs(_rhs){}
	virtual void print(std::ostream &dst) const override{
		lhs->print(dst);
		dst << "&&";
		rhs->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		lhs->py_translate(dst);
		dst << " and ";
		rhs->py_translate(dst);
	}
};

class LessThanExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	LessThanExpression(const NodePtr _lhs, const NodePtr _rhs) : lhs(_lhs),rhs(_rhs){}
	virtual void print(std::ostream &dst) const override{
		lhs->print(dst);
		dst << "<";
		rhs->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		lhs->py_translate(dst);
		dst << "<";
		rhs->py_translate(dst);
	}
};

class GreaterThanExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	GreaterThanExpression(const NodePtr _lhs, const NodePtr _rhs) : lhs(_lhs),rhs(_rhs){}
	virtual void print(std::ostream &dst) const override{
		lhs->print(dst);
		dst << ">";
		rhs->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		lhs->py_translate(dst);
		dst << ">";
		rhs->py_translate(dst);
	}
};

class EqualityExpression : public Node {
private:
	const NodePtr lhs;
	const NodePtr rhs;
public:
	EqualityExpression(const NodePtr _lhs, const NodePtr _rhs) : lhs(_lhs),rhs(_rhs){}
	virtual void print(std::ostream &dst) const override{
		lhs->print(dst);
		dst << "==";
		rhs->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		lhs->py_translate(dst);
		dst << "==";
		rhs->py_translate(dst);
	}
};


class LonePostfixExpression : public Node{
private:
	const NodePtr expr;
public:
	LonePostfixExpression(const NodePtr _expr) : expr(_expr){}
	virtual void print(std::ostream &dst) const override{
		expr->print(dst);
		dst << "()";
	}
	virtual void py_translate(std::ostream &dst) const override{
		expr->py_translate(dst);
		dst << "()";
	}
};

class PostfixArguExpression : public Node{
private:
	const NodePtr expr;
	const NodePtr arguexpr;
public:
	PostfixArguExpression(const NodePtr _expr, const NodePtr _arguexpr):
		expr(_expr), arguexpr(_arguexpr){}
	virtual void print(std::ostream &dst) const override{
		expr->print(dst);
		dst << "(";
		arguexpr->print(dst);
		dst << ")";
	}
	virtual void py_translate(std::ostream &dst) const override{
		expr->py_translate(dst);
		dst << "(";
		arguexpr->py_translate(dst);
		dst << ")";
	}
};

class AssignExprList : public Node{
private:
	const NodePtr exprlist;
	const NodePtr expr;
public:
	AssignExprList(const NodePtr _exprlist, const NodePtr _expr):
		exprlist(_exprlist), expr(_expr){}
	virtual void print(std::ostream &dst) const override{
		exprlist->print(dst);
		dst << ",";
		expr->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		exprlist->py_translate(dst);
		dst << ",";
		expr->py_translate(dst);
	}
};

class UnaryOpExpr : public Node{
private:
	const std::string *op;
	const NodePtr expr;
public:
	UnaryOpExpr(const std::string *_op, const NodePtr _expr) : op(_op),expr(_expr){}
	virtual void print(std::ostream &dst) const override{
		dst << *op;
		expr->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << *op;
		expr->py_translate(dst);
	}
};

#endif