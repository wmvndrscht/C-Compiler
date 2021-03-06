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

	for(int i =0; i<scp.count;i++){ dst << " ";};
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
	// 	dst << "\n  " << gbl.var[i];
	// }
	// dst << "\n";
	cstatement->py_translate(dst,increment(scp));
}

void FunctionDefinition::print_mips(std::ostream &dst, context& program) const {
	
	dst << "\t.text\n";
	dst << "\t.align 2\n";
	std::string label = dec->get_Label();
	//FrameSize will eventually be = tempvariables + local variables + 8 + paramarguments;
	//Find these or should I print mips and then gather the params?
	dst << "\t.global " << label << "\n";
	

  dst << "\t.set nomicromips\n";
  dst << "\t.set nomips16\n";
	dst << "\t.type " << label << ", @function\n";

	dst << label << ":\n";
	//Setup the frame on the stack for this function call


	//may create own instructions class to do the printing more clearly
	//Adjust stack for this function
	dst << "\t" << "addiu $sp,$sp,-" << program.getFrameSize() << "\n";
	//store return address incase of function call
	dst << "\tsw $31," << program.getFrameSize()-4 << "($sp)\n";
	//Store old frame pointer
	dst << "\t" << "sw $fp," << program.getFrameSize()-8 << "($sp)\n";
	//Set new frame pointer
	dst << "\t" << "move $fp,$sp\n";

	program.resetParamPass();
	program.incrScope();
	dec->print_mips(dst,program);
	program.decrScope();

	//aa
	program.resetParamPass();

	dst << "\n";
	//now do return expression, will include context later

	program.setdestReg(3);
	program.setnReg(3);


	cstatement->print_mips(dst, program);
	dst << "\n";

	//restore frame and stack
	dst << "\t" << "move $sp,$fp\n";
	dst << "\tlw $31," << program.getFrameSize() -4 << "($sp)\n";
	dst << "\t" << "lw $fp," << program.getFrameSize() -8 << "($sp)\n";
	dst << "\t" << "addiu $sp,$sp," <<  program.getFrameSize() << "\n";

	//finish function
	dst << "\t" << "j $31\n";
	dst << "\t" << "nop\n";
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


	//set destination register to 3
	program.setdestReg(3);
	program.setnReg(3);

	if(program.getScopeNum() == 0){

		//need to cover for if int a = 5*6*2+3; instead of int a =2;
		
		dst << "\t.globl " << name << "\n";
		dst << "\t.data\n";
		dst << "\t.align 2\n";
		dst << "\t.type a,@object\n";
		dst << "\t.size " << name << ",4\n";
		dst << name << ":\n";
		dst << "\t.word ";
		init->print_mips(dst,program);
		dst << "\n";
	}
	else if( program.isVarinScope(name) ){
		init->print_mips(dst,program); //this result will be stored in $3
		dst << "\tsw $3," << program.getFrameSize()- program.getVarOffset(name) << "($fp)\n";
	}
	else{
		init->print_mips(dst,program);
		program.incFrameSize();
		dst << "\n\taddiu $sp,$sp,-4\n";
		dst << "\tmove $fp,$sp\n";
		program.addVartoScope(name, program.getFrameSize() );
		//result of expression will be $3
		dst << "\tsw $3," << program.getFrameSize() - program.getVarOffset(name) << "($fp)\n";
	}
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
	// for(int i =0; i<scp.count;i++){ dst << " ";};
	dec->py_translate(dst,scp);
	dst << "=0";
}

void LoneInitDeclarator::print_mips(std::ostream &dst, context& program) const {

		// 	std::string name = dec->get_name();
	// //get value of array size
	// int size = std::stoi(( (Identify*)expr )->get_ID());
	// dst << "#size of array is " << size;

	// //   1    if global then

	// //   2    if local and previously defined

	// //   3    if local and first time declared
	// //make stack big enough
	// //store name at beginning of stack place
	// //add start of array onto the stack

	// //create space on the stack for the rest
	// for(int i=1; i < size; i++){
	// 	program.incFrameSize();
	// 	dst << "\n\taddiu $sp,$sp,-4\n";
	// 	dst << "\tmove $fp,$sp\n";
	// 	program.addVartoScope( name +std::to_string(i) , program.getFrameSize() );
	// }

	// dst << "\n";


	//----



	std::string name = dec->get_name();

	program.setdestReg(2);
	program.setnReg(2);

	//if global variable treat differently
	if(program.getScopeNum() == 0){
		// if( std::string(&(name.back())) == "0"){

		// 	//.comm	a,20,4
		// 	dst << "\t.comm " << name << ",100,4\n"; 
		// 	dec->print_mips(dst,program);
		// }
		// else{
		//assume has not been declared before as compiler emits probelms if so
		//as LoneInitDeclarator set global value to 0
		dst << "\t.globl " << name << "\n";
		dst << "\t.data\n";
		dst << "\t.align 2\n";
		dst << "\t.type a,@object\n";
		dst << "\t.size " << name << ",4\n";
		dst << name << ":\n";
		dst << "\t.word 0\n";
		// }

	}
	else{ //local variable so follow convention below
		program.incFrameSize();
		dst << "\n\taddiu $sp,$sp,-4\n";
		dst << "\tmove $fp,$sp\n";
		program.addVartoScope(name, program.getFrameSize() );
		dst << "\tsw $0," << program.getFrameSize() - program.getVarOffset(name) << "($fp)\n";
		dec->print_mips(dst,program);
	}

	
}

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


ParamListDeclarator::ParamListDeclarator(const Declaration* _dec, const Declaration* _paramlist) : 
	dec(_dec), paramlist(_paramlist) {}

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

void ParamListDeclarator::print_mips(std::ostream &dst, context& program) const {
	paramlist->print_mips(dst,program);
	// dec->print_mips(dst,program);
}

std::string ParamListDeclarator::get_Label() const{
	return dec->get_Label();
}

std::string ParamListDeclarator::get_name() const {
	return dec->get_name();
}

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

void ParamDeclaration::print_mips(std::ostream &dst, context& program) const {
	//inc ParamPass
	program.incrParamPass();
	int offset = program.getFrameSize() + 4*(program.get_ParamPass() - 1);
	int reg = program.get_ParamPass() + 3;
	dst << "\tsw $" << reg << "," << offset <<"($fp)\n";

	std::string name = dec->get_name();
	//need to account for out of scope
	program.addVartoScope(name, program.getFrameSize()-offset);

}

std::string ParamDeclaration::get_name() const {
	return dec->get_name();
}
std::string ParamDeclaration::get_Label() const {
	return dec->get_Label();
}

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

void ParamList::print_mips(std::ostream &dst, context& program) const {
	paramlist->print_mips(dst,program);
	param->print_mips(dst,program);
}

std::string ParamList::get_name() const {return "not implemented";}
std::string ParamList::get_Label() const {return "not implemented";}

//-----------------------------------------------------------------------------------

InitDeclaratorList::InitDeclaratorList(const Declaration *_declist, const Declaration *_dec) : declist(_declist),
	dec(_dec){}

void InitDeclaratorList::print_c(std::ostream &dst) const {
	declist->print_c(dst);
	dst << "\n";
	dec->print_c(dst);
}

 void InitDeclaratorList::py_translate(std::ostream &dst, const scope &scp) const {
	declist->py_translate(dst,scp);
	dst << "\n";
	for(int i =0; i<scp.count;i++){ dst << " ";};
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

//-------------------------------------------------------------------------------------------------


ArrayDeclarator::ArrayDeclarator(const Declaration *_dec, const Expression *_expr) : 
	dec(_dec), expr(_expr) {}

void ArrayDeclarator::print_c(std::ostream &dst) const {
	dec->print_c(dst);	
	dst << "[";
	expr->print_c(dst);
	dst << "]";
}

void ArrayDeclarator::py_translate(std::ostream &dst, const scope &scp) const {
	dec->py_translate(dst,scp);
	dst << "[";
	expr->py_translate(dst,scp);
	dst << "]";
}

void ArrayDeclarator::print_mips(std::ostream &dst, context& program) const {
	//takes in dec and expr

	//get name of array
	std::string name = dec->get_name();
	//get value of array size
	int size = std::stoi(( (Identify*)expr )->get_ID());
	dst << "#size of array is " << size;

	//   1    if global then

	//   2    if local and previously defined

	//   3    if local and first time declared
	//make stack big enough
	//store name at beginning of stack place
	//add start of array onto the stack

	//create space on the stack for the rest
	for(int i=1; i < size; i++){
		program.incFrameSize();
		dst << "\n\taddiu $sp,$sp,-4\n";
		dst << "\tmove $fp,$sp\n";
		program.addVartoScope( name +std::to_string(i) , program.getFrameSize() );
	}

	dst << "\n";


	// dec->print_mips(dst,program);
}

std::string ArrayDeclarator::get_Label() const{
	return (dec->get_Label()+"0");
}

std::string ArrayDeclarator::get_name() const {
	return (dec->get_name()+"0");
}




//-------------------------------------------------------------------------------------------------


TwoDArrayDeclarator::TwoDArrayDeclarator(const Declaration *_dec, const Expression *_expr, const Expression *_expr1) : 
	dec(_dec), expr(_expr), expr1(_expr1) {}

void TwoDArrayDeclarator::print_c(std::ostream &dst) const {
	dec->print_c(dst);	
	dst << "[";
	expr->print_c(dst);
	dst << "][";
	expr1->print_c(dst);
	dst << "]";
}

void TwoDArrayDeclarator::py_translate(std::ostream &dst, const scope &scp) const {
	dec->py_translate(dst,scp);
	dst << "[";
	expr->py_translate(dst,scp);
	dst << "]";
}

void TwoDArrayDeclarator::print_mips(std::ostream &dst, context& program) const {
	//takes in dec and expr

	//get name of array
	std::string name = dec->get_name();
	//get value of array size
	int sizj = std::stoi(( (Identify*)expr )->get_ID());
	int sizi = std::stoi(( (Identify*)expr1 )->get_ID());
	dst << "#size of array is " << sizj*sizi;

	//   1    if global then

	//   2    if local and previously defined

	//   3    if local and first time declared
	//make stack big enough
	//store name at beginning of stack place
	//add start of array onto the stack

	//create space on the stack for the rest
	for(int j=0; j < sizj; j++){
		for(int i=0; i < sizi; i++){
			program.incFrameSize();
			dst << "\n\taddiu $sp,$sp,-4\n";
			dst << "\tmove $fp,$sp\n";
			program.addVartoScope( name +std::to_string(j)+std::to_string(i) , program.getFrameSize() );
		}
	}

	dst << "\n";


	// dec->print_mips(dst,program);
}

std::string TwoDArrayDeclarator::get_Label() const{
	return (dec->get_Label()+"0");
}

std::string TwoDArrayDeclarator::get_name() const {
	return (dec->get_name()+"0");
}