#include "channel.h"
#include <iostream>


#define REPEAT -1
#define NO_REPEAT 0


Channel::Channel() {}


Channel::Channel(int channel) : volume(1.0f),  fade_mode(NO_FADE), channel(channel), reserved(false) {

}


void Channel::update(float delta) {
    switch (fade_mode) {
        case NO_FADE:
            break;
        case TIMED: {
            set_volume(fade_target_volume + (fade_volume_difference  * timer.remaining()));
            if (timer.is_done()) {
                fade_mode = NO_FADE;
                if (fade_target_volume == 0) {
                    stop_playing();
                }
            }
        } break;
        case RATE: {
            float new_volume = volume + (_fade_rate * delta);
            if (_fade_rate > 0) {
                if (new_volume > fade_target_volume) {
                    new_volume = fade_target_volume;
                    fade_mode = NO_FADE;
                }
            } else if (_fade_rate < 0) {
                if (new_volume < fade_target_volume) {
                    new_volume = fade_target_volume;
                    fade_mode = NO_FADE;
                    if (fade_target_volume == 0) {
                        stop_playing();
                    }
                }
            }
            set_volume(new_volume);
        } break;
        default:
            break;
    }
}


int Channel::get_sdl_volume(float volume) {
    // Use x^4 curve to approximate logarithmic scale for volume dB
    return int(volume * volume * volume * volume * 128.0f);
}


float Channel::get_volume() {
    return volume;
}


void Channel::set_volume(float volume) {
    if (volume > 1.0f) { volume = 1.0f;}
    if (volume < 0.0f) { volume = 0.0f;}
    this->volume = volume;
    Mix_Volume(channel, get_sdl_volume(volume));
}


void Channel::play_sound(Sound sound, bool repeat) {
    if (repeat) {
        std::cout << "REPEATING" << std::endl;
    }
    Mix_HaltChannel(channel);
    std::cout << "Playing sound to Mixer" << std::endl;
    Mix_PlayChannel(channel, sound.sound, repeat ? REPEAT : NO_REPEAT);
}


void Channel::stop_playing() {
    Mix_HaltChannel(channel);
}


void Channel::fade_time(float volume, float time) {
    fade_mode = TIMED;
    fade_target_volume = volume;
    timer.set_duration(time);
    timer.reset();
}


void Channel::fade_time(float from_volume, float to_volume, float time) {
    set_volume(from_volume);
    fade_time(to_volume, time);
}


void Channel::fade_rate(float volume, float rate) {
    fade_mode = RATE;
    fade_target_volume = volume;
    _fade_rate = rate;
}


void Channel::fade_rate(float from_volume, float to_volume, float rate) {
    set_volume(from_volume);
    fade_rate(to_volume, rate);
}


void Channel::cancel_fade() {
    fade_mode = NO_FADE;
}


bool Channel::is_playing() {
    return Mix_Playing(channel);
}


bool Channel::is_free_and_not_playing() {
    return !reserved && !is_playing();
}


void Channel::free() {
    reserved = false;
}
