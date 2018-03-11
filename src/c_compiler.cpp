#include "ast.hpp"
#include "ast/ast_node.hpp"
#include "ast/ast_statements.hpp"
#include "ast/ast_declarations.hpp"
#include "ast/ast_expressions.hpp"
#include "../include/ast/ast_node.hpp"
#include "../include/ast.hpp"

#include <fstream>

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
  else if(std::string(argv[1]) == "-S"){
    const Node *ast = parseAST("std::cin");
    std::cout << ".global f\n";
    std::cout << ".align 2\n";
    //.nopmips16
    //.nomicromips
    //.ent
    //.type
    //
    //context(int _destReg, int _lReg, int _rReg, int _availReg)
    context program(2,2,3,3,0);
    ast->print_mips(std::cout, program);
  }
  // if(argc < 2){
	// ast->py_translate(std::cout);
	// ast_>print();
	std::cout<<std::endl;
  // }
  // else if(argc == 5 && argv[1] == "--translate"){
  // 	ast->pytranslate()
  // }

	// bin/c_compiler --translate [source-file.c] -o [dest-file.py]


  return 0;
}
