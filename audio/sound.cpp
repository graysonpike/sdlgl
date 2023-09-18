#include <iostream>
#include "sound.h"

const std::string Sound::sounds_dir = "res/sounds/";

Sound::Sound(const std::string& filename) {
    Audio& audio = Audio::get_instance();
    std::string filepath = sounds_dir + filename;
    ma_result result = ma_sound_init_from_file(audio.get_engine(), filepath.c_str(), 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS) {
        std::cout<< "Failed to initialize sound:" << filename << std::endl;
    }
}

void Sound::play() {
    ma_sound_start(&sound);
}

void Sound::stop() {
    ma_sound_stop(&sound);
}

void Sound::set_looping(bool looping) {
    ma_bool32 ma_is_looping = looping ? MA_TRUE: MA_FALSE;
    ma_sound_set_looping(&sound, ma_is_looping);
}

bool Sound::is_looping() {
    ma_bool32 ma_is_looping = ma_sound_is_looping(&sound);
    return ma_is_looping == MA_TRUE;
}