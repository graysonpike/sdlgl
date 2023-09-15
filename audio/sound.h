#ifndef SOUND_H
#define SOUND_H

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound {
   public:
    std::shared_ptr<Mix_Chunk> sound;

    Sound();
    Sound(const std::shared_ptr<Mix_Chunk>& sound);
};

#endif