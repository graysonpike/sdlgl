#include "tilemap.h"

Tilemap::Tilemap() {}

Tilemap::Tilemap(int scale, int width, int height, Tileset tileset)
    : scale(scale), width(width), height(height), tileset(tileset) {}

int Tilemap::coords_to_index(int x, int y) { return x + (y * width); }

SDL_Point Tilemap::index_to_coords(int index) {
    return (SDL_Point){index % width, index / width};
}

void Tilemap::add_layer() {
    std::vector<int> new_layer(width * height, -1);
    layers.push_back(new_layer);
}

void Tilemap::set_tile(int layer, int x, int y, int tile) {
    layers[layer][coords_to_index(x, y)] = tile;
}

int Tilemap::get_tile(int layer, int x, int y) {
    return layers[layer][coords_to_index(x, y)];
}

void Tilemap::draw() {
    for (int i = 0; i < layers.size(); i++) {
        draw(i);
    }
}

void Tilemap::draw(int layer) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            tileset.draw_tile(i * scale, j * scale,
                              layers[layer][coords_to_index(i, j)]);
        }
    }
}