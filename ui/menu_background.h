#ifndef SDLGL_MENU_BACKGROUND_H
#define SDLGL_MENU_BACKGROUND_H

#include <map>

#include "../graphics/tileset.h"

/*
 * A class to draw a menu background. Uses a tileset under the hood which should be a UI tileset.

 * The tiles vector is a list of menu tiles, in the following order:
 * - Top left corner
 * - Top center
 * - Top right corner
 * - Left center
 * - Center
 * - Right center
 * - Bottom left corner
 * - Bottom center
 * - Bottom right corner
 *
 * The tileset is drawn at the given coordinates with the top left corner of the top left "center" tile being at the coordinates.
 *
 * MenuBackgrounds are defined in resources.json.
 */
class MenuBackground {
    Tileset tileset;
    std::vector<int> tiles;

   public:
    explicit MenuBackground();
    MenuBackground(Tileset tileset, std::vector<int> tiles);
    void draw_background(int x, int y, int width_tiles, int height_tiles);
};

#endif
