#include "ast.hpp"
#include "ast/ast_node.hpp"
#include "ast/ast_statements.hpp"
#include "ast/ast_declarations.hpp"
#include "ast/ast_expressions.hpp"
#include "../include/ast/ast_node.hpp"
#include "../include/ast.hpp"
#include "codegen/context.hpp"

#include <fstream>
#include <unordered_map>

global gbl;

bool preif = false;

int main(int argc, char *argv[]){
  scope scp;
  scp.count = 0;
  gbl.var.push_back("");
  if(argc < 2){
  	//const Node *ast = cparseAST();
  	//ast->print(std::cout); 
  	const Node *ast = parseAST("std::cin");
  	ast->print_c(std::cout);
  }
  else if(std::string(argv[1]) == "--translate"){
    const Node *ast = parseAST(argv[2]);
    std::ofstream output(argv[4]);
    ast->py_translate(output,scp);
    output << "\n\nif __name__ == \"__main__\":\n";
    output << "\timport sys\n";
    output << "\tret=main()\n";
    output << "\tsys.exit(ret)";
  }
  else if(std::string(argv[1]) == "py"){

    const Node *ast = parseAST("std::cin");
    ast->py_translate(std::cout,scp);
  }
  else if(std::string(argv[1]) == "mips"){
    const Node *ast = parseAST("std::cin");
    std::unordered_map<std::string, int> lMap;

    context programA(2,2,0,lMap,8,0);
    ast->print_mips(std::cout, programA);
  }
  else if(std::string(argv[1]) == "-S"){
    const Node *ast = parseAST(argv[2]);
    std::ofstream output(argv[4]);
    std::unordered_map<std::string, int> Map;

    context program(2,2,0,Map,8,0);
    ast->print_mips(output, program);
  }
	std::cout<<std::endl;
  return 0;
}
