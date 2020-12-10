#include "timer.h"
#include <SDL2/SDL.h>


Timer::Timer() : duration(0) {}


Timer::Timer(float duration) {
    this->duration = (unsigned)(duration * 1000);
}


void Timer::update() {
    
    if (active) {
        unsigned int current_time = SDL_GetTicks();
        active = !(current_time > start_time + duration);
    }

}


void Timer::reset() {

    start_time = SDL_GetTicks();
    active = true;

}


bool Timer::is_done() {

    update();
    return !active;

}


bool Timer::is_active() {

    update();
    return active;
    
}


float Timer::remaining() {

    update();
    if (!active) {
        return 0.0f;
    }
    return 1 - (SDL_GetTicks() - start_time) / (float)duration;

}


float Timer::get_duration() {
    return duration;
}
