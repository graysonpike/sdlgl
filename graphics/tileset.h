#ifndef TILESET_H
#define TILESET_H

#include <map>

#include "./texture.h"

class Tileset {
    Texture texture;
    int src_scale;  // in px
    int dst_scale;  // in px
    int width;      // Width in number of tiles, not px
    int height;     // Height in number of tiles
    [[nodiscard]] SDL_Point get_src_coords(int tile) const;

   public:
    explicit Tileset();
    Tileset(Texture texture, int src_scale, int dst_scale);
    void draw_tile(int x, int y, int tile);
    int get_src_scale();
    int get_dst_scale();
    int get_size();
};

#endif
