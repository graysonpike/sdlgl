.DEFAULT_GOAL := lib
SHELL := /bin/bash

CC = g++
FLAGS = -c -std=c++11 -g3
FILES = audio/sound \
		audio/track \
		game/clock \
		game/scene \
		graphics/graphics \
		graphics/resources \
		graphics/font_renderer \
		graphics/fps_counter \
		graphics/sprite \
		graphics/texture \
		input/inputs \
		ui/fps_display

OUTPUT = $(FILES:%=build/%.o)

clean:
	rm -f build/*


lib: directories lib_compile;


directories:
	mkdir -p build
	mkdir -p build/audio
	mkdir -p build/game
	mkdir -p build/graphics
	mkdir -p build/input
	mkdir -p build/ui


lib_compile: $(OUTPUT)
	ar rcs build/libsdlgl.a $(OUTPUT)


.SECONDEXPANSION:
$(OUTPUT) : %.o : $$(subst .o,.cpp,$$(subst build/,,$$@))
	$(eval SOURCE := $@)
	$(eval SOURCE := $(SOURCE:build/%=%))
	$(eval SOURCE := $(SOURCE:%.o=%.cpp))
	$(CC) $(FLAGS) $(SOURCE) -o $@