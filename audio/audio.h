#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "channel.h"
#include "sound.h"

#define AUDIO_FREQUENCY 44100
#define HARDWARE_CHANNELS 2
#define AUDIO_CHUNK_SIZE 4096
#define ALLOCATED_CHANNELS 16

class Audio {
    std::shared_ptr<Channel> channels[ALLOCATED_CHANNELS];
    int get_next_free_channel_index();

   public:
    Audio();
    void update(float delta);
    std::shared_ptr<Channel> reserve_channel();
    std::shared_ptr<Channel> play_sound(Sound sound, bool repeat = false, float volume = 1.0f);
};

#endif