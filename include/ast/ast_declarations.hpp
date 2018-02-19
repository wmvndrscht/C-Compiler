#ifndef ast_declarations_hpp
#define ast_declarations_hpp

#include <string>
#include <iostream>



class DeclarationSpecifier : public Node {
private:
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
		}
	}

};

class VariableDeclarator : public Node{
private:
	const std::string variable;
public:
	VariableDeclarator(const std::string &_variable) : variable(_variable){}

	virtual void print(std::ostream &dst) const override{
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
		std::cerr << "LoneDeclaration: " << std::endl;
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
		std::cerr << "Declaration" << std::endl;
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