#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

#include <vector>

#include "../game/scene.h"
#include "./offset.h"

class Scene;

class Texture {
    std::shared_ptr<SDL_Texture> texture;
    Offset offset;

   public:
    Texture();
    Texture(const std::shared_ptr<SDL_Texture>& texture);
    Texture(const std::shared_ptr<SDL_Texture>& texture, Offset offset);
    void draw(const std::shared_ptr<Scene>& scene, int x, int y);
    void draw(const std::shared_ptr<Scene>& scene, int x, int y, float angle);
    void draw(const std::shared_ptr<Scene>& scene, int x, int y, float angle, bool flip_h,
              bool flip_v);
    void draw(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y);
    void draw(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, float angle);
    void draw(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, float angle, bool flip_h,
              bool flip_v);
    void set_offset(Offset new_offset);
    int get_width();
    int get_height();
};

#endif