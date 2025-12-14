#include "resources.h"

#include <filesystem>
#include <fstream>

#include "../dependencies/json.hpp"

// for convenience
using json = nlohmann::json;

// STATIC MEMBERS

const std::string Resources::RES_DIR = "res/";

// PRIVATE HELPER FUNCTIONS

std::shared_ptr<TTF_Font> Resources::load_font(const std::string& filename,
                                               int size) {
    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "fonts/" + filename;
    TTF_Font* font_ptr = TTF_OpenFont(filepath.c_str(), size);
    if (font_ptr == nullptr) {
        printf("Error loading font: %s\n", TTF_GetError());
        return nullptr;
    }
    return {font_ptr, TTF_CloseFont};
}

std::shared_ptr<SDL_Texture> Resources::load_texture(
    const std::string& filename, bool prepend_images_path) {
    // Imagefile -> Surface -> Texture
    // Empty surface to begin with
    SDL_Surface* loaded_surface_ptr = nullptr;

    // Concatenate filename to resource directory
    std::string filepath = filename;
    if (prepend_images_path) {
        filepath = std::string(RES_DIR) + "images/" + filepath;
    }

    // Load imagefile into surface
    loaded_surface_ptr = IMG_Load(filepath.c_str());
    if (loaded_surface_ptr == nullptr) {
        printf("Error loading image: %s\n", SDL_GetError());
        return nullptr;
    }

    // If successful, transfer the surface into the texture
    SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(
        Graphics::get_instance().get_renderer().get(), loaded_surface_ptr);
    if (texture_ptr == nullptr) {
        printf("Unable to create texture from surface: %s\n", SDL_GetError());
    }
    // Mode BLEND allows for rendering with alpha channel changes even on PNGs
    // without an alpha channel
    SDL_SetTextureBlendMode(texture_ptr, SDL_BLENDMODE_BLEND);

    // Free the temporary surface
    SDL_FreeSurface(loaded_surface_ptr);

    return {texture_ptr, SDL_DestroyTexture};
}

Tilemap Resources::load_tilemap(const std::string& filename) {
    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "tilemaps/" + filename;

    // Read JSON object from tilemap file
    std::ifstream file(filepath);
    json tilemap_json;
    file >> tilemap_json;

    // Create Tilemap class instance from JSON definition
    int scale = tilemap_json["scale"];
    int width = tilemap_json["width"];
    int height = tilemap_json["height"];
    std::string tileset_name = tilemap_json["tileset"];
    Tilemap tilemap = Tilemap(scale, width, height, get_tileset(tileset_name));

    for (int layer_index = 0; layer_index < tilemap_json["layers"].size();
         layer_index++) {
        tilemap.add_layer();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                tilemap.set_tile(layer_index, x, y,
                                 tilemap_json["layers"][layer_index][y][x]);
            }
        }
    }

    return tilemap;
}

Resources::Resources() {}

// PUBLIC FUNCTIONS

Resources& Resources::get_instance() {
    static Resources instance;
    return instance;
}

void Resources::load_resources(const std::string& json_filename) {
    // Read JSON object from resources file
    std::ifstream file(json_filename);
    json resources;
    file >> resources;

    // Load Fonts
    for (json::iterator it = resources["fonts"].begin();
         it != resources["fonts"].end(); it++) {
        fonts[it.key()] = load_font(it.value()["filename"], it.value()["size"]);
    }

    // Load Textures
    for (json::iterator it = resources["textures"].begin();
         it != resources["textures"].end(); it++) {
        textures[it.key()] = load_texture(it.value()["filename"]);
        Offset offset = {0, 0, 0, 0};
        if (it.value().find("offset_x") != it.value().end()) {
            offset.x = it.value()["offset_x"];
        }
        if (it.value().find("offset_y") != it.value().end()) {
            offset.y = it.value()["offset_y"];
        }
        if (it.value().find("offset_hflip_x") != it.value().end()) {
            offset.hflip_x = it.value()["offset_hflip_x"];
        }
        if (it.value().find("offset_hflip_y") != it.value().end()) {
            offset.hflip_y = it.value()["offset_hflip_y"];
        }
        texture_offsets[it.key()] = offset;
    }

    // Load Sprites
    for (json::iterator it = resources["sprites"].begin();
         it != resources["sprites"].end(); it++) {
        for (uint i = 0; i < it.value()["frames"].size(); i++) {
            sprite_frames[it.key()].push_back(
                load_texture(it.value()["frames"][i]));
        }
        sprite_frame_delays[it.key()] = it.value()["delay"];
        Offset offset = {0, 0, 0, 0};
        if (it.value().find("offset_x") != it.value().end()) {
            offset.x = it.value()["offset_x"];
        }
        if (it.value().find("offset_y") != it.value().end()) {
            offset.y = it.value()["offset_y"];
        }
        if (it.value().find("offset_hflip_x") != it.value().end()) {
            offset.hflip_x = it.value()["offset_hflip_x"];
        }
        if (it.value().find("offset_hflip_y") != it.value().end()) {
            offset.hflip_y = it.value()["offset_hflip_y"];
        }
        sprite_offsets[it.key()] = offset;
    }

    // Load Tilesets
    for (json::iterator it = resources["tilesets"].begin();
         it != resources["tilesets"].end(); it++) {
        tilesets[it.key()] =
            Tileset(get_texture(resources["tilesets"][it.key()]["texture"]),
                    resources["tilesets"][it.key()]["src_scale"],
                    resources["tilesets"][it.key()]["dst_scale"]);
    }

    // Load Tilemaps
    for (json::iterator it = resources["tilemaps"].begin();
         it != resources["tilemaps"].end(); it++) {
        tilemaps[it.key()] = load_tilemap(it.value()["filename"]);
    }

    // Load Characters
    for (json::iterator it = resources["characters"].begin();
         it != resources["characters"].end(); it++) {
        json character_json = resources["characters"][it.key()];
        Character character;
        // Load Character Sprites
        json sprites_json = character_json["sprites"];
        for (json::iterator sprite_it = sprites_json.begin();
             sprite_it != sprites_json.end(); sprite_it++) {
            Character::CharacterSprite sprite;
            std::string sprite_name = sprite_it.key();
            json facings_json = sprite_it.value();
            for (json::iterator sprite_facing_it = facings_json.begin();
                 sprite_facing_it != facings_json.end(); sprite_facing_it++) {
                Character::Cell cell;
                std::string facing_name = sprite_facing_it.key();
                cell.row = sprite_facing_it.value()["row"];
                cell.column = sprite_facing_it.value()["col"];
                sprite.cells[facing_name] = cell;
            }
            character.add_sprite(sprite_name, sprite);
        }
        // Load Character Animations
        json animations_json = character_json["animations"];
        for (json::iterator animation_it = animations_json.begin();
             animation_it != animations_json.end(); animation_it++) {
            Character::CharacterAnimation animation;
            json animation_json = animation_it.value();
            animation.num_frames = animation_json["num_frames"];
            animation.frame_delay = animation_json["frame_duration"];
            for (json::iterator sprite_facing_it = animation_json.begin();
                 sprite_facing_it != animation_json.end(); sprite_facing_it++) {
                if (sprite_facing_it.key() == "frame_duration" ||
                    sprite_facing_it.key() == "num_frames") {
                    continue;
                }
                Character::Cell cell;
                std::string facing_name = sprite_facing_it.key();
                cell.row = sprite_facing_it.value()["row"];
                cell.column = sprite_facing_it.value()["col"];
                animation.cells[facing_name] = cell;
            }
            character.add_animation(animation_it.key(), animation);
        }
        // Load layer textures
        std::string character_dir =
            "res/images/" + character_json["directory"].get<std::string>();
        json layers_json = character_json["layers"];
        int layer_index = 0;
        for (json::iterator layer_it = layers_json.begin();
             layer_it != layers_json.end(); layer_it++, layer_index++) {
            std::string layer_name = layer_it.value();
            character.add_layer(layer_name);
            std::string layer_textures_dir = character_dir + "/" + layer_name;
            // Store file paths in a vector and sort them, so that ordering is
            // guaranteed
            std::vector<std::filesystem::path> file_paths;
            for (const auto& entry :
                 std::filesystem::directory_iterator(layer_textures_dir)) {
                file_paths.push_back(entry.path());
            }
            std::sort(file_paths.begin(), file_paths.end());
            for (const auto& file_path : file_paths) {
                std::shared_ptr<SDL_Texture> layer_texture =
                    load_texture(file_path, false);
                character.add_layer_style(layer_index, Texture(layer_texture));
            }
        }
        character.set_dimensions(
            character_json["src_width"], character_json["src_height"],
            character_json["dst_width"], character_json["dst_height"]);
        characters[it.key()] = character;
    }

    // Load MenuBackgrounds
    if (resources.find("menu_backgrounds") != resources.end()) {
        for (json::iterator it = resources["menu_backgrounds"].begin();
             it != resources["menu_backgrounds"].end(); it++) {
            json menu_bg_json = it.value();
            std::string tileset_name = menu_bg_json["tileset"];
            Tileset tileset = get_tileset(tileset_name);

            std::vector<int> tiles;
            for (auto& tile : menu_bg_json["tiles"]) {
                tiles.push_back(tile);
            }

            menu_backgrounds[it.key()] = MenuBackground(tileset, tiles);
        }
    }
}

std::shared_ptr<TTF_Font> Resources::get_font(const std::string& name) {
    return fonts[name];
}

Texture Resources::get_texture(const std::string& name) {
    return Texture(textures[name], texture_offsets[name]);
}

Sprite Resources::get_sprite(const std::string& name) {
    Offset offset = sprite_offsets[name];
    float delay = sprite_frame_delays[name];
    Sprite sprite(offset, delay);
    if (sprite_frames[name].empty()) {
        printf("Error: 0 frames in sprite: %s", name.c_str());
    }
    for (uint i = 0; i < sprite_frames[name].size(); i++) {
        sprite.add_frame(Texture(sprite_frames[name][i]));
    }
    return sprite;
}

Character Resources::get_character(const std::string& name) {
    return characters[name];
}

Tileset Resources::get_tileset(const std::string& name) {
    return tilesets[name];
}

Tilemap Resources::get_tilemap(const std::string& name) {
    return tilemaps[name];
}

MenuBackground Resources::get_menu_background(const std::string& name) {
    return menu_backgrounds[name];
}