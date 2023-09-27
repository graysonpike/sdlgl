#ifndef AUDIO_H
#define AUDIO_H

// Disable the miniaudio Device API, we are using SDL Audio as our device
#define MA_NO_DEVICE_IO
#include "../dependencies/miniaudio.h"

#define CHANNELS 2
#define SAMPLE_RATE 48000

#include <SDL2/SDL.h>

// Audio system implemented as a singleton
class Audio {
   private:
    ma_engine engine;
    SDL_AudioDeviceID deviceID;
    ma_engine_config engineConfig;
    SDL_AudioSpec desiredSpec;
    SDL_AudioSpec obtainedSpec;

    Audio();

   public:
    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;

    // Static method to provide global point of access to the instance.
    static Audio& get_instance();

    // Handles the writing to and reading from the SDL Audio device
    static void data_callback(void* pUserData, ma_uint8* pBuffer,
                              int bufferSizeInBytes);
    ma_engine* get_engine();

    ~Audio();
};

#endif