#ifndef BOX_H
#define BOX_H

#include <SDL2/SDL.h>
#include "../../game/entity.h"

#include "demo_world.h"

class Box : public Entity {

	float x, y;
	int width, height;
	SDL_Color color;

public:

	Box(DemoWorld *world);
	Box(DemoWorld *world, float x, float y, int width, int height, SDL_Color color);
	void update();
	void render();


};

#endif