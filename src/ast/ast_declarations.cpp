#include "../../include/ast/ast_declarations.hpp"



#include <vector>

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

void DeclarationSpecifier::py_translate(std::ostream &dst, const scope &scp) const {
	dst << type;
	if( decspec != NULL){
		dst << "\n **>1 Declaration Specifier not in spec for formative** \n";
	}
}

void DeclarationSpecifier::print_mips(std::ostream &dst, context& program) const {}
std::string DeclarationSpecifier::get_name() const {return "not implemented";}
std::string DeclarationSpecifier::get_Label() const {return "not implemented";}

//-----------------------------------------------------------------------

VariableDeclarator::VariableDeclarator(const std::string &_variable) : variable(_variable){}

void VariableDeclarator::print_c(std::ostream &dst) const {
	dst << " " << variable;
}

void VariableDeclarator::py_translate(std::ostream &dst, const scope &scp) const {
	dst << variable;
}
void VariableDeclarator::print_mips(std::ostream &dst, context& program) const {
	int dReg = program.getnReg();
	program.assignReg();
	dst << "\tlw $" << dReg <<",$" << program.getnReg() << "\n";
	program.freeReg();
}

std::string VariableDeclarator::get_Label() const{
	return variable;
}
std::string VariableDeclarator::get_name() const {
	return variable;
}



//-----------------------------------------------------------------------

LoneDeclaration::LoneDeclaration(const DeclarationSpecifier* _decspec) : decspec(_decspec){}

void LoneDeclaration::print_c(std::ostream &dst) const {
	decspec->print_c(dst);
	dst << ";";
	//std::cerr << "[LoneDeclaration]" << std::endl;
}
void LoneDeclaration::py_translate(std::ostream &dst, const scope &scp) const {
	dst << "\n **Lone Declarationnot in py spec**\n";
}
void LoneDeclaration::print_mips(std::ostream &dst, context& program) const {}

std::string LoneDeclaration::get_name() const {return "not implemented";}
std::string LoneDeclaration::get_Label() const {return "not implemented";}

//-----------------------------------------------------------------------

TheDeclaration::TheDeclaration(const DeclarationSpecifier* _decspec,
	const Declaration* _initdeclaratorlist): decspec(_decspec), initdeclaratorlist(_initdeclaratorlist){}

void TheDeclaration::print_c(std::ostream &dst) const {
	decspec->print_c(dst);
	initdeclaratorlist->print_c(dst);
	dst << ";";
	//std::cerr << "[Declaration]" << std::endl;
}
void TheDeclaration::py_translate(std::ostream &dst, const scope &scp) const {
	// decspec->py_translate(dst,scp); don't believe I need this?
	// dst << " ";

	if(scp.count == 0){
		std::string name = initdeclaratorlist->get_name();
		gbl.var.push_back( name );
	}
	initdeclaratorlist->py_translate(dst,scp);
	dst << "\n";
}

void TheDeclaration::print_mips(std::ostream &dst, context& program) const {
	//The Declaration-> decspec & init_declarator_list (init_declarator)

	initdeclaratorlist->print_mips(dst,program);

	//get the Name
	// std::string name = initdeclaratorlist->get_name();
	// int value = initdeclaratorlist->get_Value


	// program.assignVar()
	// //Check if already on stack
	// 	//if on stack update value
	// 		//load value of expression
	// 		//move expression into register
	// 		//store register into mem at offset

	// 	//else increment frame size
	// 	//varibale offset = frame size
	// 	//load value of expression
	// 	//move expression into mem at offset
	// 	//push onto map with name and offset
	// 	//adjust frame pointer and stack pointer 9f


}
std::string TheDeclaration::get_name() const {return "not implemented";}
std::string TheDeclaration::get_Label() const {return "not implemented";}

//-----------------------------------------------------------------------

FunctionDefinition::FunctionDefinition(const DeclarationSpecifier* _decspec, const Declaration *_dec,
	const Statement* _cstatement) :  decspec(_decspec), dec(_dec), cstatement(_cstatement){}

void FunctionDefinition::print_c(std::ostream &dst) const {
	decspec->print_c(dst);
	dec->print_c(dst);
	cstatement->print_c(dst);
	//std::cerr << "[FunctionDefinition]" << std::endl;
}

void FunctionDefinition::py_translate(std::ostream &dst, const scope &scp) const {
	dst << "def ";
	dec->py_translate(dst,scp);
	// for(int i=1;i<gbl.var.size();i++){
	// 	dst << "\n\t" << gbl.var[i];
	// }
	cstatement->py_translate(dst,increment(scp));
}

void FunctionDefinition::print_mips(std::ostream &dst, context& program) const {

	std::string label = dec->get_Label();

	//FrameSize will eventually be = tempvariables + local variables + 8 + paramarguments;
	//Find these or should I print mips and then gather the params?
	int FrameSize = 8;
	dst << "\t.global " << label << "\n";
	dst << "\t.align 2\n";

	// .set	nomips16
 //    .set	nomicromips
 //    .ent	f
 //    .type	f, @function
	// dst << ""
	dst << "\t.type " << label << ", @function\n";

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
	dst << "\t" << "lw $fp," << program.getFrameSize() -4 << "($sp)\n";
	dst << "\t" << "addiu $sp,$sp," <<  program.getFrameSize() << "\n";

	//finish function
	dst << "\t" << "j $31\n";
	dst << "\t" << "nop";

}

std::string FunctionDefinition::get_name() const {return "not implemented";}
std::string FunctionDefinition::get_Label() const {return "not implemented";}

//-----------------------------------------------------------------------

EmptyDeclarator::EmptyDeclarator(const Declaration *_directdec) : directdec(_directdec){}

void EmptyDeclarator::print_c(std::ostream &dst) const {
	directdec->print_c(dst);
	dst << "()";
	//std::cerr << "[EmptyDeclarator]" << std::endl;
}

void EmptyDeclarator::py_translate(std::ostream &dst, const scope &scp) const {
	directdec->py_translate(dst,scp);
	dst << "()";
}

void EmptyDeclarator::print_mips(std::ostream &dst, context& program) const {}


std::string EmptyDeclarator::get_Label() const{
	return directdec->get_Label();
}

std::string EmptyDeclarator::get_name() const {return "not implemented";}

//-----------------------------------------------------------------------

InitDeclarator::InitDeclarator(const Declaration* _dec, const NodePtr _init) : dec(_dec), init(_init){}

void InitDeclarator::print_c(std::ostream &dst) const {
	dec->print_c(dst);
	dst << " = ";
	init->print_c(dst);
}

void InitDeclarator::py_translate(std::ostream &dst, const scope &scp) const {
	dec->py_translate(dst,scp);
	dst << "=";
	init->py_translate(dst,scp);
}

void InitDeclarator::print_mips(std::ostream &dst, context& program) const {
	//get the Name
	std::string name = dec->get_name();

	program.setdestReg(2);
	program.setnReg(2);

	init->print_mips(dst,program);


	if( program.checkVar(name) ){
		dst << "\tlw $3," << program.getFrameSize()- program.getlocalOffset(name) << "($fp)\n";
		dst << "\tmove $3,$2 \n";
		dst << "\tsw $3," << program.getFrameSize()- program.getlocalOffset(name) << "($fp)\n";
	}
	else{
		program.incFrameSize();
		dst << "\taddiu $sp,$sp,-4\n";
		dst << "\tmove $fp,$sp\n";
		program.addlocal(name, program.getFrameSize() );
		dst << "\n#local var:" << name <<" at offset " << program.getFrameSize() << "\n";
		dst << "\tsw $2," << program.getFrameSize() - program.getlocalOffset(name) << "($fp)\n";
		dst << "\n#offset adjusted = " << program.getFrameSize() - program.getlocalOffset(name) << "\n";
	}

// lw	$3,0($fp)

	// program.assignVar()
	// //Check if already on stack
	// 	//if on stack update value
	// 		//load value of expression
	// 		//move expression into register
	// 		//store register into mem at offset

	// 	//else increment frame size
	// 	//varibale offset = frame size
	// 	//load value of expression
	// 	//move expression into mem at offset
	// 	//push onto map with name and offset
	// 	//adjust frame pointer and stack pointer 9f
}

std::string InitDeclarator::get_name() const{
	return dec->get_Label();
}

std::string InitDeclarator::get_Label() const {return "not implemented";}



//-----------------------------------------------------------------------

LoneInitDeclarator::LoneInitDeclarator(const Declaration* _dec) : dec(_dec){}

void LoneInitDeclarator::print_c(std::ostream &dst) const {
	dec->print_c(dst);
}

void LoneInitDeclarator::py_translate(std::ostream &dst, const scope &scp) const {
	dec->py_translate(dst,scp);
	dst << "=0";
}

void LoneInitDeclarator::print_mips(std::ostream &dst, context& program) const {}

std::string LoneInitDeclarator::get_name() const{
	return dec->get_Label();
}

std::string LoneInitDeclarator::get_Label() const {return "not implemented";}

//-----------------------------------------------------------------------

DeclarationList::DeclarationList(const Declaration* _declist, const Declaration* _dec) : declist(_declist),
	dec(_dec){}

void DeclarationList::print_c(std::ostream &dst) const {
	declist->print_c(dst);
	dst << "\n";
	dec->print_c(dst);
}

 void DeclarationList::py_translate(std::ostream &dst, const scope &scp) const {
	declist->py_translate(dst,scp);
	dec->py_translate(dst,scp);
}

void DeclarationList::print_mips(std::ostream &dst, context& program) const {
	declist->print_mips(dst,program);
	dec->print_mips(dst,program);
}

std::string DeclarationList::get_name() const {return "not implemented";}
std::string DeclarationList::get_Label() const {return "not implemented";}

//-----------------------------------------------------------------------


ParamListDeclarator::ParamListDeclarator(const Declaration *_dec, const Declaration* _paramlist) : 
	dec(_dec), paramlist(_paramlist){}

void ParamListDeclarator::print_c(std::ostream &dst) const {
	dec->print_c(dst);
	dst << "(";
	paramlist->print_c(dst);
	dst << ")";
}

void ParamListDeclarator::py_translate(std::ostream &dst, const scope &scp) const {
	dec->py_translate(dst,scp);
	dst << "(";
	paramlist->py_translate(dst,scp);
	dst << ")";
}

void ParamListDeclarator::print_mips(std::ostream &dst, context& program) const {}

std::string ParamListDeclarator::get_Label() const{
	return dec->get_Label();
}

std::string ParamListDeclarator::get_name() const {return "not implemented";}

//-----------------------------------------------------------------------

ParamDeclaration::ParamDeclaration(const Declaration* _decspec, const Declaration* _dec) :
	decspec(_decspec), dec(_dec){}

void ParamDeclaration::print_c(std::ostream &dst) const {
	decspec->print_c(dst);
	dec->print_c(dst);
}

void ParamDeclaration::py_translate(std::ostream &dst, const scope &scp) const {
	dec->py_translate(dst,scp);
}

void ParamDeclaration::print_mips(std::ostream &dst, context& program) const {}

std::string ParamDeclaration::get_name() const {return "not implemented";}
std::string ParamDeclaration::get_Label() const {return "not implemented";}

//-----------------------------------------------------------------------

ParamList::ParamList(const Declaration* _paramlist, const Declaration* _param): 
	paramlist(_paramlist), param(_param){}

void ParamList::print_c(std::ostream &dst) const {
	paramlist->print_c(dst);
	dst << ",";
	param->print_c(dst);
}

void ParamList::py_translate(std::ostream &dst, const scope &scp) const {
	paramlist->py_translate(dst,scp);
	dst << ",";
	param->py_translate(dst,scp);
}

void ParamList::print_mips(std::ostream &dst, context& program) const {}

std::string ParamList::get_name() const {return "not implemented";}
std::string ParamList::get_Label() const {return "not implemented";}

//-----------------------------------------------------------------------

AssignmentOperator::AssignmentOperator(const std::string *_assignop) : assignop(_assignop){}

void AssignmentOperator::print_c(std::ostream &dst) const {
	dst << *assignop;
}

 void AssignmentOperator::py_translate(std::ostream &dst, const scope &scp) const {
	dst << *assignop;
}

void AssignmentOperator::print_mips(std::ostream &dst, context& program) const {}

std::string AssignmentOperator::get_name() const {return "not implemented";}
std::string AssignmentOperator::get_Label() const {return "not implemented";}

//-----------------------------------------------------------------------

InitDeclaratorList::InitDeclaratorList(const Declaration *_declist, const Declaration *_dec) : declist(_declist),
	dec(_dec){}

void InitDeclaratorList::print_c(std::ostream &dst) const {
	declist->print_c(dst);
	dst << "\n";
	dec->print_c(dst);
}

 void InitDeclaratorList::py_translate(std::ostream &dst, const scope &scp) const {
	declist->py_translate(dst,scp);
	dec->py_translate(dst,scp);
}

void InitDeclaratorList::print_mips(std::ostream &dst, context& program) const {
	declist->print_mips(dst,program);
	dec->print_mips(dst,program);
}

std::string InitDeclaratorList::get_name() const{
	return dec->get_name();
}

std::string InitDeclaratorList::get_Label() const {return "not implemented";}