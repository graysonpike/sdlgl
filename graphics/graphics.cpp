#include "graphics.h"

#include <stdexcept>
#include <utility>
#include <iostream>

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
    SDL_Window* window_ptr = SDL_CreateWindow(
        window_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    if (window_ptr == nullptr) {
        printf("Could not create window: %s\n", SDL_GetError());
        return false;
    }
    window = std::shared_ptr<SDL_Window>(window_ptr, SDL_DestroyWindow);

    // Initialize renderer with flags
    SDL_Renderer* renderer_ptr = SDL_CreateRenderer(
        window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_ptr == nullptr) {
        printf("Could not init renderer: %s\n", SDL_GetError());
        return false;
    }
    renderer = std::shared_ptr<SDL_Renderer>(renderer_ptr, SDL_DestroyRenderer);

    // Check if High DPI mode is active
    int renderer_w, renderer_h;
    SDL_GetRendererOutputSize(renderer.get(), &renderer_w, &renderer_h);
    if (renderer_w != width) {
        std::cout << "High DPI detected, setting render scale factor to 2." << std::endl;
        SDL_RenderSetScale(renderer.get(), 2, 2);
    }

    SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);

    // Initialize TTF
    if (TTF_Init() == -1) {
        printf("SDL_ttf failed to initialize: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

void Graphics::init_capture_surface() {
    SDL_Surface* capture_surface_ptr =
        SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    capture_surface =
        std::shared_ptr<SDL_Surface>(capture_surface_ptr, SDL_FreeSurface);
}

Graphics* Graphics::instance = nullptr;

// PUBLIC FUNCTIONS

Graphics& Graphics::get_instance() {
    if (!instance) {
        // Error or provide some default initialization.
        throw std::runtime_error(
            "Must call initialize() before get_instance()");
    }
    return *instance;
}

void Graphics::initialize(int width, int height,
                          const std::string& window_title) {
    if (!instance) {
        instance = new Graphics(width, height, window_title);
    }
}

// Initializes SDL and loads resources
Graphics::Graphics(int width, int height, std::string window_title) {
    this->width = width;
    this->height = height;
    debug_visuals_enabled = false;
    init_sdl(std::move(window_title));
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

int Graphics::get_width() const { return width; }

int Graphics::get_height() const { return height; }

bool Graphics::get_debug_visuals_enabled() const {
    return debug_visuals_enabled;
}

std::shared_ptr<SDL_Renderer> Graphics::get_renderer() const {
    return renderer;
}

float Graphics::get_fps() const { return fps_counter.get_fps(); }

void Graphics::capture_bmp(std::string filename) {
    SDL_RenderReadPixels(renderer.get(), nullptr,
                         SDL_GetWindowPixelFormat(window.get()),
                         capture_surface->pixels, capture_surface->pitch);
    SDL_SaveBMP(capture_surface.get(), filename.c_str());
}

// Draws text to a blank surface and transfers that to the given texture
std::shared_ptr<SDL_Texture> Graphics::load_font_texture(
    const std::string& font, const std::string& text, SDL_Color text_color, int max_width) {
    // Load temporary surface and convert to texture
    SDL_Surface* surface_ptr;
    // TTF_RenderText_Solid = quick & dirty
    // TTF_RenderText_Shaded = slow & antialiased, but with opaque box
    // TTF_RenderText_Blended = very slow & antialiased with alpha blending
    // If max_width is 0, we don't apply any wrapping.
    if (max_width == 0) {
        surface_ptr = TTF_RenderText_Blended(Resources::get_instance().get_font(font).get(),
                                             text.c_str(), text_color);
    } else {
        surface_ptr = TTF_RenderText_Blended_Wrapped(Resources::get_instance().get_font(font).get(),
                                             text.c_str(), text_color, max_width);
    }

    if (surface_ptr == nullptr) {
        printf("Error loading font surface: %s\n", TTF_GetError());
        return nullptr;
    }

    // Transfer surface to texture
    SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(
        Graphics::get_instance().get_renderer().get(), surface_ptr);
    if (texture_ptr == nullptr) {
        printf("Unable to create texture from surface: %s\n", SDL_GetError());
        return nullptr;
    }

    // Free temporary surface and exit
    SDL_FreeSurface(surface_ptr);
    return {texture_ptr, SDL_DestroyTexture};
}

Graphics::~Graphics() {
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}