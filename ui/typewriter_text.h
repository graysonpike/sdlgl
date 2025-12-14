#ifndef SDLGL_TYPEWRITER_TEXT_H
#define SDLGL_TYPEWRITER_TEXT_H

#include <string>
#include <vector>

#include "../graphics/text.h"
#include "SDL.h"

class TypewriterText {
   private:
    std::string full_text;
    std::string current_text;
    std::string font;
    SDL_Color color;
    int x, y;
    int max_width;

    // Typewriter effect state
    float delay;  // delay between each character in seconds
    float timer;
    int current_char_index;
    bool is_typing;
    bool typing_complete;

    // Character width for monospace font wrapping
    float char_width;

    // Helper methods
    void calculate_character_width();
    void perform_text_wrapping();

   public:
    explicit TypewriterText();
    TypewriterText(int x, int y, const std::string& text,
                   const std::string& font, float delay = 0.1f,
                   int max_width = -1);

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
