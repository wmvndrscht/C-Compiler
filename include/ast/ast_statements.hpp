#ifndef ast_statements_hpp
#define ast_statements_hpp


#include <string>
#include <iostream>

class CompoundStatement : public Node{
public:
	virtual void print(std::ostream &dst) const override{
		dst<< "{}";
		//std::cerr << "[CompoundStatement]" << std::endl;
	}
};

#endif