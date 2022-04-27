dependencies:
	sudo apt-get install libsfml-dev

lexer: lexer.l
	   @echo "Flex generating source for lexer"
	   flex lexer.l
	   @echo "g++ compiling source for lexer"
	   g++ -c -std=gnu++17 lex.yy.c

parser: parser.ypp game.cpp
		@echo "Bison generating source for LR parser"
		bison -d parser.ypp
		@echo "g++ compiling source for parser AND game engine"
		g++ -c -std=gnu++17 parser.tab.cpp 

engine: parser lexer
	  @echo "g++ linking translation units and SFML libraries"
	  g++ -o engine parser.tab.o lex.yy.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	
run: engine
	 @echo "Preprocessing tetris design spec source"
	 ./preprocess.sh source.t preprocessed.t
	 @echo "Engine parsing design spec and launching game"
	 ./engine < preprocessed.t


clean: 
	rm -f *.o *.out lex.yy.c parser.tab.cpp parser.tab.hpp preprocessed.t game lexerdemo lexer test


