#ifndef ast_declarations_hpp
#define ast_declarations_hpp

#include <string>
#include <iostream>



class Declaration_Specifier : Node {
private:
	const std::string type;
	const Declaration_Specifier* decspec;
public:
	Declaration_Specifier(const std::string &_type, 
		const Declaration_Specifier* _decspec) : type(_type), decspec(_decspec){}
	
	virtual void print(std::ostream &dst) const override{
		dst << type;
		if(decspec != NULL){
			dst << " ";
			decspec->print(dst);
		}
	}

};

class LoneDeclaration : public Node {
private:
	const Declaration_Specifier* decspec;
public:
	LoneDeclaration(const Declaration_Specifier* _decspec) : decspec(_decspec){}

	virtual void print(std::ostream &dst) const override{
		decspec->print(dst);
		dst << ";";
		std::cerr << "LoneDeclaration: " << std::endl;
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