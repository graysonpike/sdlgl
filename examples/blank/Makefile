.DEFAULT_GOAL := main.out

FLAGS = -g -std=c++17
LIBS  = -L../../build -lsdlgl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

clean:
	rm -f *.out *.o

main.out: main.o
	g++ $(FLAGS) -o main.out main.o $(LIBS)

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp