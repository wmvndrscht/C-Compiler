CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include 


all : bin/c_compiler

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/lexer.flex

bin/c_compiler : src/c_compiler.o src/parser.tab.o src/lexer.yy.o src/parser.tab.o src/ast/ast_node.o src/ast/ast_declarations.o src/ast/ast_statements.o src/ast/ast_expressions.o 
	mkdir -p bin
	clang++ $(CPPFLAGS) -o bin/c_compiler $^
	


clean :
	rm src/*.tab.hpp
	rm src/*.tab.cpp
	rm src/*.output
	rm src/*.o
	rm bin/*
	rm src/*.yy.cpp
	rm src/ast/*.o
