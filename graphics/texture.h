#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"

#include <vector>

#include "../game/scene.h"
#include "./offset.h"

class Scene;

class Texture {
    std::shared_ptr<SDL_Texture> texture;
    Offset offset;

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
    int get_width();
    int get_height();
};

#endif