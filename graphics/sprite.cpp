#include "sprite.h"

Sprite::Sprite() :
	frame_timer(0),
	current_frame(0) {}

Sprite::Sprite(SpriteOffset offset) : 
	frame_timer(0),
	current_frame(0),
	offset(offset) {}

void Sprite::add_frame(Texture frame, float frame_delay) {
	frames.push_back(frame);
	frame_times.push_back(frame_delay);
}

void Sprite::draw(SDL_Renderer *renderer, int x, int y, float delta) {

	// Timer to decide when to advance to the next frame
	frame_timer += delta;
	if(frame_timer >= frame_times[current_frame]) {
		current_frame ++;
		current_frame %= frames.size();
		frame_timer = 0;
	}

	frames[current_frame].draw(renderer, x + offset.x, y + offset.y);
}

void Sprite::draw(SDL_Renderer *renderer, int x, int y, float angle, bool flip_h, bool flip_v, float delta) {

	// Timer to decide when to advance to the next frame
	frame_timer += delta;
	if(frame_timer >= frame_times[current_frame]) {
		current_frame ++;
		current_frame %= frames.size();
		frame_timer = 0;
	}
	if (flip_h) {
		frames[current_frame].draw(renderer, x + offset.hflip_x, y + offset.hflip_y, angle, flip_h, flip_v);
	} else {
		frames[current_frame].draw(renderer, x + offset.x, y + offset.y, angle, flip_h, flip_v);
	}
}

int Sprite::get_width() {
	return frames[0].get_width();
}

int Sprite::get_height() {
	return frames[0].get_height();
}

void Sprite::reset() {
	frame_timer = 0;
}