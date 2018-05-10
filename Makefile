.DEFAULT_GOAL := lib

FLAGS = -c -std=c++11 -g

clean:
	rm -f build/*

lib:
	mkdir -p build;
	g++ $(FLAGS) graphics/graphics.cpp      -o build/graphics.o
	g++ $(FLAGS) graphics/resources.cpp     -o build/resources.o
	g++ $(FLAGS) graphics/font_renderer.cpp -o build/font_renderer.o
	g++ $(FLAGS) graphics/fps_counter.cpp   -o build/fps_counter.o
	g++ $(FLAGS) input/inputs.cpp           -o build/inputs.o
	g++ $(FLAGS) game/clock.cpp             -o build/clock.o
	g++ $(FLAGS) game/scene.cpp             -o build/scene.o

	ar rcs build/libsdlgl.a build/graphics.o build/resources.o build/font_renderer.o build/fps_counter.o build/inputs.o build/clock.o build/scene.o