#ifndef RESOURCES_H
#define RESOURCES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <map>
#include <string>
#include <vector>

#include "../audio/sound.h"
#include "../audio/track.h"
#include "./offset.h"
#include "./sprite.h"
#include "./texture.h"

class Sprite;
class Texture;

class Resources {
    static const std::string RES_DIR;
    std::map<std::string, TTF_Font *> fonts;
    std::map<std::string, SDL_Texture *> textures;
    std::map<std::string, Offset> texture_offsets;
    std::map<std::string, std::vector<SDL_Texture *> > sprite_frames;
    std::map<std::string, Offset> sprite_offsets;
    std::map<std::string, float> sprite_frame_delays;
    std::map<std::string, Mix_Chunk *> sounds;
    std::map<std::string, Mix_Music *> tracks;
    SDL_Renderer *renderer;
    bool load_font(TTF_Font **font, std::string filename, int size);
    bool load_texture(SDL_Texture **texture, std::string filename);
    bool load_sound(Mix_Chunk **sound, std::string filename);
    bool load_track(Mix_Music **track, std::string filename);

   public:
    Resources(SDL_Renderer *renderer);
    void load_resources(std::string json_filename);
    TTF_Font *get_font(std::string name);
    Texture get_texture(std::string name);
    Sprite get_sprite(std::string name);
    Sound get_sound(std::string name);
    Track get_track(std::string name);
    ~Resources();
};

#endif