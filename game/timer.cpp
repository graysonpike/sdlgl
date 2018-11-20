#include "timer.h"
#include <SDL2/SDL.h>

Timer::Timer(float duration) {

	this->duration = (unsigned)(duration * 1000); 
	reset();

}

void Timer::reset() {

	start_time = SDL_GetTicks();

}

bool Timer::is_done() {

	unsigned int current_time = SDL_GetTicks();
	return current_time > (start_time + duration);

}
