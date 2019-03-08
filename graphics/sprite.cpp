#include "sprite.h"

Sprite::Sprite() :
	delay(0),
	frame_timer(0),
	total_time(0) {}

Sprite::Sprite(SpriteOffset offset, float delay) : 
	delay(delay),
	frame_timer(0),
	total_time(0),
	offset(offset) {}

void Sprite::add_frame(Texture frame) {
	frames.push_back(frame);
	total_time = frames.size() * delay;
}

int Sprite::get_frame_num(float delta) {
	while (frame_timer > total_time) {
		frame_timer -= total_time;
	}
	int frame = (int)(frame_timer / total_time * frames.size());
	frame_timer += delta;
	return frame;
}

void Sprite::draw(SDL_Renderer *renderer, int x, int y, float delta) {

	int current_frame = get_frame_num(delta);

	frames[current_frame].draw(renderer, x + offset.x, y + offset.y);
}

void Sprite::draw(SDL_Renderer *renderer, int x, int y, float angle, bool flip_h, bool flip_v, float delta) {

	int current_frame = get_frame_num(delta);

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