#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "audio.h"

class Sound {
   private:
    static const std::string sounds_dir;
    std::vector<std::shared_ptr<ma_sound>> sounds;
    int instances;
    bool is_playing(int instance);

   public:
    Sound();
    explicit Sound(const std::string& filename, int instances = 1);
    void play();
    void stop();
    void set_looping(bool looping);
    bool is_looping();
    void set_pitch(float pitch);
    float get_pitch();
    bool is_playing();
};

#endif