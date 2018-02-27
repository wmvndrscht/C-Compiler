#ifndef ast_node_hpp
#define ast_node_hpp

#include <string>
#include <iostream>
#include <memory>

class Node;

typedef const Node *NodePtr;

class Node{
public:
  virtual ~Node(){}
    //! Tell and Node to print itself to the given stream
  virtual void print(std::ostream &dst) const =0;
  virtual void py_translate(std::ostream &dst) const =0;

};

class TranslationUnit: public Node{
private: 
	const NodePtr left;
	const NodePtr right;
public:
	TranslationUnit(const NodePtr leftn,const NodePtr rightn) : left(leftn), right(rightn){}
	
	~TranslationUnit(){ delete left; delete right;}
	
	virtual void print(std::ostream &dst) const override{
		left->print(dst);
		dst<<"\n";
		right->print(dst);
	}
	virtual void py_translate(std::ostream &dst) const override{
		left->py_translate(dst);
		dst<<"\n";
		right->py_translate(dst);
	}

};


#endif