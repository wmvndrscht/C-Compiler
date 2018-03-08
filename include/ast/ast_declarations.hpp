#ifndef ast_declarations_hpp
#define ast_declarations_hpp

#include <string>
#include <iostream>

#include "../ast.hpp"
#include "ast_node.hpp"
#include "ast_statements.hpp"


class Declaration : public Node{
};

class Declarator : public Declaration{
public:
	virtual std::string get_Label() const =0;
};

class DeclarationSpecifier : public Declaration{
private:
	//can be extern int
	const std::string type;
	const DeclarationSpecifier* decspec;
public:
	DeclarationSpecifier(const std::string &_type, 
		const DeclarationSpecifier* _decspec);
	
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class VariableDeclarator : public Declarator {
private:
	const std::string variable;
public:
	VariableDeclarator(const std::string &_variable);

	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_Label() const override;
};

class LoneDeclaration : public Declaration{
private:
	const DeclarationSpecifier* decspec;
public:
	LoneDeclaration(const DeclarationSpecifier* _decspec);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class TheDeclaration : public Declaration{
private:
	const DeclarationSpecifier* decspec;
	const Declaration *initdeclaratorlist;
public:
	TheDeclaration(const DeclarationSpecifier* _decspec,
		const Declaration *_initdeclaratorlist);

	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

//Declaration_Specifiers Declarator Compound_Statement
class FunctionDefinition : public Declaration{
private:
	const DeclarationSpecifier* decspec;
	const Declarator *dec;
	const CompoundStatement* cstatement;
public:
	FunctionDefinition(const DeclarationSpecifier* _decspec, const Declarator *_dec,
		const CompoundStatement* _cstatement);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class EmptyDeclarator : public Declarator{
private:
	const Declarator *directdec;
public:
	EmptyDeclarator(const Declarator *_directdec);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_Label() const override;
};

class InitDeclarator : public Declaration{
private:
	const Declaration *dec;
	const NodePtr init;
public:
	InitDeclarator(const Declaration *_dec, const NodePtr _init);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class LoneInitDeclarator : public Declaration{
private:
	const Declaration *dec;
public:
	LoneInitDeclarator(const Declaration *_dec);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class DeclarationList : public Declaration{
private:
	const Declaration *dec;
	const Declaration *declist;
public:
	DeclarationList(const Declaration *_dec, const Declaration *_declist);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;

};


class ParamListDeclarator : public Declarator{
private:
	const Declarator *dec;
	const Declaration *paramlist;
public:
	ParamListDeclarator(const Declarator *_dec, const Declaration *_paramlist);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_Label() const override;
};

class ParamDeclaration : public Declaration{
private:
	const Declaration *decspec;
	const Declaration *dec;
public:
	ParamDeclaration(const Declaration *_decspec, const Declaration *_dec);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class ParamList : public Declaration{
private:
	const Declaration *paramlist;
	const Declaration *param;
public:
	ParamList(const Declaration *_paramlist, const Declaration *_param);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};

class AssignmentOperator : public Declaration{
private:
	const std::string *assignop;
public:
	AssignmentOperator(const std::string *_assignop);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};



// class Declaration : public Declaration{
// private:
// 	const DeclarationSpecifier* decspec;
// 	const Declaration *dec;
// public:
// 	Declaration(const DeclarationSpecifier* _decspec, const Declaration *_dec ) 
// 	: decspec(_decspec), dec(_dec){}
	
// 	virtual void print_c(std::ostream &dst) const override{
// 		decspec->print_c(dst);
// 		dst<<" ";
// 		dec->print_c(dst);
// 	}
// };


// class DeclarationSpecifier : public Declaration{
// private:
// 	//can be extern int
// 	const std::string type;
// 	const DeclarationSpecifier* decspec;
// public:
// 	DeclarationSpecifier(const std::string &_type, 
// 		const DeclarationSpecifier* _decspec) : type(_type), decspec(_decspec){}
	
// 	virtual void print_c(std::ostream &dst) const override{
// 		dst << type;
// 		if(decspec != NULL){
// 			dst << " ";
// 			decspec->print_c(dst);
// 			//std::cerr << "[DeclarationSpecifier]" << std::endl;

// 		}
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		dst << type;
// 		if( decspec != NULL){
// 			dst << "\n **>1 Declaration Specifier not in spec for formative** \n";
// 		}
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}
// };

// class VariableDeclarator : public Declaration{
// private:
// 	const std::string variable;
// public:
// 	VariableDeclarator(const std::string &_variable) : variable(_variable){}

// 	virtual void print_c(std::ostream &dst) const override{
// 		dst << " " << variable;
// 		//std::cerr << "[VariableDeclarator]" << std::endl;
// 	}

// 	virtual void py_translate(std::ostream &dst) const override{
// 		dst << variable;
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}
// };

// class LoneDeclaration : public Declaration{
// private:
// 	const DeclarationSpecifier* decspec;
// public:
// 	LoneDeclaration(const DeclarationSpecifier* _decspec) : decspec(_decspec){}

// 	virtual void print_c(std::ostream &dst) const override{
// 		decspec->print_c(dst);
// 		dst << ";";
// 		//std::cerr << "[LoneDeclaration]" << std::endl;
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		dst << "\n **Lone Declarationnot in py spec**\n";
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}
// };

// class Declaration : public Declaration{
// private:
// 	const DeclarationSpecifier* decspec;
// 	const Declaration *initdeclaratorlist;
// public:
// 	Declaration(const DeclarationSpecifier* _decspec,
// 		const Declaration *_initdeclaratorlist): decspec(_decspec), initdeclaratorlist(_initdeclaratorlist){}

// 	virtual void print_c(std::ostream &dst) const override{
// 		decspec->print_c(dst);
// 		initdeclaratorlist->print_c(dst);
// 		dst << ";";
// 		//std::cerr << "[Declaration]" << std::endl;
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		// decspec->py_translate(dst); don't believe I need this?
// 		// dst << " ";
// 		initdeclaratorlist->py_translate(dst);
// 		dst << "\n  ";
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}
// };

// //Declaration_Specifiers Declarator Compound_Statement
// class FunctionDefinition : public Declaration{
// private:
// 	const DeclarationSpecifier* decspec;
// 	const Declaration *dec;
// 	const CompoundStatement* cstatement;
// public:
// 	FunctionDefinition(const DeclarationSpecifier* _decspec, const Declaration *_dec,
// 		const CompoundStatement* _cstatement) :  decspec(_decspec), dec(_dec), cstatement(_cstatement){}
// 	virtual void print_c(std::ostream &dst) const override{
// 		decspec->print_c(dst);
// 		dec->print_c(dst);
// 		cstatement->print_c(dst);
// 		//std::cerr << "[FunctionDefinition]" << std::endl;
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		dst << "def ";
// 		dec->py_translate(dst);
// 		cstatement->py_translate(dst);
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{
// 		dst << "f:\n";
// 		//Setup the frame on the stack for this function call
// 		dst << "  addiu $sp,$sp,-8\n"; //start with no params
// 		dst << "  sw $fp,4($sp)\n";
// 		dst << "  move $fp,$sp\n";

// 		//now do return expression, will include context later
// 		cstatement->print_mips(dst);
// 		dst << "\n";

// 		//restore frame and stack
// 		dst << "  move $sp,$fp\n";
// 		dst << "  lw $fp,4($sp)\n";
// 		dst << "  addiu $sp,$sp,8\n";

// 		//finish function
// 		dst << "  j $31\n";
// 		dst << "  nop";


// 	}
// };

// class EmptyDeclarator : public Declaration{
// private:
// 	const Declaration *directdec;
// public:
// 	EmptyDeclarator(const Declaration *_directdec) : directdec(_directdec){}

// 	virtual void print_c(std::ostream &dst) const override{
// 		directdec->print_c(dst);
// 		dst << "()";
// 		//std::cerr << "[EmptyDeclarator]" << std::endl;
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		directdec->py_translate(dst);
// 		dst << "()";
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}
// };

// class InitDeclarator : public Declaration{
// private:
// 	const Declaration *dec;
// 	const Declaration *init;
// public:
// 	InitDeclarator(const Declaration *_dec, const Declaration *_init) : dec(_dec), init(_init){}
// 	virtual void print_c(std::ostream &dst) const override{
// 		dec->print_c(dst);
// 		dst << " = ";
// 		init->print_c(dst);
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		dec->py_translate(dst);
// 		dst << "=";
// 		init->py_translate(dst);
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}
// };

// class LoneInitDeclarator : public Declaration{
// private:
// 	const Declaration *dec;
// public:
// 	LoneInitDeclarator(const Declaration *_dec) : dec(_dec){}
// 	virtual void print_c(std::ostream &dst) const override{
// 		dec->print_c(dst);
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		dec->py_translate(dst);
// 		dst << "=0";
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}
// };

// class DeclarationList : public Declaration{
// private:
// 	const Declaration *dec;
// 	const Declaration *declist;
// public:
// 	DeclarationList(const Declaration *_dec, const Declaration *_declist) : dec(_dec),
// 		declist(_declist){}
// 	virtual void print_c(std::ostream &dst) const override{
// 		dec->print_c(dst);
// 		dst << "\n";
// 		declist->print_c(dst);
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		dec->py_translate(dst);
// 		declist->py_translate(dst);
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}

// };


// class ParamListDeclarator : public Declaration{
// private:
// 	const Declaration *dec;
// 	const Declaration *paramlist;
// public:
// 	ParamListDeclarator(const Declaration *_dec, const Declaration *_paramlist) : 
// 		dec(_dec), paramlist(_paramlist){}
// 	virtual void print_c(std::ostream &dst) const override{
// 		dec->print_c(dst);
// 		dst << "(";
// 		paramlist->print_c(dst);
// 		dst << ")";
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		dec->py_translate(dst);
// 		dst << "(";
// 		paramlist->py_translate(dst);
// 		dst << ")";
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}

// };

// class ParamDeclaration : public Declaration{
// private:
// 	const Declaration *decspec;
// 	const Declaration *dec;
// public:
// 	ParamDeclaration(const Declaration *_decspec, const Declaration *_dec) :
// 		decspec(_decspec), dec(_dec){}
// 	virtual void print_c(std::ostream &dst) const override{
// 		decspec->print_c(dst);
// 		dec->print_c(dst);
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		dec->py_translate(dst);
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}
// };

// class ParamList : public Declaration{
// private:
// 	const Declaration *paramlist;
// 	const Declaration *param;
// public:
// 	ParamList(const Declaration *_paramlist, const Declaration *_param): 
// 		paramlist(_paramlist), param(_param){}
// 	virtual void print_c(std::ostream &dst) const override{
// 		paramlist->print_c(dst);
// 		dst << ",";
// 		param->print_c(dst);
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		paramlist->py_translate(dst);
// 		dst << ",";
// 		param->py_translate(dst);
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}
// };

// class AssignmentOperator : public Declaration{
// private:
// 	const std::string *assignop;
// public:
// 	AssignmentOperator(const std::string *_assignop) : assignop(_assignop){}
// 	virtual void print_c(std::ostream &dst) const override{
// 		dst << *assignop;
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		dst << *assignop;
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}

// };


#endif