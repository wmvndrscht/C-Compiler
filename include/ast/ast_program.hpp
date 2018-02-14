#ifndef ast_program_hpp
#define ast_program_hpp



class Program;

typedef const Program *ProgramPtr;

class Program{
public:
	virtual ~Program(){};

	virtual void print(std::ostream &dst) const=0;


};


#endif