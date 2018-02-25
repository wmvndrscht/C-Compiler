#ifndef ast_statements_hpp
#define ast_statements_hpp


#include <string>
#include <iostream>


class ReturnStatement : public Node {
public:
	virtual void print(std::ostream &dst) const override{
		dst<< "return;";
		//std::cerr << "[EmptyCompoundStatement]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "return";
	}
};

class ReturnExprStatement : public Node {
private:
	const NodePtr retexprstat;
public:
	ReturnExprStatement(const NodePtr _retexprstat) : retexprstat(_retexprstat){}
	virtual void print(std::ostream &dst) const override{
		dst << "return ";
		retexprstat->print(dst);
		dst << ";";
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "return ";
		retexprstat->py_translate(dst);
	}
};

class CompoundStatement : public Node{
private:
	const NodePtr statlist;
	const NodePtr declist;
public:
	CompoundStatement(const NodePtr _statlist, const NodePtr _declist) : 
		statlist(_statlist), declist(_declist){}
	virtual void print(std::ostream &dst) const override{
		dst<< "{";
		if(statlist != NULL){
			dst << "\n";
			statlist->print(dst);
		}
		if(declist != NULL){
			dst << "\n";
			declist->print(dst);
		}
		dst<< "\n}";
		//std::cerr << "[EmptyCompoundStatement]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << ":\n";
		dst << "  ";
		if(statlist != NULL){
			statlist->py_translate(dst);
		}
		if(declist != NULL){
			declist->py_translate(dst);
		}
		dst << "\n";
	}
};

class StatementList : public Node{
private:
	const NodePtr statlist;
	const NodePtr stat;
public:
	StatementList(const NodePtr _statlist, const NodePtr _stat) : 
	statlist(_statlist), stat(_stat){}
	virtual void print(std::ostream &dst) const override{
		statlist->print(dst);
		dst << "\n";
		stat->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		statlist->py_translate(dst);
		dst << "\n";
		stat->py_translate(dst);
	}
};

class WhileStatement : public Node{
private:
	const NodePtr expr;
	const NodePtr stat;
public:
	WhileStatement(const NodePtr _expr, const NodePtr _stat) : 
		expr(_expr), stat(_stat){}
	virtual void print(std::ostream &dst) const override{
		dst << "while(";
		expr->print(dst);
		dst << ")";
		stat->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "while(";
		expr->py_translate(dst);
		dst << "):\n\t";
		stat->py_translate(dst);
	}
};


class IfStatement : public Node{
private:
	const NodePtr expr;
	const NodePtr stat;
public:
	IfStatement(const NodePtr _expr, const NodePtr _stat) : expr(_expr), stat(_stat){}
	virtual void print(std::ostream &dst) const override{
		dst << "if(";
		expr->print(dst);
		dst << ")";
		stat->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "if(";
		expr->py_translate(dst);
		dst << "):\n\t";
		stat->py_translate(dst);
	}
};

class IfElseStatement : public Node{
private:
	const NodePtr expr;
	const NodePtr ifstat;
	const NodePtr elsestat;
public:
	IfElseStatement(const NodePtr _expr, const NodePtr _ifstat, const NodePtr _elsestat) :
	  expr(_expr), ifstat(_ifstat), elsestat(_elsestat){}
	virtual void print(std::ostream &dst) const override{
		dst << "if(";
		expr->print(dst);
		dst << ")";
		ifstat->print(dst);
		dst << "\n else";
		elsestat->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "if(";
		expr->py_translate(dst);
		dst << "):\n\t";
		ifstat->py_translate(dst);
		dst << "else:\n\t";
		elsestat->py_translate(dst);
	}

};

class ExprStatement : public Node{
private:
	const NodePtr expr;
public:
	ExprStatement(const NodePtr _expr) : expr(_expr){}
	virtual void print(std::ostream &dst) const override{
		expr->print(dst);
		dst << ";";
	}
	virtual void py_translate(std::ostream &dst) const override{
		expr->print(dst);
	}
};

#endif