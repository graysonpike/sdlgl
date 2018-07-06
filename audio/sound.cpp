#include "sound.h"


#define NEXT_CHANNEL -1
#define NO_REPEAT 0

Sound::Sound() {

}

Sound::Sound(Mix_Chunk *sound) {
	this->sound = sound;
}

void Sound::play() {
	Mix_PlayChannel(NEXT_CHANNEL, sound, NO_REPEAT);
}