#include "timer.h"

#include <SDL2/SDL.h>
 
Timer::Timer() : duration(0), active(false) {}

Timer::Timer(float duration) { this->duration = (unsigned)(duration * 1000); }

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

void Timer::set_duration(float duration) { this->duration = duration; }

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

float Timer::elapsed() {
    update();
    if (!active) {
        return 0.0f;
    }
    return (duration - (SDL_GetTicks() - start_time)) / (float)duration;
}

float Timer::duration_remaining() {
    update();
    if (!active) {
        return 0.0f;
    }
    return (SDL_GetTicks() - start_time) / 1000.0f;
}

float Timer::duration_elapsed() {
    update();
    if (!active) {
        return 0.0f;
    }
    return (SDL_GetTicks() - start_time) / 1000.0f;
}

float Timer::get_duration() { return duration; }
