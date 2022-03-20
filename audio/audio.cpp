#include "audio.h"
#include <iostream>


Audio::Audio() {

    //Initialize Mixer
    if( Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, HARDWARE_CHANNELS, AUDIO_CHUNK_SIZE) < 0 ) {
        printf("SDL_mixer failed to initialize: %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(ALLOCATED_CHANNELS);

    for (unsigned int i = 0; i < ALLOCATED_CHANNELS; i++) {
        channels[i] = Channel(i);
    }
       
}

int Audio::get_next_free_channel_index() {
    for (unsigned int i = 0; i < ALLOCATED_CHANNELS; i++) {
        if (channels[i].is_free_and_not_playing()) {
            return i;
        }
    }
    return -1;
}

void Audio::update(float delta) {
    for (unsigned int i = 0; i < ALLOCATED_CHANNELS; i++) {
        channels[i].update(delta);
    }
}

Channel *Audio::reserve_channel() {
    int index = get_next_free_channel_index();
    channels[index].reserved = true;
    return &channels[index];
}

Channel *Audio::play_sound(Sound sound, bool repeat) {
    int index = get_next_free_channel_index();
    channels[index].play_sound(sound, repeat);
    return &channels[index];
}
