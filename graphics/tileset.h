#ifndef SDLGL_TILESET_H
#define SDLGL_TILESET_H

#include <map>

#include "./texture.h"

/*
 * A class to efficiently draw a single tileset texture. Supports scaling for
 * pixel art. The tileset texture is assumed to be a grid of square tiles. Each
 * tile is `src_scale` pixels. The Tileset class uses a zero-based index to
 * address the tiles, which wraps around.
 *
 * For example, in a 5x5 tileset texture,
 * the first tile in the second row will be addressed with index 5. To easily
 * see tiles and their indices for map creation purposes, see the tileset
 * numbering utility (https://github.com/graysonpike/sdlgl-tileset-utils).
 *
 * Tilesets are defined in resources.json and during resources loading.
 */
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
