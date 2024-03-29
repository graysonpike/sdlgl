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
        fps = Graphics::get_instance().get_fps();
        update_delay_timer = 0;
    }
}

void FPS_Display::render() {
    const Graphics& graphics = Graphics::get_instance();
    if (!graphics.get_debug_visuals_enabled()) {
        return;
    }
    std::string text = "FPS: " + std::to_string(std::lround(fps));
    std::shared_ptr<SDL_Texture> text_texture =
        Graphics::load_font_texture(font, text, color);

    int texture_width, texture_height;
    SDL_QueryTexture(text_texture.get(), NULL, NULL, &texture_width,
                     &texture_height);

    SDL_Rect dst = {X_COORD, Y_COORD, texture_width, texture_height};

    SDL_RenderCopy(graphics.get_renderer().get(), text_texture.get(), NULL,
                   &dst);
}