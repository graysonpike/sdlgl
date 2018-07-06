#ifndef TRACK_H
#define TRACK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


class Track {

	Mix_Music *track;

public:

	Track();
	Track(Mix_Music *track);
};

#endif