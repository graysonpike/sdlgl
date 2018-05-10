.DEFAULT_GOAL := main.out

FLAGS = -std=c++11 -g
LIBS  = -L../../build -lsdlgl -lSDL2 -lSDL2_image -lSDL2_ttf

clean:
	rm -f *.out *.o

main.out: main.o box.o
	g++ $(FLAGS) -o main.out main.o box.o $(LIBS)

main.o: main.cpp
	g++ -g -c -std=c++11 main.cpp

box.o: box.cpp
	g++ -g -c -std=c++11 box.cpp