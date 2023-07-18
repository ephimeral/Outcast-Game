
all: compile link

compile:
	g++ -I src/include -c main.cpp -o main.o
	g++ -I src/include -c src/game.cpp -o game.o
	g++ -I src/include -c src/stagebuilder.cpp -o stagebuilder.o
	g++ -I src/include -c src/stage.cpp -o stage.o
	g++ -I src/include -c src/player.cpp -o player.o
	g++ -I src/include -c src/animation.cpp -o animation.o
	g++ -I src/include -c src/entity.cpp -o entity.o

link:
	g++ main.o game.o stage.o stagebuilder.o player.o animation.o entity.o -o debug-outcastgame -Lsrc/lib -lwinmm -lsfml-system -lsfml-window -lsfml-graphics