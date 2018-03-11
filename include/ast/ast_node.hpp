#ifndef ast_node_hpp
#define ast_node_hpp
#include <string>
#include <iostream>
#include <memory>
#include <vector>

#include "../codegen/context.hpp"

struct scope{
	int count;
};

static inline const scope increment(const scope& cur){
	scope x = cur;
	x.count +=2;
	return x;
}

struct global{
	std::vector<std::string> var;
};

extern global gbl;

class Node;

typedef const Node *NodePtr;

class Node{
public:
  virtual ~Node();
    //! Tell and Node to print itself to the given stream
  virtual void print_c(std::ostream &dst) const =0;
  virtual void py_translate(std::ostream &dst,  const scope &scp) const =0;
  virtual void print_mips(std::ostream &dst, context &program) const =0;

};


class TranslationUnit: public Node{
private: 
	const NodePtr left;
	const NodePtr right;
public:
	TranslationUnit(const NodePtr leftn,const NodePtr rightn);
	
	~TranslationUnit();
	
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;

};


class Declaration : public Node{
public:
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
	virtual std::string get_name() const = 0;
	virtual std::string get_Label() const = 0;
};


class Statement : public Node {
public:
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};


class Expression : public Node {
public:
	virtual void print_c(std::ostream &dst) const override;
	virtual void py_translate(std::ostream &dst,  const scope &scp) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};





#endif