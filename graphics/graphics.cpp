#include "graphics.h"

#include <utility>

// PRIVATE HELPER FUNCTIONS

// Starts SDL2 and creates a window.
// Also starts additional libraries like sdl_ttf and sdl_mixer
// Some flags can be changed for different rendering settings
bool Graphics::init_sdl(std::string window_title) {
    // Initialize SDL_video
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("Error: Failed to init SDL2: %s\n", SDL_GetError());
        return false;
    }

    // Create SDL Window
    SDL_Window *window_ptr = SDL_CreateWindow(window_title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_OPENGL
    );
    if (window_ptr == nullptr) {
        printf("Could not create window: %s\n", SDL_GetError());
        return false;
    }
    window = std::shared_ptr<SDL_Window>(window_ptr, SDL_DestroyWindow);

    // Initialize renderer with flags
    SDL_Renderer* renderer_ptr = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_ptr == nullptr) {
        printf("Could not init renderer: %s\n", SDL_GetError());
        return false;
    }
    renderer = std::shared_ptr<SDL_Renderer>(renderer_ptr, SDL_DestroyRenderer);

    SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);

    // Initialize TTF
    if (TTF_Init() == -1) {
        printf("SDL_ttf failed to initialize: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

void Graphics::init_capture_surface() {
    SDL_Surface *capture_surface_ptr =
        SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    capture_surface = std::shared_ptr<SDL_Surface>(capture_surface_ptr, SDL_FreeSurface);
}

// PUBLIC FUNCTIONS

// Initializes SDL and loads resources
Graphics::Graphics(int width, int height, std::string window_title) {
    this->width = width;
    this->height = height;
    debug_visuals_enabled = false;
    init_sdl(std::move(window_title));
    resources = std::make_shared<Resources>(renderer);
    font_renderer = std::make_shared<FontRenderer>(renderer, resources);
    fps_counter = FPSCounter();
    init_capture_surface();
}

// Clear the screen with a black background
void Graphics::clear_screen(SDL_Color color) {
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer.get());
};

// Present renderer and record delta time (in seconds)
void Graphics::present_renderer(float delta) {
    SDL_RenderPresent(renderer.get());
    fps_counter.count(delta);
}

void Graphics::toggle_debug_visuals() {
    debug_visuals_enabled = !debug_visuals_enabled;
}

void Graphics::set_debug_visuals(bool enabled) {
    debug_visuals_enabled = enabled;
}

int Graphics::get_width() { return width; }

int Graphics::get_height() { return height; }

bool Graphics::get_debug_visuals_enabled() { return debug_visuals_enabled; }

std::shared_ptr<SDL_Renderer> Graphics::get_renderer() { return renderer; }

std::shared_ptr<FontRenderer> Graphics::get_font_renderer() { return font_renderer; }

std::shared_ptr<Resources> Graphics::get_resources() { return resources; }

float Graphics::get_fps() { return fps_counter.get_fps(); }

void Graphics::capture_bmp(std::string filename) {
    SDL_RenderReadPixels(renderer.get(), nullptr, SDL_GetWindowPixelFormat(window.get()),
                         capture_surface->pixels, capture_surface->pitch);
    SDL_SaveBMP(capture_surface.get(), filename.c_str());
}

Graphics::~Graphics() {
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}