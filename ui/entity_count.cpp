#include "entity_count.h"

#define REFRESH_INTERVAL 0
#define X_COORD 16
#define Y_COORD 32

EntityCount::EntityCount(Scene *scene, std::string font, SDL_Color color)
: Entity(scene), entity_count(scene->get_entity_count()) {
    update_delay_timer = 0;
    this->font = font;
    this->color = color;
}

void EntityCount::update() {

    update_delay_timer += scene->get_delta();
    if(update_delay_timer >= REFRESH_INTERVAL) {
        entity_count = scene->get_entity_count();
        update_delay_timer = 0;
    }

}

void EntityCount::render() {

    if (!scene->get_graphics()->get_debug_visuals_enabled()) {
        return;
    }

    SDL_Texture *text_texture = NULL;
    int texture_width, texture_height;
    
    std::string text = "Entity Count: " + std::to_string(entity_count);

    scene->get_graphics()->get_font_renderer()->load_font_texture(
        &text_texture, font, text, color);
    SDL_QueryTexture(text_texture, NULL, NULL, &texture_width, &texture_height);

    SDL_Rect dst = {
        X_COORD,
        Y_COORD,
        texture_width,
        texture_height
    };

    SDL_RenderCopy(scene->get_graphics()->get_renderer(), text_texture, NULL, &dst);

    SDL_DestroyTexture(text_texture);
}