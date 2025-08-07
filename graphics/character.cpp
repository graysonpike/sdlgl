#include "character.h"

#include <utility>

Character::Character() {};

void Character::add_layer(std::string layer_name) {
    layers.emplace_back();
    layer_names.emplace_back(layer_name);
    current_styles.push_back(-1);  // Default value -1 represents nothing should
                                   // be drawn for this layer
}

void Character::add_layer_style(int layer, const Texture& texture) {
    layers[layer].push_back(texture);
}

void Character::add_sprite(std::string name, CharacterSprite sprite) {
    sprites[name] = sprite;
}

void Character::add_animation(std::string name, CharacterAnimation animation) {
    animations[name] = animation;
}

void Character::set_dimensions(int new_src_width, int new_src_height,
                               int new_dst_width, int new_dst_height) {
    src_width = new_src_width;
    src_height = new_src_height;
    dst_width = new_dst_width;
    dst_height = new_dst_height;
}

void Character::set_current_sprite(std::string sprite) {
    current_sprite = std::move(sprite);
    current_animation = "";
}

void Character::set_current_animation(std::string animation_str,
                                      bool reset_timer) {
    current_animation = std::move(animation_str);
    current_sprite = "";
    CharacterAnimation& animation = animations[current_animation];
    animation_total_duration =
        animation.frame_delay * (float)(animation.num_frames);
    if (reset_timer) {
        animation_timer = 0;
    }
}

void Character::set_style(int layer, int style) {
    current_styles[layer] = style;
}

void Character::next_style(int layer) {
    current_styles[layer] =
        ((current_styles[layer] + 1) % (get_num_styles(layer) + 1));
}

void Character::prev_style(int layer) {
    current_styles[layer] = current_styles[layer] - 1;
    if (current_styles[layer] < -1) {
        current_styles[layer] = get_num_styles(layer) - 1;
    }
}

int Character::get_style(int layer) { return current_styles[layer]; }

int Character::get_num_styles(int layer) { return (int)(layers[layer].size()); }

const std::vector<std::string>& Character::get_layer_names() const {
    return layer_names;
}

void Character::set_facing(const std::string& new_facing) {
    current_facing = new_facing;
}

std::string Character::get_facing() { return current_facing; }

void Character::draw_sprite(const std::string& sprite_str, int x, int y) {
    const CharacterSprite& sprite = sprites.at(sprite_str);
    // If current_facing is not in the sprite's cells, use the key "default"
    // (for sprites without facing)
    auto it = sprite.cells.find(current_facing);
    if (it == sprite.cells.end()) {
        it = sprite.cells.find("default");
    }
    const Cell& cell = it->second;
    int src_x = cell.column * src_width;
    int src_y = cell.row * src_height;
    SDL_Rect src_rect = {src_x, src_y, src_width, src_height};
    SDL_Rect dst_rect = {x, y, dst_width, dst_height};
    for (int layer = 0; layer < layers.size(); layer++) {
        if (current_styles[layer] == -1) {
            continue;
        }
        layers[layer][current_styles[layer]].draw_src_dst(src_rect, dst_rect);
    }
}

void Character::draw_animation(const std::string& animation_str, int x, int y,
                               float delta) {
    const CharacterAnimation& animation = animations.at(animation_str);
    // If current_facing is not in the animation's cell ranges, use the key
    // "default" (for animations without facing)
    auto it = animation.cells.find(current_facing);
    if (it == animation.cells.end()) {
        it = animation.cells.find("default");
    }
    const Cell& cell = it->second;
    int frame_index = get_frame_index(delta);
    SDL_Rect src_rect = {cell.column * src_width + (frame_index * src_width),
                         cell.row * src_height, src_width, src_height};
    SDL_Rect dst_rect = {x, y, dst_width, dst_height};
    for (int layer = 0; layer < layers.size(); layer++) {
        if (current_styles[layer] == -1) {
            continue;
        }
        layers[layer][current_styles[layer]].draw_src_dst(src_rect, dst_rect);
    }
}

int Character::get_frame_index(float delta) {
    while (animation_timer >= animation_total_duration) {
        animation_timer -= animation_total_duration;
    }
    int num_frames = animations[current_animation].num_frames;
    int frame =
        (int)(animation_timer / animation_total_duration * (float)(num_frames));
    animation_timer += delta;
    return frame;
}

void Character::draw(int x, int y, float delta) {
    // It is assumed that either a sprite or animation will always be specified.
    if (!current_sprite.empty()) {
        draw_sprite(current_sprite, x, y);
    } else {
        draw_animation(current_animation, x, y, delta);
    }
}