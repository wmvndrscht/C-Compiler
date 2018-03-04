#ifndef ast_declarations_hpp
#define ast_declarations_hpp

#include <string>
#include <iostream>



class DeclarationSpecifier : public Node {
private:
	//can be extern int
	const std::string type;
	const DeclarationSpecifier* decspec;
public:
	DeclarationSpecifier(const std::string &_type, 
		const DeclarationSpecifier* _decspec) : type(_type), decspec(_decspec){}
	
	virtual void print_c(std::ostream &dst) const override{
		dst << type;
		if(decspec != NULL){
			dst << " ";
			decspec->print_c(dst);
			//std::cerr << "[DeclarationSpecifier]" << std::endl;

		}
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << type;
		if( decspec != NULL){
			dst << "\n **>1 Declaration Specifier not in spec for formative** \n";
		}
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class VariableDeclarator : public Node{
private:
	const std::string variable;
public:
	VariableDeclarator(const std::string &_variable) : variable(_variable){}

	virtual void print_c(std::ostream &dst) const override{
		dst << " " << variable;
		//std::cerr << "[VariableDeclarator]" << std::endl;
	}

	virtual void py_translate(std::ostream &dst) const override{
		dst << variable;
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class LoneDeclaration : public Node {
private:
	const DeclarationSpecifier* decspec;
public:
	LoneDeclaration(const DeclarationSpecifier* _decspec) : decspec(_decspec){}

	virtual void print_c(std::ostream &dst) const override{
		decspec->print_c(dst);
		dst << ";";
		//std::cerr << "[LoneDeclaration]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "\n **Lone Declarationnot in py spec**\n";
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class Declaration : public Node{
private:
	const DeclarationSpecifier* decspec;
	const NodePtr initdeclaratorlist;
public:
	Declaration(const DeclarationSpecifier* _decspec,
		const NodePtr _initdeclaratorlist): decspec(_decspec), initdeclaratorlist(_initdeclaratorlist){}

	virtual void print_c(std::ostream &dst) const override{
		decspec->print_c(dst);
		initdeclaratorlist->print_c(dst);
		dst << ";";
		//std::cerr << "[Declaration]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		// decspec->py_translate(dst); don't believe I need this?
		// dst << " ";
		initdeclaratorlist->py_translate(dst);
		dst << "\n  ";
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

//Declaration_Specifiers Declarator Compound_Statement
class FunctionDefinition : public Node{
private:
	const DeclarationSpecifier* decspec;
	const NodePtr dec;
	const CompoundStatement* cstatement;
public:
	FunctionDefinition(const DeclarationSpecifier* _decspec, const NodePtr _dec,
		const CompoundStatement* _cstatement) :  decspec(_decspec), dec(_dec), cstatement(_cstatement){}
	virtual void print_c(std::ostream &dst) const override{
		decspec->print_c(dst);
		dec->print_c(dst);
		cstatement->print_c(dst);
		//std::cerr << "[FunctionDefinition]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "def ";
		dec->py_translate(dst);
		cstatement->py_translate(dst);
	}
	virtual void print_mips(std::ostream &dst) const override{
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
};

class EmptyDeclarator : public Node{
private:
	const NodePtr directdec;
public:
	EmptyDeclarator(const NodePtr _directdec) : directdec(_directdec){}

	virtual void print_c(std::ostream &dst) const override{
		directdec->print_c(dst);
		dst << "()";
		//std::cerr << "[EmptyDeclarator]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		directdec->py_translate(dst);
		dst << "()";
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class InitDeclarator : public Node{
private:
	const NodePtr dec;
	const NodePtr init;
public:
	InitDeclarator(const NodePtr _dec, const NodePtr _init) : dec(_dec), init(_init){}
	virtual void print_c(std::ostream &dst) const override{
		dec->print_c(dst);
		dst << " = ";
		init->print_c(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dec->py_translate(dst);
		dst << "=";
		init->py_translate(dst);
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class LoneInitDeclarator : public Node {
private:
	const NodePtr dec;
public:
	LoneInitDeclarator(const NodePtr _dec) : dec(_dec){}
	virtual void print_c(std::ostream &dst) const override{
		dec->print_c(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dec->py_translate(dst);
		dst << "=0";
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class DeclarationList : public Node{
private:
	const NodePtr dec;
	const NodePtr declist;
public:
	DeclarationList(const NodePtr _dec, const NodePtr _declist) : dec(_dec),
		declist(_declist){}
	virtual void print_c(std::ostream &dst) const override{
		dec->print_c(dst);
		dst << "\n";
		declist->print_c(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dec->py_translate(dst);
		declist->py_translate(dst);
	}
	virtual void print_mips(std::ostream &dst) const override{}

};


class ParamListDeclarator : public Node{
private:
	const NodePtr dec;
	const NodePtr paramlist;
public:
	ParamListDeclarator(const NodePtr _dec, const NodePtr _paramlist) : 
		dec(_dec), paramlist(_paramlist){}
	virtual void print_c(std::ostream &dst) const override{
		dec->print_c(dst);
		dst << "(";
		paramlist->print_c(dst);
		dst << ")";
	}
	virtual void py_translate(std::ostream &dst) const override{
		dec->py_translate(dst);
		dst << "(";
		paramlist->py_translate(dst);
		dst << ")";
	}
	virtual void print_mips(std::ostream &dst) const override{}

};

class ParamDeclaration : public Node{
private:
	const NodePtr decspec;
	const NodePtr dec;
public:
	ParamDeclaration(const NodePtr _decspec, const NodePtr _dec) :
		decspec(_decspec), dec(_dec){}
	virtual void print_c(std::ostream &dst) const override{
		decspec->print_c(dst);
		dec->print_c(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dec->py_translate(dst);
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class ParamList : public Node{
private:
	const NodePtr paramlist;
	const NodePtr param;
public:
	ParamList(const NodePtr _paramlist, const NodePtr _param): 
		paramlist(_paramlist), param(_param){}
	virtual void print_c(std::ostream &dst) const override{
		paramlist->print_c(dst);
		dst << ",";
		param->print_c(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		paramlist->py_translate(dst);
		dst << ",";
		param->py_translate(dst);
	}
	virtual void print_mips(std::ostream &dst) const override{}
};

class AssignmentOperator : public Node{
private:
	const std::string *assignop;
public:
	AssignmentOperator(const std::string *_assignop) : assignop(_assignop){}
	virtual void print_c(std::ostream &dst) const override{
		dst << *assignop;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << *assignop;
	}
	virtual void print_mips(std::ostream &dst) const override{}

};

// class Declaration : public Node{
// private:
// 	const DeclarationSpecifier* decspec;
// 	const NodePtr dec;
// public:
// 	Declaration(const DeclarationSpecifier* _decspec, const NodePtr _dec ) 
// 	: decspec(_decspec), dec(_dec){}
	
// 	virtual void print_c(std::ostream &dst) const override{
// 		decspec->print_c(dst);
// 		dst<<" ";
// 		dec->print_c(dst);
// 	}
// };


#endif