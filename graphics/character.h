#ifndef SDLGL_CHARACTER
#define SDLGL_CHARACTER

#include <string>
#include <vector>

#include "texture.h"

/*
 * A class for drawing a layered character sprite that supports multiple styles per layer. Supports both static sprites and animations.
 */
class Character {
   public:
    struct Cell {
        int row; // Zero-indexed
        int column; // Zero-indexed
    };
    struct CellRange {
        int row;
        int start_column; // Zero-indexed
        int end_column; // Zero-indexed, inclusive
    };
    struct CharacterAnimation {
        int num_frames;
        int frame_delay;
        CellRange cell_range; // Unused if `has_facing` is true
        bool has_facing;
        std::unordered_map<std::string, CellRange> cell_ranges; // Unused if `has_facing` is false. Key is `facing`.
    };
    struct CharacterSprite {
        Cell cell; // Unused if `has_facing` is true
        bool has_facing;
        std::unordered_map<std::string, Cell> cells; // // Unused if `has_facing` is false. Key is `facing`.
    };

   private:
    std::vector<std::vector<Texture> > layers; // First index is layer, second index is style
    int src_width;
    int src_height;
    int dst_width;
    int dst_height;
    std::unordered_map<std::string, CharacterAnimation> animations;
    std::unordered_map<std::string, CharacterSprite> sprites;
    std::vector<int> current_styles;
    std::string current_sprite; // Empty string represents no sprite to be drawn
    std::string current_animation; // Empty string represents no animation to be drawn
    float animation_frame_duration;
    float animation_timer;
    float animation_total_duration;

   public:
    explicit Character();
    Character(int width, int height);
    void add_layer();
    void add_layer_style(int layer, const Texture& texture);
    void set_current_sprite(std::string sprite);
    void set_current_animation(std::string animation);
    void set_style(int layer, int style);
    void next_style(int layer);
    void prev_style(int layer);
    int get_num_styles(int layer);
    void draw(int x, int y);
};

#endif