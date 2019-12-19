#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <SDL2/SDL.h>

#include "./offset.h"

class Texture {

	SDL_Texture *texture;
	Offset offset;

public:

	Texture();
	Texture(SDL_Texture *texture);
	Texture(SDL_Texture *texture, Offset offset);
	void draw(SDL_Renderer *renderer, int x, int y);
	void draw(SDL_Renderer *renderer, int x, int y, float angle);
	void draw(SDL_Renderer *renderer, int x, int y, float angle, bool flip_h, bool flip_v);
	void set_offset(Offset offset);
	int get_width();
	int get_height();

};

#endif