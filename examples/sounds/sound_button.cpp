#include "sound_button.h"

#include <sdlgl/audio/sound.h>

#include <memory>

#include "SDL.h"

#define COLOR_CHANGE_AMOUNT 50

SoundButton::SoundButton(const std::shared_ptr<Scene>& scene, int x, int y,
                         int width, int height, SDL_Color color,
                         const std::string& filename)
    : PhysicalEntity(scene, x, y, width, height),
      color(color),
      active_color(get_lighter_color(color)) {
    sound = Sound(filename, 3);
}

void SoundButton::update() {
    // If clicked on, play sound
    SDL_Rect rect = {(int)x, (int)y, w, h};
    if (Inputs::get_instance().is_mouse_down_event_in_rect(&rect)) {
        sound.play();
    }
}

void SoundButton::render() {
    const std::shared_ptr<SDL_Renderer>& renderer =
        Graphics::get_instance().get_renderer();
    SDL_Rect rect = {(int)x, (int)y, w, h};
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
    if (Inputs::get_instance().is_mouse_down_in_rect(&rect)) {
        SDL_SetRenderDrawColor(renderer.get(), active_color.r, active_color.g,
                               active_color.b, active_color.a);
    }
    SDL_RenderFillRect(renderer.get(), &rect);
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