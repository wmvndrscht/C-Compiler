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
	
	virtual void print(std::ostream &dst) const override{
		dst << type;
		if(decspec != NULL){
			dst << " ";
			decspec->print(dst);
			//std::cerr << "[DeclarationSpecifier]" << std::endl;

		}
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << type;
		if( decspec != NULL){
			dst << "\n **>1 Declaration Specifier not in spec for formative** \n";
		}
	}

};

class VariableDeclarator : public Node{
private:
	const std::string variable;
public:
	VariableDeclarator(const std::string &_variable) : variable(_variable){}

	virtual void print(std::ostream &dst) const override{
		dst << " " << variable;
		//std::cerr << "[VariableDeclarator]" << std::endl;
	}

	virtual void py_translate(std::ostream &dst) const override{
		dst << variable;
	}

};

class LoneDeclaration : public Node {
private:
	const DeclarationSpecifier* decspec;
public:
	LoneDeclaration(const DeclarationSpecifier* _decspec) : decspec(_decspec){}

	virtual void print(std::ostream &dst) const override{
		decspec->print(dst);
		dst << ";";
		//std::cerr << "[LoneDeclaration]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "\n **Lone Declarationnot in py spec**\n";
	}
};

class Declaration : public Node{
private:
	const DeclarationSpecifier* decspec;
	const NodePtr initdeclaratorlist;
public:
	Declaration(const DeclarationSpecifier* _decspec,
		const NodePtr _initdeclaratorlist): decspec(_decspec), initdeclaratorlist(_initdeclaratorlist){}

	virtual void print(std::ostream &dst) const override{
		decspec->print(dst);
		initdeclaratorlist->print(dst);
		dst << ";";
		//std::cerr << "[Declaration]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		// decspec->py_translate(dst); don't believe I need this?
		// dst << " ";
		initdeclaratorlist->py_translate(dst);
		dst << "\n  ";
	}
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
	virtual void print(std::ostream &dst) const override{
		decspec->print(dst);
		dec->print(dst);
		cstatement->print(dst);
		//std::cerr << "[FunctionDefinition]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << "def ";
		dec->py_translate(dst);
		cstatement->py_translate(dst);
	}

};

class EmptyDeclarator : public Node{
private:
	const NodePtr directdec;
public:
	EmptyDeclarator(const NodePtr _directdec) : directdec(_directdec){}

	virtual void print(std::ostream &dst) const override{
		directdec->print(dst);
		dst << "()";
		//std::cerr << "[EmptyDeclarator]" << std::endl;
	}
	virtual void py_translate(std::ostream &dst) const override{
		directdec->py_translate(dst);
		dst << "()";
	}
};

class InitDeclarator : public Node{
private:
	const NodePtr dec;
	const NodePtr init;
public:
	InitDeclarator(const NodePtr _dec, const NodePtr _init) : dec(_dec), init(_init){}
	virtual void print(std::ostream &dst) const override{
		dec->print(dst);
		dst << " = ";
		init->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dec->py_translate(dst);
		dst << "=";
		init->py_translate(dst);
	}

};

class LoneInitDeclarator : public Node {
private:
	const NodePtr dec;
public:
	LoneInitDeclarator(const NodePtr _dec) : dec(_dec){}
	virtual void print(std::ostream &dst) const override{
		dec->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dec->py_translate(dst);
		dst << "=0";
	}

};

class DeclarationList : public Node{
private:
	const NodePtr dec;
	const NodePtr declist;
public:
	DeclarationList(const NodePtr _dec, const NodePtr _declist) : dec(_dec),
		declist(_declist){}
	virtual void print(std::ostream &dst) const override{
		dec->print(dst);
		dst << "\n";
		declist->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dec->py_translate(dst);
		declist->py_translate(dst);
	}
};


class ParamListDeclarator : public Node{
private:
	const NodePtr dec;
	const NodePtr paramlist;
public:
	ParamListDeclarator(const NodePtr _dec, const NodePtr _paramlist) : 
		dec(_dec), paramlist(_paramlist){}
	virtual void print(std::ostream &dst) const override{
		dec->print(dst);
		dst << "(";
		paramlist->print(dst);
		dst << ")";
	}
	virtual void py_translate(std::ostream &dst) const override{
		dec->py_translate(dst);
		dst << "(";
		paramlist->py_translate(dst);
		dst << ")";
	}
};

class ParamDeclaration : public Node{
private:
	const NodePtr decspec;
	const NodePtr dec;
public:
	ParamDeclaration(const NodePtr _decspec, const NodePtr _dec) :
		decspec(_decspec), dec(_dec){}
	virtual void print(std::ostream &dst) const override{
		decspec->print(dst);
		dec->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		dec->py_translate(dst);
	}

};

class ParamList : public Node{
private:
	const NodePtr paramlist;
	const NodePtr param;
public:
	ParamList(const NodePtr _paramlist, const NodePtr _param): 
		paramlist(_paramlist), param(_param){}
	virtual void print(std::ostream &dst) const override{
		paramlist->print(dst);
		dst << ",";
		param->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		paramlist->py_translate(dst);
		dst << ",";
		param->py_translate(dst);
	}
};

class AssignmentOperator : public Node{
private:
	const std::string *assignop;
public:
	AssignmentOperator(const std::string *_assignop) : assignop(_assignop){}
	virtual void print(std::ostream &dst) const override{
		dst << *assignop;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << *assignop;
	}
};

// class Declaration : public Node{
// private:
// 	const DeclarationSpecifier* decspec;
// 	const NodePtr dec;
// public:
// 	Declaration(const DeclarationSpecifier* _decspec, const NodePtr _dec ) 
// 	: decspec(_decspec), dec(_dec){}
	
// 	virtual void print(std::ostream &dst) const override{
// 		decspec->print(dst);
// 		dst<<" ";
// 		dec->print(dst);
// 	}
// };


#endif