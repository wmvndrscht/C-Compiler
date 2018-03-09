#ifndef ast_hpp
#define ast_hpp

// extern int scopecount;

extern bool preif;

#include "ast/ast_node.hpp"
// #include "ast/ast_statements.hpp"
// #include "ast/ast_declarations.hpp"
// #include "ast/ast_expressions.hpp"

extern const Node *parseAST(const char file[]);


#endif
