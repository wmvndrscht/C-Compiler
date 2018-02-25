#include "ast.hpp"

#include <fstream>


int main(int argc, char *argv[]){
    
  if(argc < 2){
  	const Node *ast = cparseAST();
  	ast->print(std::cout);
  }
  else if(std::string(argv[1]) == "--translate"){
  	const Node *ast = pyparseAST(argv[2]);
  	std::ofstream output(argv[4]);
  	ast->py_translate(output);
    output << "\n\nif _name_ == \"_main_\":\n";
    output << "\timport sys\n";
    output << "\tret=main()\n";
    output << "\tsys.exit(ret)";
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