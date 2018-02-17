#ifndef ast_declarations_hpp
#define ast_declarations_hpp

#include <string>
#include <iostream>




class LoneDeclaration : public Node {
private:
	const std::string type;
public:
	LoneDeclaration(const std::string &_type) : type(_type){}

	virtual void print(std::ostream &dst) const override{
		dst<<type;
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