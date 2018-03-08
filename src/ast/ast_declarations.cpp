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

void DeclarationSpecifier::print_mips(std::ostream &dst, context& program) const {}

//-----------------------------------------------------------------------

VariableDeclarator::VariableDeclarator(const std::string &_variable) : variable(_variable){}

void VariableDeclarator::print_c(std::ostream &dst) const {
	dst << " " << variable;
}

void VariableDeclarator::py_translate(std::ostream &dst) const {
	dst << variable;
}
void VariableDeclarator::print_mips(std::ostream &dst, context& program) const {}

std::string VariableDeclarator::get_Label() const{
	return variable;
}


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
void LoneDeclaration::print_mips(std::ostream &dst, context& program) const {}

//-----------------------------------------------------------------------

TheDeclaration::TheDeclaration(const DeclarationSpecifier* _decspec,
	const Declaration* _initdeclaratorlist): decspec(_decspec), initdeclaratorlist(_initdeclaratorlist){}

void TheDeclaration::print_c(std::ostream &dst) const {
	decspec->print_c(dst);
	initdeclaratorlist->print_c(dst);
	dst << ";";
	//std::cerr << "[Declaration]" << std::endl;
}
void TheDeclaration::py_translate(std::ostream &dst) const {
	// decspec->py_translate(dst); don't believe I need this?
	// dst << " ";
	initdeclaratorlist->py_translate(dst);
	dst << "\n  ";
}

void TheDeclaration::print_mips(std::ostream &dst, context& program) const {}

//-----------------------------------------------------------------------

FunctionDefinition::FunctionDefinition(const DeclarationSpecifier* _decspec, const Declarator *_dec,
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

void FunctionDefinition::print_mips(std::ostream &dst, context& program) const {

	std::string label = dec->get_Label();

	//FrameSize will eventually be = tempvariables + local variables + 8 + paramarguments;
	//Find these or should I print mips and then gather the params?
	int FrameSize = 8;
	dst << label << ":\n";
	//Setup the frame on the stack for this function call


	//may create own instructions class to do the printing more clearly
	//Adjust stack for this function
	dst << "\t" << "addiu $sp,$sp,-" << FrameSize << "\n";
	//Store old frame pointer
	dst << "\t" << "sw $fp," << FrameSize-4 << "($sp)\n";
	//Set new frame pointer
	dst << "\t" << "move $fp,$sp\n";

	dst << "\n";
	//now do return expression, will include context later
	cstatement->print_mips(dst, program);
	dst << "\n";

	//restore frame and stack
	dst << "\t" << "move $sp,$fp\n";
	dst << "\t" << "lw $fp," << FrameSize-4 << "($sp)\n";
	dst << "\t" << "addiu $sp,$sp," << FrameSize << "\n";

	//finish function
	dst << "\t" << "j $31\n";
	dst << "\t" << "nop";

}

//-----------------------------------------------------------------------

EmptyDeclarator::EmptyDeclarator(const Declarator *_directdec) : directdec(_directdec){}

void EmptyDeclarator::print_c(std::ostream &dst) const {
	directdec->print_c(dst);
	dst << "()";
	//std::cerr << "[EmptyDeclarator]" << std::endl;
}

void EmptyDeclarator::py_translate(std::ostream &dst) const {
	directdec->py_translate(dst);
	dst << "()";
}

void EmptyDeclarator::print_mips(std::ostream &dst, context& program) const {}


std::string EmptyDeclarator::get_Label() const{
	return directdec->get_Label();
}

//-----------------------------------------------------------------------

InitDeclarator::InitDeclarator(const Declaration* _dec, const NodePtr _init) : dec(_dec), init(_init){}

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

void InitDeclarator::print_mips(std::ostream &dst, context& program) const {}

//-----------------------------------------------------------------------

LoneInitDeclarator::LoneInitDeclarator(const Declaration* _dec) : dec(_dec){}

void LoneInitDeclarator::print_c(std::ostream &dst) const {
	dec->print_c(dst);
}

void LoneInitDeclarator::py_translate(std::ostream &dst) const {
	dec->py_translate(dst);
	dst << "=0";
}

void LoneInitDeclarator::print_mips(std::ostream &dst, context& program) const {}
//-----------------------------------------------------------------------

DeclarationList::DeclarationList(const Declaration* _dec, const Declaration* _declist) : dec(_dec),
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

void DeclarationList::print_mips(std::ostream &dst, context& program) const {}

//-----------------------------------------------------------------------


ParamListDeclarator::ParamListDeclarator(const Declarator *_dec, const Declaration* _paramlist) : 
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

void ParamListDeclarator::print_mips(std::ostream &dst, context& program) const {}

std::string ParamListDeclarator::get_Label() const{
	return dec->get_Label();
}

//-----------------------------------------------------------------------

ParamDeclaration::ParamDeclaration(const Declaration* _decspec, const Declaration* _dec) :
	decspec(_decspec), dec(_dec){}

void ParamDeclaration::print_c(std::ostream &dst) const {
	decspec->print_c(dst);
	dec->print_c(dst);
}

void ParamDeclaration::py_translate(std::ostream &dst) const {
	dec->py_translate(dst);
}

void ParamDeclaration::print_mips(std::ostream &dst, context& program) const {}

//-----------------------------------------------------------------------

ParamList::ParamList(const Declaration* _paramlist, const Declaration* _param): 
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

void ParamList::print_mips(std::ostream &dst, context& program) const {}

//-----------------------------------------------------------------------

AssignmentOperator::AssignmentOperator(const std::string *_assignop) : assignop(_assignop){}

void AssignmentOperator::print_c(std::ostream &dst) const {
	dst << *assignop;
}

 void AssignmentOperator::py_translate(std::ostream &dst) const {
	dst << *assignop;
}

void AssignmentOperator::print_mips(std::ostream &dst, context& program) const {}

//-----------------------------------------------------------------------