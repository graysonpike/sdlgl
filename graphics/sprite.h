#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <SDL2/SDL.h>
#include "./texture.h"
#include "./sprite_offset.h"


class Sprite {

	float frame_timer;
	int current_frame;
	SpriteOffset offset;
	std::vector<Texture> frames;
	std::vector<float> frame_times;

public:

	Sprite();
	Sprite(SpriteOffset offset);
	void add_frame(Texture frame, float frame_delay);
	void draw(SDL_Renderer *renderer, int x, int y, float delta);
	void draw(SDL_Renderer *renderer, int x, int y, float angle, bool flip_h, bool flip_v, float delta);
	int get_width();
	int get_height();
	void reset();

};

#endif