#ifndef SDLGL_TEXTURE_H
#define SDLGL_TEXTURE_H

#include <vector>

#include "./offset.h"
#include "SDL.h"

class Texture {
    std::shared_ptr<SDL_Texture> texture;
    Offset offset;
    int width;
    int height;

   public:
    Texture();
    explicit Texture(const std::shared_ptr<SDL_Texture>& texture);
    Texture(const std::shared_ptr<SDL_Texture>& texture, Offset offset);
    void draw(int x, int y);
    void draw(int x, int y, float angle);
    void draw(int x, int y, float angle, bool flip_h, bool flip_v);
    void draw_src(int x, int y, SDL_Rect src);
    void draw_src_dst(SDL_Rect src, SDL_Rect dst);
    void set_offset(Offset new_offset);
    int get_width() const;
    int get_height() const;
};

#endif