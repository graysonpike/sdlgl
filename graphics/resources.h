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
    std::map<std::string, std::shared_ptr<TTF_Font>> fonts;
    std::map<std::string, std::shared_ptr<SDL_Texture>> textures;
    std::map<std::string, Offset> texture_offsets;
    std::map<std::string, std::vector<std::shared_ptr<SDL_Texture>>> sprite_frames;
    std::map<std::string, Offset> sprite_offsets;
    std::map<std::string, float> sprite_frame_delays;
    std::map<std::string, std::shared_ptr<Mix_Chunk>> sounds;
    std::map<std::string, std::shared_ptr<Mix_Music>> tracks;
    std::shared_ptr<SDL_Renderer> renderer;
    static std::shared_ptr<TTF_Font> load_font(const std::string& filename, int size);
    std::shared_ptr<SDL_Texture> load_texture(const std::string& filename);
    static std::shared_ptr<Mix_Chunk>load_sound(const std::string& filename);
    static std::shared_ptr<Mix_Music>load_track(const std::string& filename);

   public:
    Resources(const std::shared_ptr<SDL_Renderer>& renderer);
    void load_resources(const std::string& json_filename);
    std::shared_ptr<TTF_Font> get_font(const std::string& name);
    Texture get_texture(const std::string& name);
    Sprite get_sprite(const std::string& name);
    Sound get_sound(const std::string& name);
    Track get_track(const std::string& name);
    std::vector<std::string> get_sounds() const;
};

#endif