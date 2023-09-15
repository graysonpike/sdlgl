#include "sprite.h"

Sprite::Sprite() : delay(0), frame_timer(0), total_time(0) {}

Sprite::Sprite(Offset offset, float delay)
    : delay(delay), frame_timer(0), total_time(0), offset(offset) {}

void Sprite::add_frame(Texture frame) {
    frame.set_offset(offset);
    frames.push_back(frame);
    total_time = frames.size() * delay;
}

int Sprite::get_frame_num(float delta) {
    while (frame_timer >= total_time) {
        frame_timer -= total_time;
    }
    int frame = (int)(frame_timer / total_time * frames.size());
    frame_timer += delta;
    return frame;
}

void Sprite::draw(const std::shared_ptr<Scene>& scene, int x, int y, float delta) {
    draw(scene->get_graphics()->get_renderer(), x, y, delta);
}

void Sprite::draw(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, float delta) {
    int current_frame = get_frame_num(delta);
    frames[current_frame].draw(renderer, x, y);
}

void Sprite::draw(const std::shared_ptr<Scene>& scene, int x, int y, float angle, bool flip_h,
                  bool flip_v, float delta) {
    draw(scene->get_graphics()->get_renderer(), x, y, angle, flip_h, flip_v,
         delta);
}

void Sprite::draw(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, float angle,
                  bool flip_h, bool flip_v, float delta) {
    int current_frame = get_frame_num(delta);
    frames[current_frame].draw(renderer, x, y, angle, flip_h, flip_v);
}

int Sprite::get_width() { return frames[0].get_width(); }

int Sprite::get_height() { return frames[0].get_height(); }

float Sprite::get_delay() { return delay; }

void Sprite::reset() { frame_timer = 0; }

void Sprite::set_frame_timer(float time) {
    frame_timer = time;
    if (frame_timer < 0) {
        printf("Error, frame time reset to below zero\n");
        frame_timer = 0;
    }
    if (frame_timer >= total_time) {
        printf("Error, frame time reset beyond maximum\n");
        frame_timer = 0;
    }
}

void Sprite::set_delay(float delay) {
    this->delay = delay;
    total_time = frames.size() * delay;
}