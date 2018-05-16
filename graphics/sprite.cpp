#include "sprite.h"

Sprite::Sprite() {
	frame_timer = 0;
	current_frame = 0;
}

void Sprite::add_frame(SDL_Texture *frame, float frame_delay) {
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

	// Once current frame is determined, render it
	int texture_width, texture_height;
	SDL_QueryTexture(frames[current_frame], NULL, NULL, &texture_width, &texture_height);
	SDL_Rect dst = {
	    x,
	    y,
	    texture_width,
	    texture_height
	};

	SDL_RenderCopy(renderer, frames[current_frame], NULL, &dst);
}

void Sprite::reset() {
	frame_timer = 0;
}