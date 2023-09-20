#include "entity_count.h"

#include <utility>

#define REFRESH_INTERVAL 0
#define X_COORD 16
#define Y_COORD 32

EntityCount::EntityCount(std::shared_ptr<Scene>& scene, std::string font,
                         SDL_Color color)
    : Entity(scene), entity_count(scene->get_entity_count()) {
    update_delay_timer = 0;
    this->font = std::move(font);
    this->color = color;
}

void EntityCount::update() {
    update_delay_timer += scene->get_delta();
    if (update_delay_timer >= REFRESH_INTERVAL) {
        entity_count = scene->get_entity_count();
        update_delay_timer = 0;
    }
}

void EntityCount::render() {
    const Graphics& graphics = Graphics::get_instance();
    if (!graphics.get_debug_visuals_enabled()) {
        return;
    }

    std::string text = "Entity Count: " + std::to_string(entity_count);
    std::shared_ptr<SDL_Texture> text_texture = Graphics::load_font_texture(font, text, color);

    int texture_width, texture_height;
    SDL_QueryTexture(text_texture.get(), nullptr, nullptr, &texture_width, &texture_height);

    SDL_Rect dst = {X_COORD, Y_COORD, texture_width, texture_height};

    SDL_RenderCopy(graphics.get_renderer().get(), text_texture.get(), nullptr,
                   &dst);
}