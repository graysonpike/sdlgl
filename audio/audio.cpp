#include "audio.h"


#define REPEAT -1
#define NO_REPEAT 0


Audio::Audio() {

    //Initialize Mixer
    if( Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, HARDWARE_CHANNELS, AUDIO_CHUNK_SIZE) < 0 ) {
        printf("SDL_mixer failed to initialize: %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(ALLOCATED_CHANNELS);

    for (unsigned int i = 0; i < ALLOCATED_CHANNELS; i++) {
        reserved[i] = false;
    }
    
}

int Audio::get_free_channel() {
    for (unsigned int i = 0; i < ALLOCATED_CHANNELS; i++) {
        if (!reserved[i] && !Mix_Playing(i)) {
            return i;
        }
    }
    return -1;
}

int Audio::reserve_channel() {
    int channel = get_free_channel();
    reserved[channel] = true;
    return channel;
}

void Audio::free_channel(int channel) {
    reserved[channel] = false;
}

int Audio::play_sound(Sound sound) {
    int channel = get_free_channel();
    return play_sound(sound, channel);
}

int Audio::play_sound(Sound sound, int channel, bool repeat) {
    return Mix_PlayChannel(channel, sound.sound, repeat ? REPEAT : NO_REPEAT);
}

void Audio::stop_channel(int channel) {
    Mix_HaltChannel(channel);
}

void Audio::set_channel_volume(int channel, int volume) {
    Mix_Volume(channel, volume);
}

void Audio::fade_out_channel(int channel, float time) {
    Mix_FadeOutChannel(channel, time * 1000);
}

int Audio::fade_in_channel(int channel, Sound sound, float time, bool repeat) {
    return Mix_FadeInChannel(channel, sound.sound, repeat ? REPEAT : NO_REPEAT, time * 1000);
}
