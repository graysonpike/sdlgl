#ifndef BOX_H
#define BOX_H

#include <SDL2/SDL.h>
#include "../../game/entity.h"
#include "../../game/scene.h"

class Box : public Entity {

	float x, y;
	int width, height;
	SDL_Color color;

public:

	Box(Scene *scene);
	Box(Scene *scene, float x, float y, int width, int height, SDL_Color color);
	void update();
	void render();


};

#endif