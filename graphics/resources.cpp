#include "resources.h"

#include <iostream>

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
void Resources::load_resources() {

    // FONTS
    load_font(&fonts["inconsolata"], "Inconsolata/Inconsolata-Regular.ttf", 18);

    // TEXTURES
    load_texture(&textures["ship1"][1], "ship1/ship1.png");

}

TTF_Font* Resources::get_font(std::string name) {
    return fonts[name];
}

SDL_Texture* Resources::get_texture(std::string name, int frame) {
    return textures[name][frame];
}

Resources::~Resources() {
    
    // Iterate through fonts and free them
    std::map<std::string, TTF_Font*>::iterator font_it;
    for(font_it = fonts.begin(); font_it != fonts.end(); font_it++) {
        TTF_CloseFont(font_it->second);
    }
    
    // Iterate through textures and free them
    std::map<std::string, std::map<int, SDL_Texture*> >::iterator frames;
    for(frames = textures.begin(); frames != textures.end(); frames++) {
        std::map<int, SDL_Texture*>::iterator frame;
        for(frame = frames->second.begin(); frame != frames->second.end(); frame++) {
            //SDL_DestroyTexture(frame->second);
            frame->second = NULL;
        }
    }
    
}