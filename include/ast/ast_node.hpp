#ifndef ast_node_hpp
#define ast_node_hpp

#include <string>
#include <iostream>
#include <memory>

#include "../codegen/context.hpp"

class Node;

typedef const Node *NodePtr;

class Node{
public:
  virtual ~Node();
    //! Tell and Node to print itself to the given stream
  virtual void print_c(std::ostream &dst) const =0;
  virtual void py_translate(std::ostream &dst) const =0;
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
	virtual void py_translate(std::ostream &dst) const override;
	virtual void print_mips(std::ostream &dst, context &program) const override;
};



// class Node{
// public:
//   virtual ~Node(){}
//     //! Tell and Node to print itself to the given stream
//   virtual void print_c(std::ostream &dst) const =0;
//   virtual void py_translate(std::ostream &dst) const =0;
//   virtual void print_mips(std::ostream &dst, context &program) const =0;

// };

// class TranslationUnit: public Node{
// private: 
// 	const NodePtr left;
// 	const NodePtr right;
// public:
// 	TranslationUnit(const NodePtr leftn,const NodePtr rightn) : left(leftn), right(rightn){}
	
// 	~TranslationUnit(){ delete left; delete right;}
	
// 	virtual void print_c(std::ostream &dst) const override{
// 		left->print_c(dst);
// 		dst<<"\n";
// 		right->print_c(dst);
// 	}
// 	virtual void py_translate(std::ostream &dst) const override{
// 		left->py_translate(dst);
// 		dst<<"\n";
// 		right->py_translate(dst);
// 	}
// 	virtual void print_mips(std::ostream &dst, context &program) const override{}

// };


#endif