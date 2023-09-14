#include "fps_display.h"

#include <cmath>
#include <utility>

#define REFRESH_INTERVAL 1.0
#define X_COORD 16
#define Y_COORD 16

FPS_Display::FPS_Display(const std::shared_ptr<Scene>& scene, std::string font,
                         SDL_Color color)
    : Entity(scene),
      fps(0),
      update_delay_timer(0),
      font(std::move(font)),
      color(color) {}

void FPS_Display::update() {
    update_delay_timer += scene->get_delta();
    if (update_delay_timer >= REFRESH_INTERVAL) {
        fps = scene->get_graphics()->get_fps();
        update_delay_timer = 0;
    }
}

void FPS_Display::render() {
    if (!scene->get_graphics()->get_debug_visuals_enabled()) {
        return;
    }

    SDL_Texture* text_texture = nullptr;
    int texture_width, texture_height;

    std::string text = "FPS: " + std::to_string(std::lround(fps));

    scene->get_graphics()->get_font_renderer()->load_font_texture(
        &text_texture, font, text, color);
    SDL_QueryTexture(text_texture, nullptr, nullptr, &texture_width,
                     &texture_height);

    SDL_Rect dst = {X_COORD, Y_COORD, texture_width, texture_height};

    SDL_RenderCopy(scene->get_graphics()->get_renderer(), text_texture, nullptr,
                   &dst);

    SDL_DestroyTexture(text_texture);
}