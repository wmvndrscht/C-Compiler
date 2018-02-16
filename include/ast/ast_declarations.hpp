#ifndef ast_declarations_hpp
#define ast_declarations_hpp

#include <string>
#include <iostream>


class DeclarationSpecifier : public Node {
private:
	std::string type;
public:
	TypeSpecifier(const std::string &_type) : type(_type){}

	virtual void print(std::ostream &dst) const override{
		dst<<type;
	}
}


#endif