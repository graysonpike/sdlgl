#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <SDL2/SDL.h>

class Texture {

	SDL_Texture *texture;

public:

	Texture();
	Texture(SDL_Texture *texture);
	void draw(SDL_Renderer *renderer, int x, int y);
	int get_width();
	int get_height();

};

#endif