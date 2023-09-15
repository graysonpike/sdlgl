#ifndef TRACK_H
#define TRACK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <memory>

class Track {
    std::shared_ptr<Mix_Music> track;

   public:
    Track();
    Track(const std::shared_ptr<Mix_Music>& track);
};

#endif