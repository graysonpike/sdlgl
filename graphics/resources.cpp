#include <fstream>
#include "../dependencies/json.hpp"
#include "resources.h"

// for convenience
using json = nlohmann::json;

// STATIC MEMBERS

const std::string Resources::RES_DIR = "res/";

// PRIVATE HELPER FUNCTIONS

bool Resources::load_sound(Mix_Chunk **sound, std::string filename) {
    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "sounds/" + filename;

    *sound = Mix_LoadWAV(filepath.c_str());
    if(*sound == NULL) {
        printf("Failed to load sound: %s\n", Mix_GetError());
        return false;
    }
    return true;
}

bool Resources::load_track(Mix_Music **track, std::string filename) {
    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "tracks/" + filename;
    
    *track = Mix_LoadMUS(filepath.c_str());
    if(*track == NULL) {
        printf("Failed to load track: %s\n", Mix_GetError());
        return false;
    }
    return false;
}

// Returns true on success
bool Resources::load_font(TTF_Font **font, std::string filename, int size) {

    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "fonts/" + filename;
    *font = TTF_OpenFont(filepath.c_str(), size);
    if(*font == NULL) {
        printf("Error loading font: %s\n", TTF_GetError());
        return false;
    }
    return true;

}

// Returns true on success
bool Resources::load_texture(SDL_Texture **texture, std::string filename){

    // Assumes texture is not already created
    *texture = NULL;

    // Imagefile -> Surface -> Texture
    // Empty surface to begin with
    SDL_Surface *loaded_surface = NULL;

    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "images/" + filename;

    // Load imagefile into surface
    loaded_surface = IMG_Load(filepath.c_str());
    if(loaded_surface == NULL) {
        printf("Error loading image: %s\n", SDL_GetError());
        return false;
    }

    // If successful, transfer the surface into the texture
    *texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if(texture == NULL) {
        printf("Unable to create texture from surface: %s\n", SDL_GetError());
    }
    // Mode BLEND allows for rendering with alpha channel changes even on PNGs
    // without an alpha channel
    SDL_SetTextureBlendMode(*texture, SDL_BLENDMODE_BLEND);

    // Free the temporary surface
    SDL_FreeSurface(loaded_surface);

    return true;

}

// PUBLIC FUNCTIONS

Resources::Resources(SDL_Renderer *renderer) {
    this->renderer = renderer;
}


void Resources::load_resources(std::string json_filename) {

    // Read JSON object from resources file
    std::ifstream file(json_filename);
    json resources;
    file >> resources;

    // Load Sounds
    for (json::iterator it = resources["sounds"].begin(); it != resources["sounds"].end(); it++) {
        Mix_Chunk *sound;
        load_sound(&sound, it.value());
        sounds[it.key()] = sound;
    }

    // Load Tracks
    for (json::iterator it = resources["tracks"].begin(); it != resources["tracks"].end(); it++) {
        Mix_Music *track;
        load_track(&track, it.value());
        tracks[it.key()] = track;
    }

    // Load Fonts
    for (json::iterator it = resources["fonts"].begin(); it != resources["fonts"].end(); it++) {
        TTF_Font *font = NULL;
        load_font(&font, it.value()["filename"], it.value()["size"]);
        fonts[it.key()] = font;
    }

    // Load Textures
    for (json::iterator it = resources["textures"].begin(); it != resources["textures"].end(); it++) {
        SDL_Texture *texture;
        load_texture(&texture, it.value());
        textures[it.key()] = texture;
    }

    // Load Sprites
    for (json::iterator it = resources["sprites"].begin(); it != resources["sprites"].end(); it++) {
        for(uint i = 0; i < it.value()["frames"].size(); i++) {
            SDL_Texture *texture;
            load_texture(&texture, it.value()["frames"][i]);
            sprite_frames[it.key()].push_back(texture);
            sprite_frame_delays[it.key()].push_back(it.value()["delays"][i]);
        }
        SpriteOffset offset = {0, 0, 0, 0};
        if(it.value().find("offset_x") != it.value().end()) {
            offset.x = it.value()["offset_x"];
        }
        if(it.value().find("offset_y") != it.value().end()) {
            offset.y = it.value()["offset_y"];
        }
        if(it.value().find("offset_hflip_x") != it.value().end()) {
            offset.hflip_x = it.value()["offset_hflip_x"];
        }
        if(it.value().find("offset_hflip_y") != it.value().end()) {
            offset.hflip_y = it.value()["offset_hflip_y"];
        }
        sprite_offsets[it.key()] = offset;
    }

}

Sound Resources::get_sound(std::string name) {
    return Sound(sounds[name]);
}

Track Resources::get_track(std::string name) {
    return Track(tracks[name]);
}

TTF_Font* Resources::get_font(std::string name) {
    // TODO: Add check to see if name exists
    return fonts[name];
}

Texture Resources::get_texture(std::string name) {
    return Texture(textures[name]);
}

Sprite Resources::get_sprite(std::string name) {
    SpriteOffset offset = sprite_offsets[name];
    Sprite sprite(offset);
    if(sprite_frames[name].size() == 0) {
        printf("Error: 0 frames in sprite: %s", name.c_str());
    }
    for(uint i = 0; i < sprite_frames[name].size(); i++) {
        sprite.add_frame(Texture(sprite_frames[name][i]), sprite_frame_delays[name][i]);
    }
    return sprite;
}

Resources::~Resources() {
    
    // Iterate through fonts and free them
    std::map<std::string, TTF_Font*>::iterator font_it;
    for(font_it = fonts.begin(); font_it != fonts.end(); font_it++) {
        TTF_CloseFont(font_it->second);
    }
    
    // Iterate through textures and free them
    std::map<std::string, SDL_Texture*>::iterator texture_it;
    for(texture_it = textures.begin(); texture_it != textures.end(); texture_it++) {
        SDL_DestroyTexture(texture_it->second);
    }

    // Iterate through sprite textures and free them
    std::map<std::string, std::vector<SDL_Texture *> >::iterator sprite_it;
    for(sprite_it = sprite_frames.begin(); sprite_it != sprite_frames.end(); sprite_it++) {
        for(uint i = 0; i < sprite_it->second.size(); i++) {
            SDL_DestroyTexture(sprite_it->second[i]);
        }
    }
    
    // Iterate through sounds and free them
    std::map<std::string, Mix_Chunk*>::iterator sound_it;
    for(sound_it = sounds.begin(); sound_it != sounds.end(); sound_it++) {
        Mix_FreeChunk(sound_it->second);
    }

    // Iterate through tracks and free them
    std::map<std::string, Mix_Music*>::iterator track_it;
    for(track_it = tracks.begin(); track_it != tracks.end(); track_it++) {
        Mix_FreeMusic(track_it->second);
    }
}