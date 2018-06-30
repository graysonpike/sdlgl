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