#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include <vector>

#include "../game/scene.h"
#include "./offset.h"
#include "./texture.h"

class Texture;

class Sprite {
    float delay;
    float frame_timer;
    float total_time;
    Offset offset;
    std::vector<Texture> frames;

    int get_frame_num(float delta);

   public:
    Sprite();
    Sprite(Offset offset, float delay);
    void add_frame(Texture frame);
    void draw(Scene *scene, int x, int y, float delta);
    void draw(Scene *scene, int x, int y, float angle, bool flip_h, bool flip_v,
              float delta);
    void draw(SDL_Renderer *renderer, int x, int y, float delta);
    void draw(SDL_Renderer *renderer, int x, int y, float angle, bool flip_h,
              bool flip_v, float delta);
    int get_width();
    int get_height();
    float get_delay();
    void reset();
    void set_frame_timer(float time);
    void set_delay(float delay);
};

#endif