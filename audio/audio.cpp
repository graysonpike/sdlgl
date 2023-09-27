#include "audio.h"

#define MA_NO_DEVICE_IO
#define MINIAUDIO_IMPLEMENTATION
#include "../dependencies/miniaudio.h"

Audio& Audio::get_instance() {
    static Audio instance;
    return instance;
}

Audio::Audio() {
    engineConfig = ma_engine_config_init();
    engineConfig.noDevice = MA_TRUE;
    engineConfig.channels = CHANNELS;
    engineConfig.sampleRate = SAMPLE_RATE;

    ma_result result;
    result = ma_engine_init(&engineConfig, &engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine.");
    }

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        printf("Failed to initialize SDL sub-system.");
    }

    MA_ZERO_OBJECT(&desiredSpec);
    desiredSpec.freq = ma_engine_get_sample_rate(&engine);
    desiredSpec.format = AUDIO_F32;
    desiredSpec.channels = ma_engine_get_channels(&engine);
    desiredSpec.samples = 512;
    desiredSpec.callback = data_callback;
    desiredSpec.userdata = this;

    deviceID = SDL_OpenAudioDevice(NULL, 0, &desiredSpec, &obtainedSpec,
                                   SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (deviceID == 0) {
        printf("Failed to open SDL audio device.");
    }

    SDL_PauseAudioDevice(deviceID, 0);
}

void Audio::data_callback(void* pUserData, ma_uint8* pBuffer,
                          int bufferSizeInBytes) {
    Audio* audioInstance = static_cast<Audio*>(pUserData);
    ma_uint32 bufferSizeInFrames =
        (ma_uint32)bufferSizeInBytes /
        ma_get_bytes_per_frame(ma_format_f32,
                               ma_engine_get_channels(&audioInstance->engine));
    ma_engine_read_pcm_frames(&audioInstance->engine, pBuffer,
                              bufferSizeInFrames, NULL);
}

ma_engine* Audio::get_engine() { return &engine; }

Audio::~Audio() {
    ma_engine_uninit(&engine);
    SDL_CloseAudioDevice(deviceID);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
