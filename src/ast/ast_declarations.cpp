#include "../../include/ast/ast_declarations.hpp"


//----------------------------------------------------------------------

DeclarationSpecifier::DeclarationSpecifier(const std::string &_type, 
		const DeclarationSpecifier* _decspec) : type(_type), decspec(_decspec){}
	
void DeclarationSpecifier::print_c(std::ostream &dst) const {
	dst << type;
	if(decspec != NULL){
		dst << " ";
		decspec->print_c(dst);
	}
}


void DeclarationSpecifier::py_translate(std::ostream &dst) const {
	dst << type;
	if( decspec != NULL){
		dst << "\n **>1 Declaration Specifier not in spec for formative** \n";
	}
}

void DeclarationSpecifier::print_mips(std::ostream &dst) const {}

//-----------------------------------------------------------------------

VariableDeclarator::VariableDeclarator(const std::string &_variable) : variable(_variable){}

void VariableDeclarator::print_c(std::ostream &dst) const {
	dst << " " << variable;
}

void VariableDeclarator::py_translate(std::ostream &dst) const {
	dst << variable;
}
void VariableDeclarator::print_mips(std::ostream &dst) const {}

//-----------------------------------------------------------------------

LoneDeclaration::LoneDeclaration(const DeclarationSpecifier* _decspec) : decspec(_decspec){}

void LoneDeclaration::print_c(std::ostream &dst) const {
	decspec->print_c(dst);
	dst << ";";
	//std::cerr << "[LoneDeclaration]" << std::endl;
}
void LoneDeclaration::py_translate(std::ostream &dst) const {
	dst << "\n **Lone Declarationnot in py spec**\n";
}
void LoneDeclaration::print_mips(std::ostream &dst) const {}

//-----------------------------------------------------------------------

Declaration::Declaration(const DeclarationSpecifier* _decspec,
	const NodePtr _initdeclaratorlist): decspec(_decspec), initdeclaratorlist(_initdeclaratorlist){}

void Declaration::print_c(std::ostream &dst) const {
	decspec->print_c(dst);
	initdeclaratorlist->print_c(dst);
	dst << ";";
	//std::cerr << "[Declaration]" << std::endl;
}
void Declaration::py_translate(std::ostream &dst) const {
	// decspec->py_translate(dst); don't believe I need this?
	// dst << " ";
	initdeclaratorlist->py_translate(dst);
	dst << "\n  ";
}

void Declaration::print_mips(std::ostream &dst) const {}

//-----------------------------------------------------------------------

FunctionDefinition::FunctionDefinition(const DeclarationSpecifier* _decspec, const NodePtr _dec,
	const CompoundStatement* _cstatement) :  decspec(_decspec), dec(_dec), cstatement(_cstatement){}

void FunctionDefinition::print_c(std::ostream &dst) const {
	decspec->print_c(dst);
	dec->print_c(dst);
	cstatement->print_c(dst);
	//std::cerr << "[FunctionDefinition]" << std::endl;
}

void FunctionDefinition::py_translate(std::ostream &dst) const {
	dst << "def ";
	dec->py_translate(dst);
	cstatement->py_translate(dst);
}

void FunctionDefinition::print_mips(std::ostream &dst) const {
	dst << "f:\n";
	//Setup the frame on the stack for this function call
	dst << "  addiu $sp,$sp,-8\n"; //start with no params
	dst << "  sw $fp,4($sp)\n";
	dst << "  move $fp,$sp\n";

	//now do return expression, will include context later
	cstatement->print_mips(dst);
	dst << "\n";

	//restore frame and stack
	dst << "  move $sp,$fp\n";
	dst << "  lw $fp,4($sp)\n";
	dst << "  addiu $sp,$sp,8\n";

	//finish function
	dst << "  j $31\n";
	dst << "  nop";

}

//-----------------------------------------------------------------------

EmptyDeclarator::EmptyDeclarator(const NodePtr _directdec) : directdec(_directdec){}

void EmptyDeclarator::print_c(std::ostream &dst) const {
	directdec->print_c(dst);
	dst << "()";
	//std::cerr << "[EmptyDeclarator]" << std::endl;
}

void EmptyDeclarator::py_translate(std::ostream &dst) const {
	directdec->py_translate(dst);
	dst << "()";
}

void EmptyDeclarator::print_mips(std::ostream &dst) const {}

//-----------------------------------------------------------------------

InitDeclarator::InitDeclarator(const NodePtr _dec, const NodePtr _init) : dec(_dec), init(_init){}

void InitDeclarator::print_c(std::ostream &dst) const {
	dec->print_c(dst);
	dst << " = ";
	init->print_c(dst);
}

void InitDeclarator::py_translate(std::ostream &dst) const {
	dec->py_translate(dst);
	dst << "=";
	init->py_translate(dst);
}

void InitDeclarator::print_mips(std::ostream &dst) const {}

//-----------------------------------------------------------------------

LoneInitDeclarator::LoneInitDeclarator(const NodePtr _dec) : dec(_dec){}

void LoneInitDeclarator::print_c(std::ostream &dst) const {
	dec->print_c(dst);
}

void LoneInitDeclarator::py_translate(std::ostream &dst) const {
	dec->py_translate(dst);
	dst << "=0";
}

void LoneInitDeclarator::print_mips(std::ostream &dst) const {}
//-----------------------------------------------------------------------

DeclarationList::DeclarationList(const NodePtr _dec, const NodePtr _declist) : dec(_dec),
	declist(_declist){}

void DeclarationList::print_c(std::ostream &dst) const {
	dec->print_c(dst);
	dst << "\n";
	declist->print_c(dst);
}

 void DeclarationList::py_translate(std::ostream &dst) const {
	dec->py_translate(dst);
	declist->py_translate(dst);
}

void DeclarationList::print_mips(std::ostream &dst) const {}

//-----------------------------------------------------------------------


ParamListDeclarator::ParamListDeclarator(const NodePtr _dec, const NodePtr _paramlist) : 
	dec(_dec), paramlist(_paramlist){}

void ParamListDeclarator::print_c(std::ostream &dst) const {
	dec->print_c(dst);
	dst << "(";
	paramlist->print_c(dst);
	dst << ")";
}

void ParamListDeclarator::py_translate(std::ostream &dst) const {
	dec->py_translate(dst);
	dst << "(";
	paramlist->py_translate(dst);
	dst << ")";
}

void ParamListDeclarator::print_mips(std::ostream &dst) const {}

//-----------------------------------------------------------------------

ParamDeclaration::ParamDeclaration(const NodePtr _decspec, const NodePtr _dec) :
	decspec(_decspec), dec(_dec){}

void ParamDeclaration::print_c(std::ostream &dst) const {
	decspec->print_c(dst);
	dec->print_c(dst);
}

void ParamDeclaration::py_translate(std::ostream &dst) const {
	dec->py_translate(dst);
}

void ParamDeclaration::print_mips(std::ostream &dst) const {}

//-----------------------------------------------------------------------

ParamList::ParamList(const NodePtr _paramlist, const NodePtr _param): 
	paramlist(_paramlist), param(_param){}

void ParamList::print_c(std::ostream &dst) const {
	paramlist->print_c(dst);
	dst << ",";
	param->print_c(dst);
}

void ParamList::py_translate(std::ostream &dst) const {
	paramlist->py_translate(dst);
	dst << ",";
	param->py_translate(dst);
}

void ParamList::print_mips(std::ostream &dst) const {}

//-----------------------------------------------------------------------

AssignmentOperator::AssignmentOperator(const std::string *_assignop) : assignop(_assignop){}

void AssignmentOperator::print_c(std::ostream &dst) const {
	dst << *assignop;
}

 void AssignmentOperator::py_translate(std::ostream &dst) const {
	dst << *assignop;
}

void AssignmentOperator::print_mips(std::ostream &dst) const {}

//-----------------------------------------------------------------------