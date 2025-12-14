#include "menu_background.h"

#include <stdexcept>

MenuBackground::MenuBackground() {}

MenuBackground::MenuBackground(Tileset tileset, std::vector<int> tiles)
    : tileset(tileset), tiles(tiles) {}

void MenuBackground::draw_background(int x, int y, int width_tiles,
                                     int height_tiles) {
    // Validate tile configuration
    if (tiles.size() != 9) {
        throw std::runtime_error(
            "MenuBackground: Invalid tile configuration. Expected 9 tiles, "
            "got " +
            std::to_string(tiles.size()));
    }

    int tile_size = tileset.get_dst_scale();

    // The dimensions represent the center content area only
    // We need to add 2 tiles in each direction for the borders
    int total_width_tiles = width_tiles + 2;
    int total_height_tiles = height_tiles + 2;
    int tiles_x = total_width_tiles;
    int tiles_y = total_height_tiles;

    // Calculate the offset to position the center tile at the given coordinates
    // The center tile should be at (x, y), so we need to offset by one tile in
    // each direction
    int offset_x = x - tile_size;
    int offset_y = y - tile_size;

    for (int bg_y = 0; bg_y < tiles_y; bg_y++) {
        for (int bg_x = 0; bg_x < tiles_x; bg_x++) {
            int tile_index;

            // Determine which tile to use based on position
            if (bg_y == 0) {
                // Top row (border)
                if (bg_x == 0) {
                    tile_index = tiles[0];  // Top left corner
                } else if (bg_x == tiles_x - 1) {
                    tile_index = tiles[2];  // Top right corner
                } else {
                    tile_index = tiles[1];  // Top center
                }
            } else if (bg_y == tiles_y - 1) {
                // Bottom row (border)
                if (bg_x == 0) {
                    tile_index = tiles[6];  // Bottom left corner
                } else if (bg_x == tiles_x - 1) {
                    tile_index = tiles[8];  // Bottom right corner
                } else {
                    tile_index = tiles[7];  // Bottom center
                }
            } else {
                // Middle rows
                if (bg_x == 0) {
                    tile_index = tiles[3];  // Left center (border)
                } else if (bg_x == tiles_x - 1) {
                    tile_index = tiles[5];  // Right center (border)
                } else {
                    tile_index = tiles[4];  // Center (content area)
                }
            }

            tileset.draw_tile(offset_x + bg_x * tile_size,
                              offset_y + bg_y * tile_size, tile_index);
        }
    }
}
