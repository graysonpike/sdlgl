#include "texture.h"

Texture::Texture() {}


Texture::Texture(SDL_Texture *texture) {
    this->texture = texture;
}

void Texture::draw(SDL_Renderer *renderer, int x, int y) {

    int width, height;
    SDL_QueryTexture(this->texture, NULL, NULL, &width, &height);
    SDL_Rect dst = {
        x,
        y,
        width,
        height
    };

    SDL_RenderCopy(renderer, this->texture, NULL, &dst);
}

void Texture::draw(SDL_Renderer *renderer, int x, int y, float angle) {

    int width, height;
    SDL_QueryTexture(this->texture, NULL, NULL, &width, &height);
    SDL_Rect dst = {
        x,
        y,
        width,
        height
    };

    SDL_RenderCopyEx(renderer, texture, NULL, &dst, angle / M_PI * 180 + 90,
                 NULL, SDL_FLIP_NONE);
}

int Texture::get_width() {
    int width, height;
    SDL_QueryTexture(this->texture, NULL, NULL, &width, &height);
    return width;
}

int Texture::get_height() {
    int width, height;
    SDL_QueryTexture(this->texture, NULL, NULL, &width, &height);
    return height; 
}