deps: 
	sudo apt-get install libsfml-dev
	

game: game.cpp
	  g++ -c game.cpp
	  g++ game.o -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean: 
	rm -f *.o *.out lex.yy.c parser.tab.cpp parser.tab.hpp preprocessed.t game lexerdemo lexer test


rungame: game
	 @echo "Autorunning with make.\n\n"
	 @./game

lexerdemo: lexer.l preprocess.sh sample.t
	  chmod 777 preprocess.sh	
	  ./preprocess.sh sample.t preprocessed.t
	  flex -d lexer.l
	  gcc lex.yy.c -ll -o lexerdemo
	  ./lexerdemo < preprocessed.t
	  
temp:
	bison -d -t parser.ypp -Wcounterexamples
	flex -d lexer.l
	g++ -o test_d parser.tab.cpp lex.yy.c -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

	bison -d parser.ypp
	flex lexer.l
	g++ -o test parser.tab.cpp lex.yy.c -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

asmitemp:
	bison parser.ypp
	flex lexer.l
	g++ -o test parser.tab.cpp lex.yy.c -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./preprocess.sh test.t amu.t
	
	


