.DEFAULT_GOAL := main.out

FLAGS = -std=c++11 -g3
LIBS  = -L../../build -lsdlgl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

clean:
	rm -f *.out *.o

main.out: main.o player.o
	g++ $(FLAGS) -o main.out main.o player.o $(LIBS)

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

player.o: player.cpp
	g++ $(FLAGS) -c player.cpp