#ifndef RESOURCES_H
#define RESOURCES_H

#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "sprite.h"
#include "texture.h"

class Resources {

    static const std::string RES_DIR;
    std::map<std::string, TTF_Font*> fonts;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, std::vector<SDL_Texture *> > sprite_frames;
    std::map<std::string, std::vector<float> > sprite_frame_delays;
    SDL_Renderer *renderer;
    bool load_font(TTF_Font **font, std::string filename, int size);
    bool load_texture(SDL_Texture **texture, std::string filename);

public:

    Resources(SDL_Renderer *renderer);
    void load_resources(std::string json_filename);
    TTF_Font *get_font(std::string name);
    Texture get_texture(std::string name);
    Sprite get_sprite(std::string name);
    ~Resources();

};

#endif