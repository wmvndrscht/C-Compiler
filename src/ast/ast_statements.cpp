#include "../../include/ast/ast_statements.hpp"



//----------------------------------------------------------------------

void ReturnStatement::print_c(std::ostream &dst) const {
	dst<< "return;";
	//std::cerr << "[EmptyCompoundStatement]" << std::endl;
}
void ReturnStatement::py_translate(std::ostream &dst) const {
	// for(int i =0; i<scopecount;i++){ dst << " ";};
	dst << "return";
}
void ReturnStatement::print_mips(std::ostream &dst, context &program) const {}

//----------------------------------------------------------------------

ReturnExprStatement::ReturnExprStatement(const NodePtr _retexprstat) : retexprstat(_retexprstat){}
void ReturnExprStatement::print_c(std::ostream &dst) const {
	dst << "return ";
	retexprstat->print_c(dst);
	dst << ";";
}
void ReturnExprStatement::py_translate(std::ostream &dst) const {
	// for(int i =0; i<scopecount;i++){ dst << " ";};
	dst << "return ";
	retexprstat->py_translate(dst);
}
void ReturnExprStatement::print_mips(std::ostream &dst, context &program) const {
	dst << "\tmove $2,$";
	retexprstat->print_mips(dst,program);//can use dest reg etc
	dst << "\n";
}


//----------------------------------------------------------------------

CompoundStatement::CompoundStatement(const Statement* _statlist, const Declaration* _declist) : 
	statlist(_statlist), declist(_declist){}

void CompoundStatement::print_c(std::ostream &dst) const {
	dst<< "{";
	if(declist != NULL){
		dst << "\n";
		declist->print_c(dst);
	}
	if(statlist != NULL){
		dst << "\n";
		statlist->print_c(dst);
	}
	dst<< "\n}";
	//std::cerr << "[EmptyCompoundStatement]" << std::endl;
}

void CompoundStatement::py_translate(std::ostream &dst) const {
	if(!preif){ dst << ":";};
	dst << "\n";
	scopecount+=2;
	if(declist != NULL){
		dst << "\n";
		for(int i =0; i<scopecount;i++){ dst << " ";};
		declist->py_translate(dst);
	}
	if(statlist != NULL){
		for(int i =0; i<scopecount;i++){ dst << " ";};
		statlist->py_translate(dst);
	}
	scopecount-=2;
	dst << "\n";
}

void CompoundStatement::print_mips(std::ostream &dst, context &program) const {
	statlist->print_mips(dst,program);
}

//----------------------------------------------------------------------

StatementList::StatementList(const Statement* _statlist, const Statement* _stat) : 
statlist(_statlist), stat(_stat){}

void StatementList::print_c(std::ostream &dst) const {
	statlist->print_c(dst);
	dst << "\n  ";
	stat->print_c(dst);
}
void StatementList::py_translate(std::ostream &dst) const {
	statlist->py_translate(dst);
	dst << "\n";
	for(int i =0; i<scopecount;i++){ dst << " ";};
	stat->py_translate(dst);
}
void StatementList::print_mips(std::ostream &dst, context &program) const {}

//----------------------------------------------------------------------

WhileStatement::WhileStatement(const NodePtr _expr, const Statement* _stat) : 
	expr(_expr), stat(_stat){}

void WhileStatement::print_c(std::ostream &dst) const {
	dst << "while(";
	expr->print_c(dst);
	dst << ")";
	stat->print_c(dst);
}

void WhileStatement::py_translate(std::ostream &dst) const {
	dst << "while(";
	expr->py_translate(dst);
	dst << "):\n";
	scopecount+=2;
	for(int i =0; i<scopecount;i++){ dst << " ";};
	stat->py_translate(dst);
	scopecount-=2;
}

void WhileStatement::print_mips(std::ostream &dst, context &program) const {}

//----------------------------------------------------------------------

IfStatement::IfStatement(const NodePtr _expr, const Statement* _stat) : expr(_expr), stat(_stat){}

void IfStatement::print_c(std::ostream &dst) const {
	dst << "if(";
	expr->print_c(dst);
	dst << ")";
	stat->print_c(dst);
}

void IfStatement::py_translate(std::ostream &dst) const {
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

void IfStatement::print_mips(std::ostream &dst, context &program) const {}

//----------------------------------------------------------------------

IfElseStatement::IfElseStatement(const NodePtr _expr, const Statement* _ifstat, 
	const Statement* _elsestat) :
  expr(_expr), ifstat(_ifstat), elsestat(_elsestat){}

void IfElseStatement::print_c(std::ostream &dst) const {
	dst << "if(";
	expr->print_c(dst);
	dst << ")";
	ifstat->print_c(dst);
	dst << "\n else";
	elsestat->print_c(dst);
}

void IfElseStatement::py_translate(std::ostream &dst) const {
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

void IfElseStatement::print_mips(std::ostream &dst, context &program) const {}

//----------------------------------------------------------------------

ExprStatement::ExprStatement(const NodePtr _expr) : expr(_expr){}

void ExprStatement::print_c(std::ostream &dst) const {
	expr->print_c(dst);
	dst << ";";
}

void ExprStatement::py_translate(std::ostream &dst) const {
	expr->print_c(dst);
}

void ExprStatement::print_mips(std::ostream &dst, context &program) const {}

//----------------------------------------------------------------------