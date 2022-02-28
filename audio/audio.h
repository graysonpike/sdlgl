#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "sound.h"


#define AUDIO_FREQUENCY 44100
#define HARDWARE_CHANNELS 2
#define AUDIO_CHUNK_SIZE 4096
#define ALLOCATED_CHANNELS 16


class Audio {

	bool reserved[ALLOCATED_CHANNELS];
	int get_free_channel();

public:

	Audio();
	int reserve_channel();
	void free_channel(int channel);
	void play_sound(Sound sound);
	void play_sound(Sound sound, int channel, bool repeat = false);
	void stop_channel(int channel);
	void set_channel_volume(int channel, int volume);
	void fade_out_channel(int channel, float time);
	void fade_in_channel(int channel, Sound sound, float time, bool repeat);
    
};

#endif