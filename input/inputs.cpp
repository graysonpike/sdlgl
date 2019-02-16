#include "inputs.h"

// PRIAVTE HELPER FUNCTIONS

bool Inputs::check_for_quit(SDL_Event event) {

    if(event.type == SDL_QUIT) {
        return true;
    }

    if(event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
                return true;
                break;
            default:
                break;
        }
    }

    return false;

}

// PUBLIC FUNCTIONS

Inputs::Inputs() {
    quit = false;
    mouse_button_state = false;
    mouse_button_down_event = false;
}

bool Inputs::get_quit() {
    return quit;
}

void Inputs::update() {

    for(int i = 0; i < NUM_KEYS; i++) {
        key_down_event[i] = false;
    }

    key_states = SDL_GetKeyboardState(NULL);
    mouse_button_down_event = false;

    SDL_Event event;
    while(SDL_PollEvent(&event) != 0) {

        // ESC or X button close the game
        if(check_for_quit(event)) {
            quit = true;
        }

        // Record mouse position when it moves
        if(event.type == SDL_MOUSEMOTION) {
            mouse_x = event.motion.x;
            mouse_y = event.motion.y;
        }

        if(event.type == SDL_MOUSEBUTTONDOWN) {
            mouse_button_state = true;
            mouse_button_down_event = true;
        }

        if(event.type == SDL_MOUSEBUTTONUP) {
            mouse_button_state = false;
        }

        if(event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            key_down_event[event.key.keysym.scancode] = true;
        }
    }
    
}

bool Inputs::is_key_down(int key) {
    return key_states[key];
}

bool Inputs::is_key_down_event(int key) {
    return key_down_event[key];
}

SDL_Point Inputs::get_mouse_pos() {
    return {mouse_x, mouse_y};
}

bool Inputs::is_mouse_button_down() {
    return mouse_button_state;
}

bool Inputs::get_mouse_button_down_event() {
    return mouse_button_down_event;
}

bool Inputs::is_mouse_in_rect(SDL_Rect *rect) {
    SDL_Point mouse_pos = {mouse_x, mouse_y};
    return SDL_PointInRect(&mouse_pos, rect);
}

bool Inputs::is_mouse_down_in_rect(SDL_Rect *rect) {
    SDL_Point mouse_pos = {mouse_x, mouse_y};
    return mouse_button_state && SDL_PointInRect(&mouse_pos, rect);
}

bool Inputs::is_mouse_down_event_in_rect(SDL_Rect *rect) {
    SDL_Point mouse_pos = {mouse_x, mouse_y};
    return mouse_button_down_event && SDL_PointInRect(&mouse_pos, rect);
}