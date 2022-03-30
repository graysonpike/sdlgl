#ifndef CHANNEL_H
#define CHANNEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../game/timer.h"
#include "sound.h"


class Channel {

    enum FadeMode {
        NO_FADE,
        TIMED,
        RATE
    };

    float volume;
    Timer timer;
    FadeMode fade_mode;
    float fade_volume_difference;
    float fade_target_volume;
    float _fade_rate;

    int get_sdl_volume(float volume);

public:

    int channel;
    bool reserved;
    
    Channel();
    Channel(int channel);
    void update(float delta);
    float get_volume();
    void set_volume(float volume);
    void play_sound(Sound sound, bool repeat = false, float volume=1.0f);
    void stop_playing();
    void fade_time(float volume, float time);
    void fade_time(float from_volume, float to_volume, float time);
    void fade_rate(float volume, float rate);
    void fade_rate(float from_volume, float to_volume, float rate);
    void cancel_fade();
    bool is_playing();
    bool is_free_and_not_playing();
    void free();

};

#endif