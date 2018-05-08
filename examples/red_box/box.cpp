#include "box.h"
#include "../../graphics/graphics.h"

#define DEFAULT_WIDTH  64
#define DEFAULT_HEIGHT 64

#define DEFAULT_R 255
#define DEFAULT_G 0
#define DEFAULT_B 0
#define DEFAULT_A 255

#define KEY_UP      SDL_SCANCODE_UP
#define KEY_DOWN    SDL_SCANCODE_DOWN
#define KEY_LEFT    SDL_SCANCODE_LEFT
#define KEY_RIGHT   SDL_SCANCODE_RIGHT

#define SPEED 100

Box::Box(DemoWorld *world, float x, float y, int width, int height, SDL_Color color) {
	this->scene = world;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->color = color;
}

Box::Box(DemoWorld *world) {
	this->scene = world;
	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;
	// Position box in the middle of the window
	this->x = world->get_graphics()->get_width()/2.0 - width/2.0;
	this->y = world->get_graphics()->get_height()/2.0 - height/2.0;
	this->color = {DEFAULT_R, DEFAULT_G, DEFAULT_B, DEFAULT_A};
}

void Box::update() {
	DemoWorld *world = (DemoWorld*)scene;
	Inputs *inputs = scene->get_inputs();

	if(inputs->is_key_down(KEY_UP)) {
		y -= SPEED * world->get_delta();
	}

	if(inputs->is_key_down(KEY_DOWN)) {
		y += SPEED * world->get_delta();
	}

	if(inputs->is_key_down(KEY_LEFT)) {
		x -= SPEED * world->get_delta();
	}

	if(inputs->is_key_down(KEY_RIGHT)) {
		x += SPEED * world->get_delta();
	}
}

void Box::render() {
	SDL_Renderer *renderer = scene->get_graphics()->get_renderer();

	// Draw box
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect box_rect = {(int)x, (int)y, width, height};
	SDL_RenderDrawRect(renderer, &box_rect);

}
