#include <fstream>
#include "../dependencies/json.hpp"
#include "resources.h"

// for convenience
using json = nlohmann::json;

// STATIC MEMBERS

const std::string Resources::RES_DIR = "res/";

// PRIVATE HELPER FUNCTIONS

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

//
// Load all font and image files into memory
// For textures, the key order is [sprite_name][frame_num]
// Example:
// load_font(&fonts["inconsolata"], "Inconsolata/Inconsolata-Regular.ttf", 18);
// load_texture(&textures["player"][1], "player/player_standing.png");
//
void Resources::load_resources(std::string json_filename) {

    // Read JSON object from resources file
    std::ifstream file(json_filename);
    json resources;
    file >> resources;

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
        for(int i = 0; i < it.value()["frames"].size(); i++) {
            SDL_Texture *texture;
            load_texture(&texture, it.value()["frames"][i]);
            sprite_frames[it.key()].push_back(texture);
            sprite_frame_delays[it.key()].push_back(it.value()["delays"][i]);
        }
    }

}

TTF_Font* Resources::get_font(std::string name) {
    // TODO: Add check to see if name exists
    return fonts[name];
}

Texture Resources::get_texture(std::string name) {
    return Texture(textures[name]);
}

Sprite Resources::get_sprite(std::string name) {
    Sprite sprite;
    if(sprite_frames[name].size() == 0) {
        printf("Error: 0 frames in sprite: %s", name.c_str());
    }
    for(int i = 0; i < sprite_frames[name].size(); i++) {
        sprite.add_frame(sprite_frames[name][i], sprite_frame_delays[name][i]);
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
        for(int i = 0; i < sprite_it->second.size(); i++) {
            SDL_DestroyTexture(sprite_it->second[i]);
        }
    }
    
}