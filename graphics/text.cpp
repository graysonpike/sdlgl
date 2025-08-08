#include "text.h"

#include "graphics.h"

Text::Text() {}

Text::~Text() {}

void Text::draw_text_left_justified(int x, int y, const std::string& text,
                                    const std::string& font, SDL_Color color, int max_width) {
    const Graphics& graphics = Graphics::get_instance();
    std::shared_ptr<SDL_Texture> text_texture =
        Graphics::load_font_texture(font, text, color, max_width);

    int texture_width, texture_height;
    SDL_QueryTexture(text_texture.get(), nullptr, nullptr, &texture_width,
                     &texture_height);

    SDL_Rect dst = {x, y, texture_width, texture_height};

    SDL_RenderCopy(graphics.get_renderer().get(), text_texture.get(), nullptr,
                   &dst);
}

void Text::draw_text_left_justified(int x, int y, const std::string& text,
                                    const std::string& font, int max_width) {
    draw_text_left_justified(x, y, text, font, (SDL_Color){0, 0, 0}, max_width);
}

void Text::draw_text_center_justified(int x, int y, const std::string& text,
                                      const std::string& font,
                                      SDL_Color color, int max_width) {
    const Graphics& graphics = Graphics::get_instance();
    std::shared_ptr<SDL_Texture> text_texture =
        Graphics::load_font_texture(font, text, color, max_width);

    int texture_width, texture_height;
    SDL_QueryTexture(text_texture.get(), nullptr, nullptr, &texture_width,
                     &texture_height);

    SDL_Rect dst = {x - (texture_width / 2), y, texture_width, texture_height};

    SDL_RenderCopy(graphics.get_renderer().get(), text_texture.get(), nullptr,
                   &dst);
}

void Text::draw_text_center_justified(int x, int y, const std::string& text,
                                      const std::string& font, int max_width) {
    draw_text_center_justified(x, y, text, font, (SDL_Color){0, 0, 0}, max_width);
}

void Text::draw_text_centered(int x, int y, const std::string& text,
                              const std::string& font, SDL_Color color, int max_width) {
    const Graphics& graphics = Graphics::get_instance();
    std::shared_ptr<SDL_Texture> text_texture =
        Graphics::load_font_texture(font, text, color, max_width);

    int texture_width, texture_height;
    SDL_QueryTexture(text_texture.get(), nullptr, nullptr, &texture_width,
                     &texture_height);

    SDL_Rect dst = {x - (texture_width / 2), y - (texture_height / 2),
                    texture_width, texture_height};

    SDL_RenderCopy(graphics.get_renderer().get(), text_texture.get(), nullptr,
                   &dst);
}