#ifndef SOUND_H
#define SOUND_H

#include <memory>
#include <SDL2/SDL.h>
#include "audio.h"

class Sound {
private:
    static const std::string sounds_dir;
    ma_sound sound;
   public:
    Sound(const std::string& filename);
    void play();
    void stop();
    void set_looping(bool looping);
    bool is_looping();
};

#endif