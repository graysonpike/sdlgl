#ifndef INPUTS_H
#define INPUTS_H

#include <SDL2/SDL.h>

// KEY CODE DEFINITIONS
// Edit this file to change key bindings

#define KEY_UP      SDL_SCANCODE_W
#define KEY_DOWN    SDL_SCANCODE_S
#define KEY_LEFT    SDL_SCANCODE_A
#define KEY_RIGHT   SDL_SCANCODE_D

class Inputs {

    bool quit;
    int mouse_x;
    int mouse_y;
    // Boolean array for all keys. See above definitions
    const Uint8 *key_states;
    // Returns true if ESC or 'X' button is pressed
    bool check_for_quit(SDL_Event event);

public:

    Inputs();
    void update();
    // Returns true if the ESC key or 'close window' event was triggered
    bool get_quit();
    // Key codes defined above
    bool is_key_down(int key);

};

#endif