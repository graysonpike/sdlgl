#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <SDL2/SDL.h>
#include "./texture.h"

class Sprite {

	std::vector<Texture> frames;
	std::vector<float> frame_times;
	float frame_timer;
	int current_frame;

public:

	Sprite();
	void add_frame(Texture frame, float frame_delay);
	void draw(SDL_Renderer *renderer, int x, int y, float delta);
	int get_width();
	int get_height();
	void reset();

};

#endif