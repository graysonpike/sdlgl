#ifndef SDLGL_DIALOGUE_H
#define SDLGL_DIALOGUE_H

#include <string>
#include <vector>

#include "../graphics/text.h"
#include "./menu_background.h"
#include "SDL.h"

class Dialogue {
   private:
    std::string text;
    MenuBackground background;
    int x, y;
    int width, height;

   public:
    explicit Dialogue();
    Dialogue(int x, int y, int width, int height, const std::string& text);

    void update(float delta);
    void render();

    // Control methods
    void start();
    void reset();
    void set_text(const std::string& new_text);

    // State queries
    bool is_complete() const;

};

#endif
