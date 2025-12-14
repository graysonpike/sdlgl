#include "typewriter_text.h"

#include "../graphics/graphics.h"
#include "../graphics/resources.h"
#include "../utilities/string_utils.h"
#include "SDL_ttf.h"

TypewriterText::TypewriterText()
    : full_text(""),
      current_text(""),
      font(""),
      color({0, 0, 0, 255}),
      x(0),
      y(0),
      max_width(-1),
      delay(0.1f),
      timer(0.0f),
      current_char_index(0),
      is_typing(false),
      typing_complete(false),
      char_width(0.0f) {
    calculate_character_width();
    perform_text_wrapping();
}

TypewriterText::TypewriterText(int x, int y, const std::string& text,
                               const std::string& font, float delay,
                               int max_width)
    : full_text(text),
      current_text(""),
      font(font),
      color({0, 0, 0, 255}),
      x(x),
      y(y),
      max_width(max_width),
      delay(delay),
      timer(0.0f),
      current_char_index(0),
      is_typing(false),
      typing_complete(false),
      char_width(0.0f) {
    calculate_character_width();
    perform_text_wrapping();
}

void TypewriterText::update(float delta) {
    if (!is_typing || typing_complete) {
        return;
    }

    timer += delta;

    if (timer >= delay) {
        timer = 0.0f;
        current_char_index++;

        if (current_char_index <= full_text.length()) {
            current_text = full_text.substr(0, current_char_index);
        } else {
            typing_complete = true;
            is_typing = false;
        }
    }
}

void TypewriterText::render() {
    if (current_text.empty()) {
        return;
    }
    const Graphics& graphics = Graphics::get_instance();
    // Always pass max_width = -1 to disable SDL's wrapping since we handle it
    // manually
    std::shared_ptr<SDL_Texture> text_texture =
        Graphics::load_font_texture(font, current_text, color, -1);

    if (!text_texture) {
        return;
    }

    int texture_width, texture_height;
    SDL_QueryTexture(text_texture.get(), nullptr, nullptr, &texture_width,
                     &texture_height);

    SDL_Rect dst = {x, y, texture_width, texture_height};

    SDL_RenderCopy(graphics.get_renderer().get(), text_texture.get(), nullptr,
                   &dst);
}

void TypewriterText::start() {
    is_typing = true;
    typing_complete = false;
    timer = 0.0f;
    current_char_index = 0;
    current_text = "";
}

void TypewriterText::reset() { start(); }

void TypewriterText::set_text(const std::string& new_text) {
    full_text = new_text;
    perform_text_wrapping();
    reset();
}

bool TypewriterText::is_complete() const { return typing_complete; }

/*
 * Calculate the width of a single character by rendering a test string
 * and dividing the total width by the number of characters.
 * This assumes a monospace font is being used.
 */
void TypewriterText::calculate_character_width() {
    if (font.empty()) {
        char_width = 0.0f;
        return;
    }

    // Use a test string with multiple characters to get an average width
    std::string test_string =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    std::shared_ptr<SDL_Texture> test_texture =
        Graphics::load_font_texture(font, test_string, color, -1);

    if (!test_texture) {
        char_width = 0.0f;
        return;
    }

    int texture_width, texture_height;
    SDL_QueryTexture(test_texture.get(), nullptr, nullptr, &texture_width,
                     &texture_height);

    // Calculate average character width
    char_width = static_cast<float>(texture_width) /
                 static_cast<float>(test_string.length());
}

/*
 * Perform simple text wrapping by inserting newline characters.
 * This algorithm assumes a monospace font and calculates wrapping
 * based on character count rather than pixel width.
 */
void TypewriterText::perform_text_wrapping() {
    if (max_width <= 0 || char_width <= 0.0f) {
        return;
    }

    // Calculate how many characters can fit on each line
    int chars_per_line = static_cast<int>(max_width / char_width);

    if (chars_per_line <= 0) {
        return;
    }

    std::string wrapped_text;
    std::string current_line;
    std::vector<std::string> words = StringUtils::split(full_text, ' ');

    for (const std::string& word : words) {
        // Check if adding this word would exceed the line width
        if (!current_line.empty() &&
            current_line.length() + 1 + word.length() > chars_per_line) {
            // Current line is full, start a new line
            wrapped_text += current_line + '\n';
            current_line = word;
        } else {
            // Add word to current line
            if (current_line.empty()) {
                current_line = word;
            } else {
                current_line += ' ' + word;
            }
        }
    }

    // Add the last line
    if (!current_line.empty()) {
        wrapped_text += current_line;
    }

    full_text = wrapped_text;
}
