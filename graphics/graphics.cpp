#include "graphics.h"

// PRIVATE HELPER FUNCTIONS

// Starts SDL2 and creates a window.
// Also starts additional libraries like sdl_ttf
// Some flags can be changed for different rendering settings
bool Graphics::init_sdl(std::string window_title) {

    // Initialize SDL_video
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("Error: Failed to init SDL2: %s\n", SDL_GetError());
        return false;
    }

    // Create SDL Window
    window = SDL_CreateWindow(
        window_title.c_str(),                  // window title
        SDL_WINDOWPOS_UNDEFINED,      // initial x position
        SDL_WINDOWPOS_UNDEFINED,      // initial y position
        width,                        // width, in pixels
        height,                       // height, in pixels
        SDL_WINDOW_OPENGL             // flags - see below
    );
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return false;
    }

    // Initialize renderer with flags
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        printf("Could not init renderer: %s\n", SDL_GetError());
        return false;
    }

    // Initialize TTF
    if(TTF_Init() == -1) {
        printf("SDL_ttf failed to initialize: %s\n", TTF_GetError());
        return false;
    }

    return true;

}

// PUBLIC FUNCTIONS

// Initializes SDL and loads resources
Graphics::Graphics(int width, int height) {

    this->width = width;
    this->height = height;
    init_sdl("SDLGL Game");
    resources = new Resources(renderer);
    resources->load_resources();
    font_renderer = new FontRenderer(renderer, resources);
    fps_counter = FPSCounter();

}

Graphics::Graphics(int width, int height, std::string window_title) : Graphics(width, height) {

    this->width = width;
    this->height = height;
    init_sdl(window_title);
    resources = new Resources(renderer);
    resources->load_resources();
    font_renderer = new FontRenderer(renderer, resources);
    fps_counter = FPSCounter();

}

// Clear the screen with a black background
void Graphics::clear_screen() {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

};

// Present renderer and record delta time (in seconds)
void Graphics::present_renderer(float delta) {

    SDL_RenderPresent(renderer);
    fps_counter.count(delta);

}

int Graphics::get_width() {
    return width;
}

int Graphics::get_height() {
    return height;
}

SDL_Renderer *Graphics::get_renderer() {
    return renderer;
}

Graphics::~Graphics() {

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete resources;
    delete font_renderer;

}