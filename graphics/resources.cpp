#include "resources.h"

#include <fstream>

#include "../dependencies/json.hpp"

// for convenience
using json = nlohmann::json;

// STATIC MEMBERS

const std::string Resources::RES_DIR = "res/";

// PRIVATE HELPER FUNCTIONS

std::shared_ptr<Mix_Chunk> Resources::load_sound(const std::string& filename) {
    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "sounds/" + filename;

    Mix_Chunk *sound_ptr = Mix_LoadWAV(filepath.c_str());
    if (sound_ptr == nullptr) {
        printf("Failed to load sound: %s\n", Mix_GetError());
        return nullptr;
    }
    return {sound_ptr, Mix_FreeChunk};
}

std::shared_ptr<Mix_Music> Resources::load_track(const std::string& filename) {
    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "tracks/" + filename;

    Mix_Music *track_ptr = Mix_LoadMUS(filepath.c_str());
    if (track_ptr == nullptr) {
        printf("Failed to load track: %s\n", Mix_GetError());
        return nullptr;
    }
    return {track_ptr, Mix_FreeMusic};
}

std::shared_ptr<TTF_Font> Resources::load_font(const std::string& filename, int size) {
    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "fonts/" + filename;
    TTF_Font *font_ptr = TTF_OpenFont(filepath.c_str(), size);
    if (font_ptr == nullptr) {
        printf("Error loading font: %s\n", TTF_GetError());
        return nullptr;
    }
    return {font_ptr, TTF_CloseFont};
}

std::shared_ptr<SDL_Texture> Resources::load_texture(const std::string& filename) {

    // Imagefile -> Surface -> Texture
    // Empty surface to begin with
    SDL_Surface *loaded_surface_ptr = nullptr;

    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "images/" + filename;

    // Load imagefile into surface
    loaded_surface_ptr = IMG_Load(filepath.c_str());
    if (loaded_surface_ptr == nullptr) {
        printf("Error loading image: %s\n", SDL_GetError());
        return nullptr;
    }

    // If successful, transfer the surface into the texture
    SDL_Texture *texture_ptr = SDL_CreateTextureFromSurface(renderer.get(), loaded_surface_ptr);
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

// PUBLIC FUNCTIONS

Resources::Resources(const std::shared_ptr<SDL_Renderer>& renderer) { this->renderer = renderer; }

void Resources::load_resources(const std::string& json_filename) {
    // Read JSON object from resources file
    std::ifstream file(json_filename);
    json resources;
    file >> resources;

    // Load Sounds
    for (json::iterator it = resources["sounds"].begin();
         it != resources["sounds"].end(); it++) {
        sounds[it.key()] = load_sound(it.value());
    }

    // Load Tracks
    for (json::iterator it = resources["tracks"].begin();
         it != resources["tracks"].end(); it++) {
        tracks[it.key()] = load_track(it.value());
    }

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
            sprite_frames[it.key()].push_back(load_texture(it.value()["frames"][i]));
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
}

Sound Resources::get_sound(const std::string& name) { return Sound(sounds[name]); }

Track Resources::get_track(const std::string& name) { return Track(tracks[name]); }

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

std::vector<std::string> Resources::get_sounds() const {
    std::vector<std::string> keys;
    keys.reserve(sounds.size());
    for (const auto& kv : sounds) {
        keys.push_back(kv.first);
    }
    return keys;
}