# Author: Andrew Naughton, 8/8/2020

sudogen: main.o generator.o sudoku.o
	g++ -Wall -std=c++11 -o sudogen main.o generator.o sudoku.o

main.o: main.cpp main.h generator.cpp generator.h
	g++ -Wall -std=c++11 -c main.cpp generator.cpp

generator.o: generator.cpp generator.h sudoku.cpp sudoku.h
	g++ -Wall -std=c++11 -c generator.cpp sudoku.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -Wall -std=c++11 -c sudoku.cpp

clean:
	rm -f *.o sudogen