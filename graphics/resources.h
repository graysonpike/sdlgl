#ifndef SDLGL_RESOURCES_H
#define SDLGL_RESOURCES_H

#include <map>
#include <string>
#include <vector>

#include "./character.h"
#include "./offset.h"
#include "./sprite.h"
#include "./texture.h"
#include "./tilemap.h"
#include "../ui/menu_background.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

class Sprite;
class Texture;

class Resources {
    static const std::string RES_DIR;
    std::map<std::string, std::shared_ptr<TTF_Font>> fonts;
    std::map<std::string, std::shared_ptr<SDL_Texture>> textures;
    std::map<std::string, Offset> texture_offsets;
    std::map<std::string, std::vector<std::shared_ptr<SDL_Texture>>>
        sprite_frames;
    std::map<std::string, Offset> sprite_offsets;
    std::map<std::string, float> sprite_frame_delays;
    std::map<std::string, Tileset> tilesets;
    std::map<std::string, Tilemap> tilemaps;
    std::map<std::string, Character> characters;
    std::map<std::string, MenuBackground> menu_backgrounds;
    static std::shared_ptr<TTF_Font> load_font(const std::string& filename,
                                               int size);
    std::shared_ptr<SDL_Texture> load_texture(const std::string& filename,
                                              bool prepend_images_path = true);
    Tilemap load_tilemap(const std::string& filename);
    Resources();

   public:
    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;
    // Static method to provide global point of access to the instance.
    static Resources& get_instance();
    void load_resources(const std::string& json_filename);
    std::shared_ptr<TTF_Font> get_font(const std::string& name);
    Texture get_texture(const std::string& name);
    Sprite get_sprite(const std::string& name);
    Character get_character(const std::string& name);
    Tileset get_tileset(const std::string& name);
    Tilemap get_tilemap(const std::string& name);
    MenuBackground get_menu_background(const std::string& name);
};

#endif