#include "ast.hpp"

#include <fstream>

int scopecount = 0;
bool preif = false;

int main(int argc, char *argv[]){
  if(argc < 2){
  	//const Node *ast = cparseAST();
  	//ast->print(std::cout); 
  	const Node *ast = parseAST("std::cin");
  	ast->print(std::cout);
  }
  else if(std::string(argv[1]) == "--translate"){
    const Node *ast = parseAST(argv[2]);
    std::ofstream output(argv[4]);
    ast->py_translate(output);
    output << "\n\nif __name__ == \"__main__\":\n";
    output << "\timport sys\n";
    output << "\tret=main()\n";
    output << "\tsys.exit(ret)";
  }
  else if(std::string(argv[1]) == "py"){

    const Node *ast = parseAST("std::cin");
    ast->py_translate(std::cout);
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
