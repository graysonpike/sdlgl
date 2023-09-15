#include "texture.h"

Texture::Texture() {}

Texture::Texture(const std::shared_ptr<SDL_Texture>& texture) { this->texture = texture; }

Texture::Texture(const std::shared_ptr<SDL_Texture>& texture, Offset offset) {
    this->texture = texture;
    this->offset = offset;
}

void Texture::draw(const std::shared_ptr<Scene>& scene, int x, int y) {
    draw(scene->get_graphics()->get_renderer(), x, y);
}

void Texture::draw(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y) {
    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    SDL_Rect dst = {x + offset.x, y + offset.y, width, height};

    SDL_RenderCopy(renderer.get(), texture.get(), nullptr, &dst);
}

void Texture::draw(const std::shared_ptr<Scene>& scene, int x, int y, float angle) {
    draw(scene->get_graphics()->get_renderer(), x, y, angle);
}

void Texture::draw(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, float angle) {
    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    SDL_Rect dst = {x + offset.x, y + offset.y, width, height};

    SDL_RenderCopyEx(renderer.get(), texture.get(), nullptr, &dst, angle / M_PI * 180, nullptr,
                     SDL_FLIP_NONE);
}

void Texture::draw(const std::shared_ptr<Scene>& scene, int x, int y, float angle, bool flip_h,
                   bool flip_v) {
    draw(scene->get_graphics()->get_renderer(), x, y, angle, flip_h, flip_v);
}

void Texture::draw(const std::shared_ptr<SDL_Renderer>& renderer, int x, int y, float angle,
                   bool flip_h, bool flip_v) {
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
    SDL_RenderCopyEx(renderer.get(), texture.get(), nullptr, &dst, angle / M_PI * 180, nullptr,
                     (SDL_RendererFlip)flip);
}

void Texture::set_offset(Offset new_offset) { this->offset = new_offset; }

int Texture::get_width() {
    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    return width;
}

int Texture::get_height() {
    int width, height;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    return height;
}