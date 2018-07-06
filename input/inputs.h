#ifndef INPUTS_H
#define INPUTS_H

#include <SDL2/SDL.h>


class Inputs {

    bool quit;
    int mouse_x;
    int mouse_y;
    bool mouse_button_state;
    bool mouse_button_down_event;
    // Boolean array for all keys. See above definitions
    const Uint8 *key_states;
    // Returns true if ESC or 'X' button is pressed
    bool check_for_quit(SDL_Event event);

public:

    Inputs();
    void update();
    // Returns true if the ESC key or 'close window' event was triggered
    bool get_quit();
    // Keycode definitions: https://wiki.libsdl.org/SDL_Keycode
    bool is_key_down(int key);
    SDL_Point get_mouse_pos();
    bool is_mouse_button_down();
    bool get_mouse_button_down_event();
    bool is_mouse_in_rect(SDL_Rect *rect);
    bool is_mouse_down_in_rect(SDL_Rect *rect);
    bool is_mouse_down_event_in_rect(SDL_Rect *rect);

};

#endif