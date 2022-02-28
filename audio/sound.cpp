#include "sound.h"


#define NEXT_CHANNEL -1
#define NO_REPEAT 0
#define REPEAT -1

Sound::Sound() {

}

Sound::Sound(Mix_Chunk *sound) {
	this->sound = sound;
}
