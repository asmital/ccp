deps: 
	sudo apt-get install libsfml-dev
	

game: game.cpp
	  g++ -c game.cpp
	  g++ game.o -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean: 
	rm -f *.o *.out lex.yy.c parser.tab.c parser.tab.h preprocessed.t game lexerdemo lexer


rungame: game
	 @echo "Autorunning with make.\n\n"
	 @./game

lexerdemo: lexer.l preprocess.sh sample.t
	  chmod 777 preprocess.sh	
	  ./preprocess.sh sample.t preprocessed.t
	  flex lexer.l
	  gcc lex.yy.c -ll -o lexerdemo
	  ./lexerdemo < preprocessed.t
	  

