#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <SDL2/SDL.h>
#include "./texture.h"
#include "./sprite_offset.h"


class Sprite {

	float delay;
	float frame_timer;
	float total_time;
	SpriteOffset offset;
	std::vector<Texture> frames;

	int get_frame_num(float delta);

public:

	Sprite();
	Sprite(SpriteOffset offset, float delay);
	void add_frame(Texture frame);
	void draw(SDL_Renderer *renderer, int x, int y, float delta);
	void draw(SDL_Renderer *renderer, int x, int y, float angle, bool flip_h, bool flip_v, float delta);
	int get_width();
	int get_height();
	float get_delay();
	void reset();
	void set_frame_timer(float time);
	void set_delay(float delay);

};

#endif