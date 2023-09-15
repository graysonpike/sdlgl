#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

#include "graphics.h"
#include "resources.h"

class Resources;

class FontRenderer {
    std::shared_ptr<Resources> resources;
    std::shared_ptr<SDL_Renderer> renderer;

   public:
    FontRenderer(const std::shared_ptr<SDL_Renderer>& renderer, const std::shared_ptr<Resources>& resources);
    std::shared_ptr<SDL_Texture> load_font_texture(const std::string& font,
                           const std::string& text, SDL_Color text_color);
};

#endif