#ifndef SDLGL_TEXT_H
#define SDLGL_TEXT_H

#include <string>

#include "SDL.h"

class Text {
   public:
    // Draw the given text with the top left being at (x, y)
    static void draw_text_left_justified(int x, int y, const std::string& text,
                                         const std::string& font,
                                         SDL_Color color);
    // Draw the given text with the top left being at (x, y), with black text
    // color
    static void draw_text_left_justified(int x, int y, const std::string& text,
                                         const std::string& font);
    // Draw the given text with the top center being at (x, y)
    static void draw_text_center_justified(int x, int y,
                                           const std::string& text,
                                           const std::string& font,
                                           SDL_Color color);
    // Draw the given text with the top center being at (x, y), with black text
    // color
    static void draw_text_center_justified(int x, int y,
                                           const std::string& text,
                                           const std::string& font);
    // Draw the given text with the center (horizontal and vertical) being at
    // (x, y)
    static void draw_text_centered(int x, int y, const std::string& text,
                                   const std::string& font, SDL_Color color);

   private:
    Text();
    ~Text();
};

#endif