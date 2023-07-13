all: compile link

compile:
	g++ -Isrc/include -c main.cpp -o main.o

link:
	g++ main.o -o debug-outcastgame -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system