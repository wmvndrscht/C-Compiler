#ifndef ast_declarations_hpp
#define ast_declarations_hpp

#include <string>
#include <iostream>

#include "../ast.hpp"
#include "ast_node.hpp"



class DeclarationSpecifier : public Declaration{
private:
	//can be extern int
	const std::string type;
	const DeclarationSpecifier* decspec;
public:
	DeclarationSpecifier(const std::string &_type, 
		const DeclarationSpecifier* _decspec);
	
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

class VariableDeclarator : public Declaration {
private:
	const std::string variable;
public:
	VariableDeclarator(const std::string &_variable);

	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

class LoneDeclaration : public Declaration{
private:
	const DeclarationSpecifier* decspec;
public:
	LoneDeclaration(const DeclarationSpecifier* _decspec);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

class TheDeclaration : public Declaration{
private:
	const DeclarationSpecifier* decspec;
	const Declaration *initdeclaratorlist;
public:
	TheDeclaration(const DeclarationSpecifier* _decspec,
		const Declaration *_initdeclaratorlist);

	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

//Declaration_Specifiers Declarator Compound_Statement
class FunctionDefinition : public Declaration{
private:
	const DeclarationSpecifier* decspec;
	const Declaration *dec;
	const Statement* cstatement;
public:
	FunctionDefinition(const DeclarationSpecifier* _decspec, const Declaration *_dec,
		const Statement* _cstatement);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

class EmptyDeclarator : public Declaration{
private:
	const Declaration *directdec;
public:
	EmptyDeclarator(const Declaration *_directdec);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

class InitDeclarator : public Declaration {
private:
	const Declaration *dec;
	const NodePtr init;
public:
	InitDeclarator(const Declaration *_dec, const NodePtr _init);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

class LoneInitDeclarator : public Declaration {
private:
	const Declaration *dec;
public:
	LoneInitDeclarator(const Declaration *_dec);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

class DeclarationList : public Declaration{
private:
	const Declaration *declist;
	const Declaration *dec;
public:
	DeclarationList(const Declaration *_declist, const Declaration *_dec);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;

};


class ParamListDeclarator : public Declaration{
private:
	const Declaration *dec;
	const Declaration *paramlist;
public:
	ParamListDeclarator(const Declaration *_dec, const Declaration  *_paramlist);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

class ParamDeclaration : public Declaration{
private:
	const Declaration *decspec;
	const Declaration *dec;
public:
	ParamDeclaration(const Declaration *_decspec, const Declaration *_dec);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

class ParamList : public Declaration{
private:
	const Declaration *paramlist;
	const Declaration *param;
public:
	ParamList(const Declaration *_paramlist, const Declaration *_param);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

class InitDeclaratorList : public Declaration{
private:
	const Declaration* declist;
	const Declaration* dec;
public:
	InitDeclaratorList(const Declaration *_declist, const Declaration *_dec);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};


class ArrayDeclarator : public Declaration{
private:
	const Declaration* dec;
	const Expression* expr;
public:
	ArrayDeclarator(const Declaration *_dec, const Expression *_expr);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};

class TwoDArrayDeclarator : public Declaration{
private:
	const Declaration* dec;
	const Expression* expr;
	const Expression* expr1;
public:
	TwoDArrayDeclarator(const Declaration *_dec, const Expression *_expr, const Expression *_expr1);
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst, const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const override;
	virtual std::string get_Label() const override;
};


#endif