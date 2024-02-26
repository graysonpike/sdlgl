#include "texture.h"

#include "graphics.h"

Texture::Texture() {}

Texture::Texture(const std::shared_ptr<SDL_Texture>& texture) {
    this->texture = texture;
    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
}

Texture::Texture(const std::shared_ptr<SDL_Texture>& texture, Offset offset) {
    this->texture = texture;
    this->offset = offset;
    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
}

void Texture::draw(int x, int y) {
    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    SDL_Rect dst = {x + offset.x, y + offset.y, width, height};
    SDL_RenderCopy(Graphics::get_instance().get_renderer().get(), texture.get(),
                   nullptr, &dst);
}

void Texture::draw(int x, int y, float angle) {
    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    SDL_Rect dst = {x + offset.x, y + offset.y, width, height};

    SDL_RenderCopyEx(Graphics::get_instance().get_renderer().get(),
                     texture.get(), nullptr, &dst, angle / M_PI * 180, nullptr,
                     SDL_FLIP_NONE);
}

void Texture::draw(int x, int y, float angle, bool flip_h, bool flip_v) {
    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    SDL_Rect dst;
    if (flip_h) {
        dst = {x + offset.hflip_x, y + offset.hflip_y, width, height};
    } else {
        dst = {x + offset.x, y + offset.y, width, height};
    }

    uint flip = (uint)SDL_FLIP_NONE;
    if (flip_h) {
        flip |= (uint)SDL_FLIP_HORIZONTAL;
    }
    if (flip_v) {
        flip |= (uint)SDL_FLIP_HORIZONTAL;
    }
    SDL_RenderCopyEx(Graphics::get_instance().get_renderer().get(),
                     texture.get(), nullptr, &dst, angle / M_PI * 180, nullptr,
                     (SDL_RendererFlip)flip);
}

void Texture::draw_src(int x, int y, SDL_Rect src) {
    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    SDL_Rect dst = {x + offset.x, y + offset.y, src.w, src.h};
    SDL_RenderCopy(Graphics::get_instance().get_renderer().get(), texture.get(),
                   &src, &dst);
}

void Texture::draw_src_dst(SDL_Rect src, SDL_Rect dst) {
    SDL_RenderCopy(Graphics::get_instance().get_renderer().get(), texture.get(),
                   &src, &dst);
}

void Texture::set_offset(Offset new_offset) { this->offset = new_offset; }

int Texture::get_width() const {
    return width;
}

int Texture::get_height() const {
    return height;
}
