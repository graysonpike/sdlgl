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
	void draw(SDL_Renderer *renderer, int x, int y, float angle);
	void draw(SDL_Renderer *renderer, int x, int y, float angle, bool flip_h, bool flip_v);
	int get_width();
	int get_height();

};

#endif