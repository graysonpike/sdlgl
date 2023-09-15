#include "font_renderer.h"

FontRenderer::FontRenderer(const std::shared_ptr<SDL_Renderer>& renderer, const std::shared_ptr<Resources>& resources) {
    this->renderer = renderer;
    this->resources = resources;
}

// Draws text to a blank surface and transfers that to the given texture
std::shared_ptr<SDL_Texture> FontRenderer::load_font_texture(const std::string& font,
                                     const std::string& text, SDL_Color text_color) {

    // Load temporary surface and convert to texture
    // TTF_RenderText_Solid = quick & dirty
    // TTF_RenderText_Shaded = slow & antialiased, but with opaque box
    // TTF_RenderText_Blended = very slow & antialiased with alpha blending
    SDL_Surface *surface_ptr = TTF_RenderText_Blended(resources->get_font(font).get(),
                                            text.c_str(), text_color);
    if (surface_ptr == nullptr) {
        printf("Error loading font surface: %s\n", TTF_GetError());
        return nullptr;
    }

    // Transfer surface to texture
    SDL_Texture *texture_ptr = SDL_CreateTextureFromSurface(renderer.get(), surface_ptr);
    if (texture_ptr == nullptr) {
        printf("Unable to create texture from surface: %s\n", SDL_GetError());
        return nullptr;
    }

    // Free temporary surface and exit
    SDL_FreeSurface(surface_ptr);
    return {texture_ptr, SDL_DestroyTexture};
}
