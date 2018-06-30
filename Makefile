.DEFAULT_GOAL := lib
SHELL := /bin/bash

CC = g++
FLAGS = -c -std=c++11 -g
FILES = graphics/graphics \
		graphics/resources \
		graphics/font_renderer \
		graphics/fps_counter \
		graphics/sprite \
		input/inputs \
		game/clock \
		game/scene \
		ui/fps_display

OUTPUT = $(FILES:%=build/%.o)

clean:
	rm -f build/*


%.o:
	$(eval SOURCE := $@)
	$(eval SOURCE := $(SOURCE:build/%=%))
	$(eval SOURCE := $(SOURCE:%.o=%.cpp))
	$(CC) $(FLAGS) $(SOURCE) -o $@


lib: directories lib_compile;



directories:
	mkdir -p build
	mkdir -p build/graphics
	mkdir -p build/input
	mkdir -p build/game
	mkdir -p build/ui


lib_compile: $(OUTPUT)

	ar rcs build/libsdlgl.a $(OUTPUT)