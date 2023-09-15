#include "sound.h"

#define NEXT_CHANNEL -1
#define NO_REPEAT 0
#define REPEAT -1

Sound::Sound() {}

Sound::Sound(const std::shared_ptr<Mix_Chunk>& sound) { this->sound = sound; }
