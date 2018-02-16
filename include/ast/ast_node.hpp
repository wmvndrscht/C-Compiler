#ifndef ast_node_hpp
#define ast_node_hpp

#include <iostream>

class Node;

typedef const Node *NodePtr;

class Node{
public:
	virtual ~Node(){};

	virtual void print(std::ostream &dst) const=0;


};

class TranslationUnit: public Node{
private: 
	const NodePtr left;
	const NodePtr right;
public:
	TranslationUnit(const NodePtr leftn,const NodePtr rightn) : left(leftn), right(rightn){}
	
	~TranslationUnit(){ delete left; delete right;}
	
	virtual void print(std::ostream &dst) const override{
		dst << left->print(dst);
		dst << "\n";
		dst << right->print(dst);
	}
}


#endif