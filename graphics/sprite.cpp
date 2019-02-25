#include "sprite.h"

Sprite::Sprite() {
	frame_timer = 0;
	current_frame = 0;
}

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

	frames[current_frame].draw(renderer, x, y);
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