#ifndef ast_expressions_hpp
#define ast_expressions_hpp

class ExpressionVariable : public Node {
private:
	const std::string *variable;
public:
	ExpressionVariable(const std::string* _variable) : variable(_variable){}
	virtual void print(std::ostream &dst) const override{
		dst << *variable;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << *variable;
	}
};

class Value : public Node {
private:
	const double *number;
public:
	Value(const double* _number) : number(_number){}
	virtual void print(std::ostream &dst) const override{
		dst << *number;
	}
	virtual void py_translate(std::ostream &dst) const override{
		dst << *number;
	}
};

#endif