#include "../../include/ast/ast_expressions.hpp"

//-----------------------------------------------------------------------------

ExpressionVariable::ExpressionVariable(const std::string* _variable) : variable(_variable){}

void ExpressionVariable::print_c(std::ostream &dst) const {
	dst << *variable;
}

void ExpressionVariable::py_translate(std::ostream &dst, const scope &scp) const {
	dst << *variable;
}

void ExpressionVariable::print_mips(std::ostream &dst, context &program) const {
	// dst << *variable;

	if( program.isVarGlobal(*variable) ){
		dst << "\tlui $" << program.getnReg() << ",%hi(" << *variable << ")\n";
		dst << "\tlw $" << program.getnReg() << ",%lo(" << *variable << ")($" << program.getnReg() << ")\n";
	}
	else{
		dst << "\tlw $" << program.getnReg() << "," << program.getFrameSize() - program.getVarOffset(*variable) << "($fp)" << "\n";
	}
	// dst << "\t" << "lw $fp," << FrameSize-4 << "($sp)\n";
}

std::string ExpressionVariable::get_ID() const{
	return *variable;
}

//-----------------------------------------------------------------------------


Value::Value(const double* _number) : number(_number){}

void Value::print_c(std::ostream &dst) const {
	dst << *number;
}

void Value::py_translate(std::ostream &dst, const scope &scp) const {
	dst << *number;
}

void Value::print_mips(std::ostream &dst, context &program) const {
	if(program.getScopeNum() == 0){
		dst << *number;
	}
	else{
		dst << "\tli $" << program.getnReg() << "," << *number <<"\n";
	}
}

std::string Value::get_ID() const{
	return std::to_string(*number);
}


//-----------------------------------------------------------------------------


MultExpression::MultExpression(const Expression* _lhs, const Expression* _rhs) : lhs(_lhs),rhs(_rhs){}

void MultExpression::print_c(std::ostream &dst) const {
	dst << "(";
	lhs->print_c(dst);
	dst << ")*(";
	rhs->print_c(dst);
	dst << ")";
}

void MultExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "*";
	rhs->py_translate(dst,scp);
}

void MultExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();

	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tmultu $"  << dReg << ",$" << program.getnReg() << "\n";
	dst << "\tmflo $" << dReg << "\n";
	program.freeReg();
}


//-----------------------------------------------------------------------------


// AssignEqExpr::AssignEqExpr(const Expression* _unaryexpr, const Declaration* _assignop,
//  const Expression* _assignexpr) : unaryexpr(_unaryexpr), assignop(_assignop),
// 	assignexpr(_assignexpr){}

AssignEqExpr::AssignEqExpr(const Expression* _unaryexpr,const Expression* _assignexpr) :
 unaryexpr( _unaryexpr), assignexpr(_assignexpr){}

void AssignEqExpr::print_c(std::ostream &dst) const {
	unaryexpr->print_c(dst);
	dst << " = ";
	assignexpr->print_c(dst);
}

void AssignEqExpr::py_translate(std::ostream &dst, const scope &scp) const {
	unaryexpr->py_translate(dst,scp);
	dst << "= ";
	assignexpr->py_translate(dst,scp);
}

void AssignEqExpr::print_mips(std::ostream &dst, context &program) const {
	//load value into getnReg


	unaryexpr->print_mips(dst,program);
	int destReg = program.getnReg();
	Identify* a = (Identify*)unaryexpr;

	std::string name = a->get_ID();
	// std::string name = "a";
	//assume operator is "="
	//evaluate expression in next Register
	program.assignReg();
	//if variable is global
	assignexpr->print_mips(dst,program);
	if( program.isVarGlobal(name) ){
		dst << "\tlui $" << destReg << ",%hi(" << name << ")\n";
		dst << "\tsw $" << program.getnReg() << ",%lo(" << name << ")($" << destReg << ")\n";

	}
	else{
		
		dst << "\tmove $" << destReg << ",$" << program.getnReg() << "\n";
		dst << "\tsw $" << destReg << ","  << program.getFrameSize()- program.getVarOffset(name) << "($fp)\n";
	}
	program.freeReg();
}


//----------------------------------------------------------------------------

AssignOpEqExpr::AssignOpEqExpr(const Expression* _unaryexpr,const Expression* _assignexpr, const std::string _op) :
 unaryexpr( _unaryexpr), assignexpr(_assignexpr), op(_op){}

void AssignOpEqExpr::print_c(std::ostream &dst) const {
	unaryexpr->print_c(dst);
	dst << op;
	assignexpr->print_c(dst);
}

void AssignOpEqExpr::py_translate(std::ostream &dst, const scope &scp) const {
	unaryexpr->py_translate(dst,scp);
	dst << op;
	assignexpr->py_translate(dst,scp);
}

void AssignOpEqExpr::print_mips(std::ostream &dst, context &program) const {
	//load value into getnReg


	unaryexpr->print_mips(dst,program);
	int destReg = program.getnReg();
	Identify* a = (Identify*)unaryexpr;

	std::string name = a->get_ID();
	// std::string name = "a";
	//assume operator is "="
	//evaluate expression in next Register
	program.assignReg();
	//if variable is global
	assignexpr->print_mips(dst,program);
	if( program.isVarGlobal(name) ){
		dst << "\tlui $" << destReg << ",%hi(" << name << ")\n";
		// dst << "\tlw $" << program.getnReg() << ",%lo(" << *variable << ")($" << program.getnReg() << ")\n";
		dst << "\tlw $" << destReg << ",%lo(" << name << ")($" << destReg << ")\n";
		
		if(op == "+="){
			dst << "\taddu $" << program.getnReg() << ",$" << program.getnReg() << ",$" << destReg << "\n";
		}
		else if(op == "-="){
			dst << "\tsubu $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}
		else if(op == "*="){
			dst << "\tmultu $" << destReg << ",$" << program.getnReg() << "\n";
			dst << "\tmflo $" << program.getnReg() << "\n";
		}
		else if(op == "/="){
			dst << "\tdiv $" << destReg << ",$" << program.getnReg() << "\n";
			dst << "\tmflo $" << program.getnReg() << "\n";
		}
		else if(op == "%="){
			dst << "\tdiv $" << destReg << ",$" << program.getnReg() << "\n";
			dst << "\tmfhi $" << program.getnReg() << "\n";

		}
		else if(op == "<<="){
			dst << "\tsll $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}
		else if(op == ">>="){
			dst << "\tsra $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}
		else if(op == "&="){
			dst << "\tand $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}
		else if(op == "^="){
			dst << "\txor $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}
		else{
			dst << "\tor $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}


		dst << "\tlui $" << destReg << ",%hi(" << name << ")\n";
		dst << "\tsw $" << program.getnReg() << ",%lo(" << name << ")($" << destReg << ")\n";

	}
	else{

		dst << "\tlw $" << destReg << ","  << program.getFrameSize()- program.getVarOffset(name) << "($fp)\n";
		
		if(op == "+="){
			dst << "\taddu $" << program.getnReg() << ",$" << program.getnReg() << ",$" << destReg << "\n";
		}
		else if(op == "-="){
			dst << "\tsubu $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}
		else if(op == "*="){
			dst << "\tmultu $" << destReg << ",$" << program.getnReg() << "\n";
			dst << "\tmflo $" << program.getnReg() << "\n";
		}
		else if(op == "/="){
			dst << "\tdiv $" << destReg << ",$" << program.getnReg() << "\n";
			dst << "\tmflo $" << program.getnReg() << "\n";
		}
		else if(op == "%="){
			dst << "\tdiv $" << destReg << ",$" << program.getnReg() << "\n";
			dst << "\tmfhi $" << program.getnReg() << "\n";

		}
		else if(op == "<<="){
			dst << "\tsll $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}
		else if(op == ">>="){
			dst << "\tsra $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}
		else if(op == "&="){
			dst << "\tand $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}
		else if(op == "^="){
			dst << "\txor $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}
		else{
			dst << "\tor $" << program.getnReg() << ",$" << destReg << ",$" << program.getnReg() << "\n";
		}

		dst << "\tmove $" << destReg << ",$" << program.getnReg() << "\n";
		dst << "\tsw $" << destReg << ","  << program.getFrameSize()- program.getVarOffset(name) << "($fp)\n";
	}
	program.freeReg();
}

//-----------------------------------------------------------------------------

AddExpression::AddExpression(const Expression* _lhs, const Expression* _rhs) : lhs(_lhs),rhs(_rhs){}

void AddExpression::print_c(std::ostream &dst) const {
	dst << "(";
	lhs->print_c(dst);
	dst << ")+(";
	rhs->print_c(dst);
	dst << ")";
}

void AddExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "+";
	rhs->py_translate(dst,scp);
}

void AddExpression::print_mips(std::ostream &dst, context &program) const {
	//evaluate expression
	//pass value into destReg
	int dReg = program.getnReg();
	//Run lhs where value is stored into lReg
	lhs->print_mips(dst,program);
	//Adjust availReg for rhs
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\taddu $" << dReg << ",$" << dReg <<
		",$" << program.getnReg() << "\n";
	program.freeReg();

}

//-----------------------------------------------------------------------------


SubExpression::SubExpression(const Expression* _lhs, const Expression* _rhs) : lhs(_lhs),rhs(_rhs){}

void SubExpression::print_c(std::ostream &dst) const {
	dst << "(";
	lhs->print_c(dst);
	dst << ")-(";
	rhs->print_c(dst);
	dst << ")";
}

void SubExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "-";
	rhs->py_translate(dst,scp);
}

void SubExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	//Run lhs where value is stored into lReg
	lhs->print_mips(dst,program);
	//Adjust availReg for rhs
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tsubu $" << dReg << ",$" << dReg <<
		",$" << program.getnReg() << "\n";
	program.freeReg();
}


//-----------------------------------------------------------------------------

//Reduce this by inheriting lhs and rhs??
ORExpression::ORExpression(const Expression* _lhs, const Expression* _rhs) : lhs(_lhs),rhs(_rhs){}
void ORExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "||";
	rhs->print_c(dst);
}
void ORExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << " or ";
	rhs->py_translate(dst,scp);
}
void ORExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	//Run lhs where value is stored into lReg
	lhs->print_mips(dst,program);
	//Adjust availReg for rhs
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tor $" << dReg << ",$" << dReg <<
		",$" << program.getnReg() << "\n";
	program.freeReg();
}

//-----------------------------------------------------------------------------


ANDExpression::ANDExpression(const Expression* _lhs, const Expression* _rhs) : lhs(_lhs),rhs(_rhs){}

void ANDExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "&&";
	rhs->print_c(dst);
}

void ANDExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << " and ";
	rhs->py_translate(dst,scp);
}

void ANDExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	//Run lhs where value is stored into lReg
	lhs->print_mips(dst,program);
	//Adjust availReg for rhs
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tand $" << dReg << ",$" << dReg <<
		",$" << program.getnReg() << "\n";
	program.freeReg();
}

//-----------------------------------------------------------------------------

LessThanExpression::LessThanExpression(const Expression* _lhs, const Expression* _rhs) : lhs(_lhs),rhs(_rhs){}

void LessThanExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "<";
	rhs->print_c(dst);
}

void LessThanExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "<";
	rhs->py_translate(dst,scp);
}

void LessThanExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tslt $" << dReg << ",$" << dReg <<
		",$" <<  program.getnReg() << "\n";
	program.freeReg();
}

//-----------------------------------------------------------------------------


GreaterThanExpression::GreaterThanExpression(const Expression* _lhs, const Expression* _rhs) : lhs(_lhs),rhs(_rhs){}

void GreaterThanExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << ">";
	rhs->print_c(dst);
}

void GreaterThanExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << ">";
	rhs->py_translate(dst,scp);
}

void GreaterThanExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tslt $" << dReg << ",$" << program.getnReg() <<
		",$" <<  dReg << "\n";
	program.freeReg();
}


//-----------------------------------------------------------------------------


EqualityExpression::EqualityExpression(const Expression* _lhs, const Expression* _rhs) : lhs(_lhs),rhs(_rhs){}

void EqualityExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "==";
	rhs->print_c(dst);
}

void EqualityExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "==";
	rhs->py_translate(dst,scp);
}

void EqualityExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	std::string eq = program.createLabel();
	std::string end = program.createLabel();

	//Run lhs where value is stored into lReg
	lhs->print_mips(dst,program);
	//Adjust availReg for rhs
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tbeq $" << dReg << ",$" << program.getnReg() <<
		"," << eq << "\n";
	dst << "\tnop\n";
	dst << "\tli $" << dReg << ",0\n";
	dst << "\tb " << end << "\n";
	dst << eq << ":\n";
	dst << "\tli $" << dReg << ",1\n";
	dst << end <<":\n";


	program.freeReg();
}
//-----------------------------------------------------------------------------


LonePostfixExpression::LonePostfixExpression(const Identify* _expr) : expr(_expr){}

void LonePostfixExpression::print_c(std::ostream &dst) const {
	expr->print_c(dst);
	dst << "()";
}

void LonePostfixExpression::py_translate(std::ostream &dst, const scope &scp) const {
	expr->py_translate(dst,scp);
	dst << "()";
}

void LonePostfixExpression::print_mips(std::ostream &dst, context &program) const {
	std::string name = expr->get_ID();

	// program.incFrameSize();
	// dst << "\n\taddiu $sp,$sp,-4\n";
	// dst << "\tmove $fp,$sp\n";
	// program.addVartoScope(name, program.getFrameSize() );
	// dst << "\tsw $0," << program.getFrameSize() - program.getVarOffset(name) << "($fp)\n";

	program.addtoFrameSize(23*4);
	//push 19 registers onto the stack
	dst << "\n\taddiu $sp,$sp,-92\n";
	dst << "\tsw $25,16($sp)\n";
	dst << "\tsw $24,20($sp)\n";
	dst << "\tsw $23,24($sp)\n";
	dst << "\tsw $22,28($sp)\n";
	dst << "\tsw $21,32($sp)\n";
	dst << "\tsw $20,36($sp)\n";
	dst << "\tsw $19,40($sp)\n";
	dst << "\tsw $18,44($sp)\n";
	dst << "\tsw $17,48($sp)\n";
	dst << "\tsw $16,52($sp)\n";
	dst << "\tsw $15,56($sp)\n";
	dst << "\tsw $14,60($sp)\n";
	dst << "\tsw $13,64($sp)\n";
	dst << "\tsw $12,68($sp)\n";
	dst << "\tsw $11,72($sp)\n";
	dst << "\tsw $10,76($sp)\n";
	dst << "\tsw $9,80($sp)\n";
	dst << "\tsw $8,84($sp)\n";
	dst << "\tsw $3,88($sp)\n";
	dst << "\tmove $fp,$sp\n";

	dst << "\t.option pic0\n";
	dst << "\tjal " << name << "\n";
	dst << "\tnop\n";
	dst << "\t.option pic2\n";
	//restore the 19 registers
	// dst << "\n\taddiu $sp,$sp,-76\n";
	dst << "\tlw $25,16($sp)\n";
	dst << "\tlw $24,20($sp)\n";
	dst << "\tlw $23,24($sp)\n";
	dst << "\tlw $22,28($sp)\n";
	dst << "\tlw $21,32($sp)\n";
	dst << "\tlw $20,36($sp)\n";
	dst << "\tlw $19,40($sp)\n";
	dst << "\tlw $18,44($sp)\n";
	dst << "\tlw $17,48($sp)\n";
	dst << "\tlw $16,52($sp)\n";
	dst << "\tlw $15,56($sp)\n";
	dst << "\tlw $14,60($sp)\n";
	dst << "\tlw $13,64($sp)\n";
	dst << "\tlw $12,68($sp)\n";
	dst << "\tlw $11,72($sp)\n";
	dst << "\tlw $10,76($sp)\n";
	dst << "\tlw $9,80($sp)\n";
	dst << "\tlw $8,84($sp)\n";
	dst << "\tlw $3,88($sp)\n";
	dst << "\n\taddiu $sp,$sp,92\n";
	dst << "\tmove $fp,$sp\n";
	program.addtoFrameSize(-23*4);
	dst << "\tmove $" << program.getnReg() << ",$2\n";
}

std::string LonePostfixExpression::get_ID() const{
	return expr->get_ID();
}

//-----------------------------------------------------------------------------


PostfixArguExpression::PostfixArguExpression(const Identify* _expr, const Expression* _arguexpr):
expr(_expr), arguexpr(_arguexpr){}

void PostfixArguExpression::print_c(std::ostream &dst) const {
	expr->print_c(dst);
	dst << "(";
	arguexpr->print_c(dst);
	dst << ")";
}

void PostfixArguExpression::py_translate(std::ostream &dst, const scope &scp) const {
	expr->py_translate(dst,scp);
	dst << "(";
	arguexpr->py_translate(dst,scp);
	dst << ")";
}

void PostfixArguExpression::print_mips(std::ostream &dst, context &program) const {

	std::string name = expr->get_ID();

	program.resetParamPass();
	arguexpr->print_mips(dst,program);
	program.resetParamPass();

	//stack control
	program.addtoFrameSize(23*4);
	//push 19 registers onto the stack
	dst << "\n\taddiu $sp,$sp,-92\n";
	dst << "\tsw $25,16($sp)\n";
	dst << "\tsw $24,20($sp)\n";
	dst << "\tsw $23,24($sp)\n";
	dst << "\tsw $22,28($sp)\n";
	dst << "\tsw $21,32($sp)\n";
	dst << "\tsw $20,36($sp)\n";
	dst << "\tsw $19,40($sp)\n";
	dst << "\tsw $18,44($sp)\n";
	dst << "\tsw $17,48($sp)\n";
	dst << "\tsw $16,52($sp)\n";
	dst << "\tsw $15,56($sp)\n";
	dst << "\tsw $14,60($sp)\n";
	dst << "\tsw $13,64($sp)\n";
	dst << "\tsw $12,68($sp)\n";
	dst << "\tsw $11,72($sp)\n";
	dst << "\tsw $10,76($sp)\n";
	dst << "\tsw $9,80($sp)\n";
	dst << "\tsw $8,84($sp)\n";
	dst << "\tsw $3,88($sp)\n";
	dst << "\tmove $fp,$sp\n";

	dst << "\t.option pic0\n";
	dst << "\tjal " << name << "\n";
	dst << "\tnop\n";
	dst << "\t.option pic2\n";
	//restore the 19 registers
	// dst << "\n\taddiu $sp,$sp,-76\n";
	dst << "\tlw $25,16($sp)\n";
	dst << "\tlw $24,20($sp)\n";
	dst << "\tlw $23,24($sp)\n";
	dst << "\tlw $22,28($sp)\n";
	dst << "\tlw $21,32($sp)\n";
	dst << "\tlw $20,36($sp)\n";
	dst << "\tlw $19,40($sp)\n";
	dst << "\tlw $18,44($sp)\n";
	dst << "\tlw $17,48($sp)\n";
	dst << "\tlw $16,52($sp)\n";
	dst << "\tlw $15,56($sp)\n";
	dst << "\tlw $14,60($sp)\n";
	dst << "\tlw $13,64($sp)\n";
	dst << "\tlw $12,68($sp)\n";
	dst << "\tlw $11,72($sp)\n";
	dst << "\tlw $10,76($sp)\n";
	dst << "\tlw $9,80($sp)\n";
	dst << "\tlw $8,84($sp)\n";
	dst << "\tlw $3,88($sp)\n";
	dst << "\n\taddiu $sp,$sp,92\n";
	dst << "\tmove $fp,$sp\n";
	program.addtoFrameSize(-23*4);
	dst << "\tmove $" << program.getnReg() << ",$2\n";

}

std::string PostfixArguExpression::get_ID() const{
	return expr->get_ID();
}

//----------------------------------------------------------------------------------------------------------

PostArrayExpr::PostArrayExpr(const Identify* _expr, const Expression* _arguexpr):
expr(_expr), arguexpr(_arguexpr){}

void PostArrayExpr::print_c(std::ostream &dst) const {
	expr->print_c(dst);
	dst << "[";
	arguexpr->print_c(dst);
	dst << "]";
}

void PostArrayExpr::py_translate(std::ostream &dst, const scope &scp) const {
	expr->py_translate(dst,scp);
	dst << "[";
	arguexpr->py_translate(dst,scp);
	dst << "]";
}

void PostArrayExpr::print_mips(std::ostream &dst, context &program) const {
	int offset = std::stoi(((Identify*)arguexpr)->get_ID());
	std::string name = expr->get_ID() + std::to_string(offset);

	if( program.isVarGlobal(name) ){
		dst << "\tlui $" << program.getnReg() << ",%hi(" << name << ")\n";
		dst << "\tlw $" << program.getnReg() << ",%lo(" << name << ")($" << program.getnReg() << ")\n";
	}
	else{
		dst << "\tlw $" << program.getnReg() << "," << program.getFrameSize() - program.getVarOffset(name) << "($fp)" << "\n";
	}
	// dst << "\t" << "lw $fp," << FrameSize-4 << "($sp)\n";

}

std::string PostArrayExpr::get_ID() const{
	int offset = std::stoi(((Identify*)arguexpr)->get_ID());
	std::string name = expr->get_ID() + std::to_string(offset);
	return name ;
}
//-----------------------------------------------------------------------------

AssignExprList::AssignExprList(const Expression* _exprlist, const Expression* _expr):
	exprlist(_exprlist), expr(_expr){}

void AssignExprList::print_c(std::ostream &dst) const {
	if(exprlist != NULL){
		exprlist->print_c(dst);
		dst << ",";
	}
	expr->print_c(dst);
}

void AssignExprList::py_translate(std::ostream &dst, const scope &scp) const {
	if(exprlist != NULL){
		exprlist->py_translate(dst,scp);
		dst << ",";
	}
	expr->py_translate(dst,scp);
}

void AssignExprList::print_mips(std::ostream &dst, context &program) const {
	//null don't print next expr
	//in postfixarguexpression set param to 0
	if(exprlist != NULL){
		exprlist->print_mips(dst,program);
	}
	expr->print_mips(dst,program);
	int reg = 4 + program.get_ParamPass();
	dst << "\tmove $" << reg << ",$" << program.getnReg() << "\n";
	program.incrParamPass();
}

//-----------------------------------------------------------------------------

// UnaryOpExpr::UnaryOpExpr(const Expression* _op, const Expression* _expr) : op(_op),expr(_expr){}

// void UnaryOpExpr::print_c(std::ostream &dst) const {
// 	dst << "[";
// 	op->print_c(dst);
// 	dst << "]{";
// 	expr->print_c(dst);
// 	dst << "}";
// }

// void UnaryOpExpr::py_translate(std::ostream &dst, const scope &scp) const {
// 	op->print_c(dst);
// 	expr->py_translate(dst,scp);
// }

// void UnaryOpExpr::print_mips(std::ostream &dst, context &program) const {}

// std::string UnaryOpExpr::get_ID() const{
// 	return "yet to support UnaryOpExpr class get_ID()";
// }


// //-----------------------------------------------------------------------------

// UnaryOp::UnaryOp(const std::string _op) : op(_op){}

// void UnaryOp::print_c(std::ostream &dst) const {
// 	dst << op;
// }

// void UnaryOp::py_translate(std::ostream &dst, const scope &scp) const {
// 	dst << op;
// }

// void UnaryOp::print_mips(std::ostream &dst, context &program) const {}

UnaryCastExpr::UnaryCastExpr(const std::string _op, const Identify* _castexpr) : op(_op),castexpr(_castexpr){}

void UnaryCastExpr::print_c(std::ostream &dst) const {
	dst << op;
	castexpr->print_c(dst);
}

void UnaryCastExpr::py_translate(std::ostream &dst, const scope &scp) const {
	dst << op;
	castexpr->py_translate(dst,scp);
}

void UnaryCastExpr::print_mips(std::ostream &dst, context &program) const {
	castexpr->print_mips(dst,program);
	if(op == "-"){
		dst << "\tsub $" << program.getnReg() << ",$0,$" << program.getnReg(); 
	}

}

std::string  UnaryCastExpr::get_ID() const{
	return castexpr->get_ID();
}


//-----------------------------------------------------------------------------

ParenExpr::ParenExpr(const Expression* _expr) : expr(_expr){}

void ParenExpr::print_c(std::ostream &dst) const {
	dst << "(";
	expr->print_c(dst);
	dst << ")";
}

void ParenExpr::py_translate(std::ostream &dst, const scope &scp) const {
	dst << "(";
	expr->py_translate(dst,scp);
	dst << ")";
}

void ParenExpr::print_mips(std::ostream &dst, context &program) const {
	expr->print_mips(dst,program);
}


std::string ParenExpr::get_ID() const{
	return "ParenExpr not supported for get_ID yet";
}



//-----------------------------------------------------------------------------
DivExpression::DivExpression(const Expression* _lhs, const Expression* _rhs) : 
	lhs(_lhs),rhs(_rhs){}

void DivExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "/";
	rhs->print_c(dst);
}

void DivExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "/";
	rhs->py_translate(dst,scp);
}

void DivExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();

	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tdiv $"  << dReg <<",$" << program.getnReg() << "\n";
	dst << "\tmflo $" << dReg << "\n";
	program.freeReg();
}

//-----------------------------------------------------------------------------
ModExpression::ModExpression(const Expression* _lhs, const Expression* _rhs) : 
	lhs(_lhs),rhs(_rhs){}

void ModExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "%";
	rhs->print_c(dst);
}

void ModExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "%";
	rhs->py_translate(dst,scp);
}

void ModExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	dst << "\n\t #ModExpression \n";
	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tdiv $"  << dReg <<",$" << program.getnReg() << "\n";
	dst << "\tmfhi $" << dReg << "\n";
	program.freeReg();
}
//-----------------------------------------------------------------------------
LshiftExpression::LshiftExpression(const Expression* _lhs, const Expression* _rhs) : 
	lhs(_lhs),rhs(_rhs){}

void LshiftExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "<<";
	rhs->print_c(dst);
}

void LshiftExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "<<";
	rhs->py_translate(dst,scp);
}

void LshiftExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tsll $" << dReg << ",$" << dReg <<",$" << program.getnReg() << "\n";
	program.freeReg();
}
//-----------------------------------------------------------------------------
RshiftExpression::RshiftExpression(const Expression* _lhs, const Expression* _rhs) : 
	lhs(_lhs),rhs(_rhs){}

void RshiftExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << ">>";
	rhs->print_c(dst);
}

void RshiftExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << ">>";
	rhs->py_translate(dst,scp);
}

void RshiftExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tsra $" << dReg << ",$" << dReg <<
		",$" << program.getnReg() << "\n";
	program.freeReg();
}
//-----------------------------------------------------------------------------
LTEQExpression::LTEQExpression(const Expression* _lhs, const Expression* _rhs) : 
	lhs(_lhs),rhs(_rhs){}

void LTEQExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "<=";
	rhs->print_c(dst);
}

void LTEQExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "<=";
	rhs->py_translate(dst,scp);
}

void LTEQExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tslt $" << dReg << ",$" << program.getnReg() <<
		",$" << dReg << "\n";
	dst << "\txori $" << dReg << ",1\n";
	program.freeReg();
}
//-----------------------------------------------------------------------------
GTEQExpression::GTEQExpression(const Expression* _lhs, const Expression* _rhs) : 
	lhs(_lhs),rhs(_rhs){}

void GTEQExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << ">=";
	rhs->print_c(dst);
}

void GTEQExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << ">=";
	rhs->py_translate(dst,scp);
}

void GTEQExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tslt $" << dReg << ",$" << dReg <<
		",$" <<  program.getnReg() << "\n";
	dst << "\txori $" << dReg << ",1\n";
	program.freeReg();
}
//-----------------------------------------------------------------------------
NEQExpression::NEQExpression(const Expression* _lhs, const Expression* _rhs) : 
	lhs(_lhs),rhs(_rhs){}

void NEQExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "!=";
	rhs->print_c(dst);
}

void NEQExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "!=";
	rhs->py_translate(dst,scp);
}

void NEQExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	std::string eq = program.createLabel();
	std::string end = program.createLabel();

	//Run lhs where value is stored into lReg
	lhs->print_mips(dst,program);
	//Adjust availReg for rhs
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tbne $" << dReg << ",$" << program.getnReg() <<
		"," << eq << "\n";
	dst << "\tnop\n";
	dst << "\tli $" << dReg << ",0\n";
	dst << "\tb " << end << "\n";
	dst << eq << ":\n";
	dst << "\tli $" << dReg << ",1\n";
	dst << end <<":\n";


	program.freeReg();
}
//-----------------------------------------------------------------------------
BANDExpression::BANDExpression(const Expression* _lhs, const Expression* _rhs) : 
	lhs(_lhs),rhs(_rhs){}

void BANDExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "&";
	rhs->print_c(dst);
}

void BANDExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "&";
	rhs->py_translate(dst,scp);
}

void BANDExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	dst << "\n\t #XORExpression \n";
	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tand $" << dReg << ",$" << dReg <<
		",$" << program.getnReg() << "\n";
	program.freeReg();
}
//-----------------------------------------------------------------------------
ExclusiveORExpression::ExclusiveORExpression(const Expression* _lhs, const Expression* _rhs) : 
	lhs(_lhs),rhs(_rhs){}

void ExclusiveORExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "^";
	rhs->print_c(dst);
}

void ExclusiveORExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "^";
	rhs->py_translate(dst,scp);
}

void ExclusiveORExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	dst << "\n\t #XORExpression \n";
	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\txor $" << dReg << ",$" << dReg <<
		",$" << program.getnReg() << "\n";
	program.freeReg();
}
//-----------------------------------------------------------------------------
InclusiveORExpression::InclusiveORExpression(const Expression* _lhs, const Expression* _rhs) : 
	lhs(_lhs),rhs(_rhs){}

void InclusiveORExpression::print_c(std::ostream &dst) const {
	lhs->print_c(dst);
	dst << "|";
	rhs->print_c(dst);
}

void InclusiveORExpression::py_translate(std::ostream &dst, const scope &scp) const {
	lhs->py_translate(dst,scp);
	dst << "|";
	rhs->py_translate(dst,scp);
}

void InclusiveORExpression::print_mips(std::ostream &dst, context &program) const {
	int dReg = program.getnReg();
	dst << "\n\t #XORExpression \n";
	lhs->print_mips(dst,program);
	program.assignReg();
	rhs->print_mips(dst,program);
	dst << "\tor $" << dReg << ",$" << dReg <<
		",$" << program.getnReg() << "\n";
	program.freeReg();
}
//-----------------------------------------------------------------------------

PostIncrementExpr::PostIncrementExpr(const Identify* _postfixexpr)
 : postfixexpr(_postfixexpr){}


void PostIncrementExpr::print_c(std::ostream &dst) const {
	postfixexpr->print_c(dst);
	dst << "++\n";
}

void PostIncrementExpr::py_translate(std::ostream &dst, const scope &scp) const {
	postfixexpr->py_translate(dst,scp);
	dst << "++\n";
}


void PostIncrementExpr::print_mips(std::ostream &dst, context &program) const {

	//do expression first then add
	postfixexpr->print_mips(dst,program);
	int destReg = program.getnReg();

	
	program.assignReg();
	// Identify* a = (Identify*)postfixexpr;
	dst << "\tmove $" << program.getnReg() << ",$" << destReg << "\n";
	std::string name = postfixexpr->get_ID();
	dst << "\taddiu $" << program.getnReg() << ",$" << program.getnReg() << ",1\n";
	dst << "\tsw $" << program.getnReg() << ","  << program.getFrameSize()- program.getVarOffset(name) << "($fp)\n";
	program.freeReg();

}

std::string PostIncrementExpr::get_ID() const{
	return postfixexpr->get_ID();
}


//-----------------------------------------------------------------------------

PostDecrementExpr::PostDecrementExpr(const Identify* _postfixexpr)
 : postfixexpr(_postfixexpr){}


void PostDecrementExpr::print_c(std::ostream &dst) const {
	postfixexpr->print_c(dst);
	dst << "--\n";
}

void PostDecrementExpr::py_translate(std::ostream &dst, const scope &scp) const {
	postfixexpr->py_translate(dst,scp);
	dst << "--\n";
}


void PostDecrementExpr::print_mips(std::ostream &dst, context &program) const {

	//do expression first then sub
	postfixexpr->print_mips(dst,program);
	int destReg = program.getnReg();

	
	program.assignReg();
	// Identify* a = (Identify*)postfixexpr;
	dst << "\tmove $" << program.getnReg() << ",$" << destReg << "\n";
	std::string name = postfixexpr->get_ID();
	dst << "\taddiu $" << program.getnReg() << ",$" << program.getnReg() << ",-1\n";
	dst << "\tsw $" << program.getnReg() << ","  << program.getFrameSize()- program.getVarOffset(name) << "($fp)\n";
	program.freeReg();

}

std::string PostDecrementExpr::get_ID() const{
	return postfixexpr->get_ID();
}

//---------------------------------------------------------------------------------

PreIncrementExpr::PreIncrementExpr(const Identify* _Prefixexpr)
 : Prefixexpr(_Prefixexpr){}


void PreIncrementExpr::print_c(std::ostream &dst) const {
	Prefixexpr->print_c(dst);
	dst << "++\n";
}

void PreIncrementExpr::py_translate(std::ostream &dst, const scope &scp) const {
	Prefixexpr->py_translate(dst,scp);
	dst << "++\n";
}


void PreIncrementExpr::print_mips(std::ostream &dst, context &program) const {

	Prefixexpr->print_mips(dst,program);
	std::string name = Prefixexpr->get_ID();
	dst << "\taddiu $" << program.getnReg() << ",$" << program.getnReg() << ",1\n";
	dst << "\tsw $" << program.getnReg() << ","  << program.getFrameSize()- program.getVarOffset(name) << "($fp)\n";

}

std::string PreIncrementExpr::get_ID() const{
	return Prefixexpr->get_ID();
}


//-----------------------------------------------------------------------------

PreDecrementExpr::PreDecrementExpr(const Identify* _Prefixexpr)
 : Prefixexpr(_Prefixexpr){}


void PreDecrementExpr::print_c(std::ostream &dst) const {
	Prefixexpr->print_c(dst);
	dst << "--\n";
}

void PreDecrementExpr::py_translate(std::ostream &dst, const scope &scp) const {
	Prefixexpr->py_translate(dst,scp);
	dst << "--\n";
}


void PreDecrementExpr::print_mips(std::ostream &dst, context &program) const {

	Prefixexpr->print_mips(dst,program);

	std::string name = Prefixexpr->get_ID();
	dst << "\taddiu $" << program.getnReg() << ",$" << program.getnReg() << ",-1\n";
	dst << "\tsw $" << program.getnReg() << ","  << program.getFrameSize()- program.getVarOffset(name) << "($fp)\n";
}

std::string PreDecrementExpr::get_ID() const{
	return Prefixexpr->get_ID();
}

//---------------------------------------------------------------------------------