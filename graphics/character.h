#ifndef SDLGL_CHARACTER
#define SDLGL_CHARACTER

#include <map>
#include <string>
#include <vector>

#include "texture.h"

/*
 * A class for drawing a layered character sprite that supports multiple styles
 * per layer. Supports both static sprites and animations.
 */
class Character {
   public:
    struct Cell {
        int row;     // Zero-indexed
        int column;  // Zero-indexed
    };
    struct CharacterAnimation {
        int num_frames;
        float frame_delay;
        std::unordered_map<std::string, Cell> cells;
    };
    struct CharacterSprite {
        std::unordered_map<std::string, Cell> cells;
    };

   private:
    std::vector<std::vector<Texture> >
        layers;  // First index is layer, second index is style
    int src_width = 0;
    int src_height = 0;
    int dst_width = 0;
    int dst_height = 0;
    std::unordered_map<std::string, CharacterAnimation> animations;
    std::unordered_map<std::string, CharacterSprite> sprites;
    std::vector<std::string> layer_names;
    std::vector<int> current_styles;
    std::string
        current_sprite;  // Empty string represents no sprite to be drawn
    std::string
        current_animation;  // Empty string represents no animation to be drawn
    std::string current_facing;
    float animation_timer = 0;
    float animation_total_duration = 0;

    void draw_sprite(const std::string& sprite, int x, int y);
    void draw_animation(const std::string& animation, int x, int y,
                        float delta);
    int get_frame_index(float delta);

   public:
    explicit Character();
    void add_layer(std::string layer_name);
    void add_layer_style(int layer, const Texture& texture);
    void add_sprite(std::string name, CharacterSprite sprite);
    void add_animation(std::string name, CharacterAnimation animation);
    void set_dimensions(int src_width, int src_height, int dst_width,
                        int dst_height);
    void set_current_sprite(std::string sprite);
    void set_current_animation(std::string animation, bool reset_timer = false);
    void set_style(int layer, int style);
    void next_style(int layer);
    void prev_style(int layer);
    int get_style(int layer);
    const std::vector<std::string>& get_layer_names() const;
    int get_num_styles(int layer);
    void set_facing(const std::string& facing);
    std::string get_facing();
    void draw(int x, int y, float delta);
};

#endif