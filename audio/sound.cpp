#include <iostream>
#include <memory>
#include "sound.h"
#include "../dependencies/miniaudio.h"

const std::string Sound::sounds_dir = "res/sounds/";

bool Sound::is_playing(int instance) {
    ma_bool32 playing = ma_sound_is_playing(sounds[instance].get());
    return playing == MA_TRUE;
}

Sound::Sound() {}

Sound::Sound(const std::string& filename, int instances) : instances(instances) {
    Audio& audio = Audio::get_instance();
    std::string filepath = sounds_dir + filename;
    for (int i = 0; i < instances; i++) {
        sounds.emplace_back(std::shared_ptr<ma_sound>(new ma_sound, ma_sound_uninit));
        ma_result result = ma_sound_init_from_file(audio.get_engine(), filepath.c_str(), 0, NULL, NULL, sounds[i].get());
        if (result != MA_SUCCESS) {
            std::string reason;
            if (result == MA_OUT_OF_MEMORY) {
                reason = " - Out of memory.";
            }
            std::string message = "Failed to initialize sound: " + filepath + reason;
            std::cout<< message << std::endl;
            throw std::runtime_error(message);
        }
    }

}

void Sound::play() {
    if (sounds.empty()) {
        std::cout << "Error: Attempting to play sound with no data." << std::endl;
    }
    for (int i = 0; i < instances; i++) {
        if (!is_playing(i)) {
            ma_sound_start(sounds[i].get());
            return;
        }
    }
    std::cout << "Reached end of sound instances vector after new play() was requested." << std::endl;
}

void Sound::stop() {
    for (int i = 0; i < instances; i++) {
        ma_sound_stop(sounds[i].get());
    }
}

// Assumes that instances = 1
void Sound::set_looping(bool looping) {
    if (sounds.size() > 1) {
        std::cout << "Error: Looping functionality should only be used with instances = 1." << std::endl;
    }
    ma_bool32 ma_is_looping = looping ? MA_TRUE: MA_FALSE;
    ma_sound_set_looping(sounds[0].get(), ma_is_looping);
}

// Assumes that instances = 1
bool Sound::is_looping() {
    if (sounds.size() > 1) {
        std::cout << "Error: Looping functionality should only be used with instances = 1." << std::endl;
    }
    ma_bool32 ma_is_looping = ma_sound_is_looping(sounds[0].get());
    return ma_is_looping == MA_TRUE;
}

void Sound::set_pitch(float pitch) {
    for (int i = 0; i < instances; i++) {
        ma_sound_set_pitch(sounds[i].get(), pitch);
    }
}

float Sound::get_pitch() {
    return ma_sound_get_pitch(sounds[0].get());
}

bool Sound::is_playing() {
    for (int i = 0; i < instances; i++) {
        if (is_playing(i)) {
            return true;
        }
    }
    return false;
}
