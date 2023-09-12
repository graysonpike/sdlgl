#include "sound_button.h"

#include <SDL2/SDL.h>

#include "../../graphics/resources.h"
#include "../../input/inputs.h"

#define COLOR_CHANGE_AMOUNT 50

SoundButton::SoundButton(Scene *scene, int x, int y, int width, int height,
                         SDL_Color color, std::string sound)
    : PhysicalEntity(scene, x, y, width, height) {
    this->color = color;
    this->active_color = get_lighter_color(color);

    Resources *resources = scene->get_graphics()->get_resources();

    this->sound = resources->get_sound(sound);
}

void SoundButton::update() {
    // If clicked on, play sound
    Inputs *inputs = scene->get_inputs();
    SDL_Rect rect = {(int)x, (int)y, w, h};
    if (inputs->is_mouse_down_event_in_rect(&rect)) {
        scene->get_audio()->play_sound(sound);
    }
}

void SoundButton::render() {
    Inputs *inputs = scene->get_inputs();
    SDL_Renderer *renderer = scene->get_graphics()->get_renderer();
    SDL_Rect rect = {(int)x, (int)y, w, h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if (inputs->is_mouse_down_in_rect(&rect)) {
        SDL_SetRenderDrawColor(renderer, active_color.r, active_color.g,
                               active_color.b, active_color.a);
    }
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Color SoundButton::get_lighter_color(SDL_Color color) {
    SDL_Color lighter = {color.r, color.g, color.b, color.a};
    lighter.r += COLOR_CHANGE_AMOUNT;
    lighter.g += COLOR_CHANGE_AMOUNT;
    lighter.b += COLOR_CHANGE_AMOUNT;
    if (lighter.r > 255) {
        lighter.r = 255;
    }
    if (lighter.g > 255) {
        lighter.g = 255;
    }
    if (lighter.b > 255) {
        lighter.b = 255;
    }
    return lighter;
}