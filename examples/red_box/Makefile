.DEFAULT_GOAL := main.out

FLAGS = -g -std=c++11
LIBS  = -L../../build -lsdlgl -lSDL2 -lSDL2_image -lSDL2_ttf

clean:
	rm -f *.out *.o

main.out: main.o box.o demo_world.o
	g++ $(FLAGS) -o main.out main.o box.o demo_world.o $(LIBS)

main.o: main.cpp
	g++ -g -c -std=c++11 main.cpp

box.o: box.cpp
	g++ -g -c -std=c++11 box.cpp

demo_world.o: demo_world.cpp
	g++ -g -c -std=c++11 demo_world.cpp