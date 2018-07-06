#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


class Sound {

	Mix_Chunk *sound;

public:

	Sound();
	Sound(Mix_Chunk *sound);
	void play();
};

#endif