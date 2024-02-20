#include "resources.h"

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
    const std::string& filename) {
    // Imagefile -> Surface -> Texture
    // Empty surface to begin with
    SDL_Surface* loaded_surface_ptr = nullptr;

    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "images/" + filename;

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

Tileset Resources::load_tileset(json &resources_json, const std::string& name) {
    return Tileset(
        get_texture(resources_json["tilesets"][name]["texture"]),
        resources_json["tilesets"][name]["src_scale"],
        resources_json["tilesets"][name]["dst_scale"]
        );
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

    for(int layer_index = 0; layer_index < tilemap_json["layers"].size(); layer_index ++) {
        tilemap.add_layer();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                tilemap.set_tile(layer_index, x, y, tilemap_json["layers"][layer_index][y][x]);
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
            load_tileset(resources, it.key());
    }

    // Load Tilemaps
    for (json::iterator it = resources["tilemaps"].begin();
         it != resources["tilemaps"].end(); it++) {
        tilemaps[it.key()] =
            load_tilemap(it.value()["filename"]);
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
