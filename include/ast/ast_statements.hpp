#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <iostream>


class ReturnStatement : public Node {
public:
	virtual void print_c(std::ostream &dst) const override{
		dst<< "return;";
		//std::cerr << "[EmptyCompoundStatement]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		// for(int i =0; i<scopecount;i++){ dst << " ";};
		dst << "return";
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class ReturnExprStatement : public Node {
private:
	const NodePtr retexprstat;
public:
	ReturnExprStatement(const NodePtr _retexprstat) : retexprstat(_retexprstat){}
	virtual void print_c(std::ostream &dst) const override{
		dst << "return ";
		retexprstat->print_c(dst);
		dst << ";";
	}
	virtual void py_translate(std::ostream &dst) const override{
		// for(int i =0; i<scopecount;i++){ dst << " ";};
		dst << "return ";
		retexprstat->py_translate(dst);
	}
	virtual void print_mips(std::ostream &dst) const override{
		dst << "  move $2,$";
		retexprstat->print_mips(dst);//can use dest reg etc
	}
};

class CompoundStatement : public Node{
private:
	const NodePtr statlist;
	const NodePtr declist;
public:
	CompoundStatement(const NodePtr _statlist, const NodePtr _declist) : 
		statlist(_statlist), declist(_declist){}
	virtual void print_c(std::ostream &dst) const override{
		dst<< "{";
		if(statlist != NULL){
			dst << "\n";
			statlist->print_c(dst);
		}
		if(declist != NULL){
			dst << "\n";
			declist->print_c(dst);
		}
		dst<< "\n}";
		//std::cerr << "[EmptyCompoundStatement]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		if(!preif){ dst << ":";};
		dst << "\n";
		scopecount+=2;
		if(statlist != NULL){
			for(int i =0; i<scopecount;i++){ dst << " ";};
			statlist->py_translate(dst);
		}
		if(declist != NULL){
			dst << "\n";
			for(int i =0; i<scopecount;i++){ dst << " ";};
			declist->py_translate(dst);
		}
		scopecount-=2;
		dst << "\n";
	}
	virtual void print_mips(std::ostream &dst) const override{
		statlist->print_mips(dst);
	}
};

class StatementList : public Node{
private:
	const NodePtr statlist;
	const NodePtr stat;
public:
	StatementList(const NodePtr _statlist, const NodePtr _stat) : 
	statlist(_statlist), stat(_stat){}
	virtual void print_c(std::ostream &dst) const override{
		statlist->print_c(dst);
		dst << "\n  ";
		stat->print_c(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		statlist->py_translate(dst);
		dst << "\n";
		for(int i =0; i<scopecount;i++){ dst << " ";};
		stat->py_translate(dst);
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class WhileStatement : public Node{
private:
	const NodePtr expr;
	const NodePtr stat;
public:
	WhileStatement(const NodePtr _expr, const NodePtr _stat) : 
		expr(_expr), stat(_stat){}
	virtual void print_c(std::ostream &dst) const override{
		dst << "while(";
		expr->print_c(dst);
		dst << ")";
		stat->print_c(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "while(";
		expr->py_translate(dst);
		dst << "):\n";
		scopecount+=2;
		for(int i =0; i<scopecount;i++){ dst << " ";};
		stat->py_translate(dst);
		scopecount-=2;
	}
	virtual void print_mips(std::ostream &dst) const override{}
};


class IfStatement : public Node{
private:
	const NodePtr expr;
	const NodePtr stat;
public:
	IfStatement(const NodePtr _expr, const NodePtr _stat) : expr(_expr), stat(_stat){}
	virtual void print_c(std::ostream &dst) const override{
		dst << "if(";
		expr->print_c(dst);
		dst << ")";
		stat->print_c(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "if(";
		expr->py_translate(dst);
		dst << "):\n";
		preif = true;
		scopecount+=2;
		for(int i =0; i<scopecount;i++){ dst << " ";};
		stat->py_translate(dst);
		scopecount-=2;
		preif = false;
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class IfElseStatement : public Node{
private:
	const NodePtr expr;
	const NodePtr ifstat;
	const NodePtr elsestat;
public:
	IfElseStatement(const NodePtr _expr, const NodePtr _ifstat, const NodePtr _elsestat) :
	  expr(_expr), ifstat(_ifstat), elsestat(_elsestat){}
	virtual void print_c(std::ostream &dst) const override{
		dst << "if(";
		expr->print_c(dst);
		dst << ")";
		ifstat->print_c(dst);
		dst << "\n else";
		elsestat->print_c(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "if(";
		expr->py_translate(dst);
		dst << "):\n";
		scopecount+=2;
		preif = true;
		for(int i =0; i<scopecount;i++){ dst << " ";};
		ifstat->py_translate(dst);
		scopecount-=2;
		for(int i =0; i<scopecount;i++){ dst << " ";};
		dst << "else:\n\t";
		scopecount+=2;
		for(int i =0; i<scopecount;i++){ dst << " ";};
		elsestat->py_translate(dst);
		scopecount-=2;
		preif=false;
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class ExprStatement : public Node{
private:
	const NodePtr expr;
public:
	ExprStatement(const NodePtr _expr) : expr(_expr){}
	virtual void print_c(std::ostream &dst) const override{
		expr->print_c(dst);
		dst << ";";
	}
	virtual void py_translate(std::ostream &dst) const override{
		expr->print_c(dst);
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

#endif