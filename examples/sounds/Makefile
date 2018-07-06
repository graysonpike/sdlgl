.DEFAULT_GOAL := main.out

FLAGS = -std=c++11 -g3
LIBS  = -L../../build -lsdlgl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

clean:
	rm -f *.out *.o

main.out: main.o sound_button.o
	g++ $(FLAGS) -o main.out main.o sound_button.o $(LIBS)

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

sound_button.o: sound_button.cpp
	g++ $(FLAGS) -c sound_button.cpp