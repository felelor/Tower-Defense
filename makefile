all:	main

main: Tower.o Tile.o Typeset.o Node.o oldsprite.o oldmain.o
	g++ Tower.o Tile.o Typeset.o Node.o oldsprite.o oldmain.o -o oldmain -lSDL -lSDL_ttf

Tower.o: Tower.cpp
	g++ -c Tower.cpp -lSDL

Tile.o: Tile.cpp
	g++ -c Tile.cpp -lSDL

Typeset.o: Typeset.cpp
	g++ -c Typeset.cpp -lSDL

Node.o: Node.cpp
	g++ -c Node.cpp

oldsprite.o: oldsprite.cpp
	g++ -c oldsprite.cpp -lSDL -lSDL_ttf

oldmain.o: oldmain.cpp
	g++ -c oldmain.cpp -lSDL

clean:
	rm -f *.o main *gch
