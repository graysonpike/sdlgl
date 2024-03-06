#include "character.h"

#include <utility>

Character::Character() = default;

void Character::add_layer() {
    layers.emplace_back();
    current_styles.push_back(-1); // Default value -1 represents nothing should be drawn for this layer
}

void Character::add_layer_style(int layer, const Texture& texture) {
    layers[layer].push_back(texture);
}

void Character::set_current_sprite(std::string sprite) {
    current_sprite = std::move(sprite);
    current_animation = "";
}

void Character::set_current_animation(std::string animation) {
    current_animation = std::move(animation);
    current_sprite = "";
}

void Character::set_style(int layer, int style) {
    current_styles[layer] = style;
}

void Character::next_style(int layer) {
    current_styles[layer] = (current_styles[layer] + 1) % get_num_styles(layer);
}

void Character::prev_style(int layer) {
    current_styles[layer] = current_styles[layer] - 1;
    if (current_styles[layer] < 0) {
        current_styles[layer] = get_num_styles(layer) - 1;
    }
}
int Character::get_num_styles(int layer) {
    return layers[layer].size();
}

void Character::draw(int x, int y) {
    if (!current_sprite.empty()) {
        CharacterSprite &sprite = sprites[current_sprite];
        SDL_Rect src_rect = {sprite.column * src_width, sprite.row * src_height, src_width, src_height};
        SDL_Rect dst_rect = {x, y, dst_width, dst_height};
        for (int layer = 0; layer < layers.size(); layer++) {
            layers[layer][current_styles[layer]].draw_src_dst(src_rect, dst_rect);
        }
    }
}