#include "../../include/ast/ast_node.hpp"


Node::~Node(){}

TranslationUnit::TranslationUnit(const NodePtr leftn,const NodePtr rightn) : left(leftn), right(rightn){}

TranslationUnit::~TranslationUnit(){ delete left; delete right;}
	
void TranslationUnit::print_c(std::ostream &dst) const{
	left->print_c(dst);
	dst<<"\n";
	right->print_c(dst);
}
void TranslationUnit::py_translate(std::ostream &dst) const{
	left->py_translate(dst);
	dst<<"\n";
	right->py_translate(dst);
}

void TranslationUnit::print_mips(std::ostream &dst, context &program) const{

}
