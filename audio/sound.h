#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound {
   public:
    Mix_Chunk *sound;

    Sound();
    Sound(Mix_Chunk *sound);
};

#endif