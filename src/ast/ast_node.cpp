#include "../../include/ast/ast_node.hpp"




Node::~Node(){}

TranslationUnit::TranslationUnit(const NodePtr leftn,const NodePtr rightn) : left(leftn), right(rightn){}

TranslationUnit::~TranslationUnit(){ delete left; delete right;}
	
void TranslationUnit::print_c(std::ostream &dst) const{
	left->print_c(dst);
	dst<<"\n";
	right->print_c(dst);
}
void TranslationUnit::py_translate(std::ostream &dst, const scope &scp) const{
	left->py_translate(dst,scp);
	dst<<"\n";
	right->py_translate(dst,scp);
}

void TranslationUnit::print_mips(std::ostream &dst, context &program) const{}

//-------------------------------Declaration-----------------------------------

void Declaration::print_c(std::ostream &dst) const {}

void Declaration::py_translate(std::ostream &dst, const scope &scp) const{}

void Declaration::print_mips(std::ostream &dst, context &program) const{}

//------------------------------Statement---------------------------------

void Statement::print_c(std::ostream &dst) const {}

void Statement::py_translate(std::ostream &dst, const scope &scp) const{}

void Statement::print_mips(std::ostream &dst, context &program) const{}

//------------------------------Expression--------------------------------

void Expression::print_c(std::ostream &dst) const {}

void Expression::py_translate(std::ostream &dst, const scope &scp) const{}

void Expression::print_mips(std::ostream &dst, context &program) const{}

//------------------------------Assign-------------------------------


void Identify::print_c(std::ostream &dst) const {}

void Identify::py_translate(std::ostream &dst, const scope &scp) const{}

void Identify::print_mips(std::ostream &dst, context &program) const{}