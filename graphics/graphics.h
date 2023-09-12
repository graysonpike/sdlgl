#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>

#include "font_renderer.h"
#include "fps_counter.h"
#include "resources.h"

class FontRenderer;

class Graphics {
    // Width and height of the window in px
    int width, height;

    bool debug_visuals_enabled;

    Resources *resources;
    FPSCounter fps_counter;
    FontRenderer *font_renderer;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *capture_surface;

    bool init_sdl(std::string window_title);
    void init_capture_surface();

   public:
    Graphics(int width, int height, std::string window_title = "SDLGL Game");
    void clear_screen(SDL_Color color = (SDL_Color){0, 0, 0, 255});
    void present_renderer(float delta);
    void toggle_debug_visuals();
    void set_debug_visuals(bool enabled);
    int get_width();
    int get_height();
    bool get_debug_visuals_enabled();
    SDL_Renderer *get_renderer();
    FontRenderer *get_font_renderer();
    Resources *get_resources();
    float get_fps();
    void capture_bmp(std::string filename);
    ~Graphics();
};

#endif