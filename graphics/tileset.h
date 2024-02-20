#ifndef TILESET_H
#define TILESET_H

#include "./texture.h"

#include <map>

class Tileset {
    Texture texture;
    int src_scale; // in px
    int dst_scale; // in px
    int width;  // Width in number of tiles, not px
    SDL_Point get_src_coords(int tile);

   public:
    explicit Tileset();
    Tileset(Texture texture, int src_scale, int dst_scale);
    void draw_tile(int x, int y, int tile);
};

#endif
