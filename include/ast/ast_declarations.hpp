#ifndef ast_declarations_hpp
#define ast_declarations_hpp

"include ast_program.hpp"

class Declaration : public Program{

public:
	
	virtual void print(std::ostream &dst) const override{
    dst << getFunction()<<"( ";
    arg->print(dst);
    dst<<" )";
  }


}


class Function_Declaration : public Declaration{

}


#endif