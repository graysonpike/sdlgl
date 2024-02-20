#include "tileset.h"

Tileset::Tileset() {}

Tileset::Tileset(Texture texture, int src_scale, int dst_scale)
    : texture(texture), src_scale(src_scale), dst_scale(dst_scale) {
    width = texture.get_width() / src_scale;
}

SDL_Point Tileset::get_src_coords(int tile) {
    return (SDL_Point){(tile % width) * src_scale, (tile / width) * src_scale};
}

void Tileset::draw_tile(int x, int y, int tile) {
    if (tile < 0) {
        return;
    }
    SDL_Point src_coords = get_src_coords(tile);
    texture.draw_src_dst(
        (SDL_Rect){src_coords.x, src_coords.y, src_scale, src_scale},
        (SDL_Rect){x, y, dst_scale, dst_scale});
}
