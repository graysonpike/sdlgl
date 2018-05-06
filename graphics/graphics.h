#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "resources.h"
#include "fps_counter.h"
#include "font_renderer.h"

class FontRenderer;

class Graphics {

    // Width and height of the window in px
    int width, height;

    Resources *resources;
    FPSCounter fps_counter;
    FontRenderer *font_renderer;
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool init_sdl();

public:

    Graphics(int width, int height);
    void clear_screen();
    void present_renderer(float delta);
    int get_width();
    int get_height();
    ~Graphics();

};

#endif