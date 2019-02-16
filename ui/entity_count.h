#ifndef ENTITY_COUNT_H
#define ENTITY_COUNT_H

#include <string>
#include <SDL2/SDL.h>

#include "../game/entity.h"
#include "../game/scene.h"
#include "../graphics/graphics.h"

class EntityCount : public Entity {

	float update_delay_timer;
	int entity_count;
	std::string font;
	SDL_Color color;

public:

	EntityCount(Scene *scene);
	EntityCount(Scene *scene, std::string font, SDL_Color color);

	void update();
	void render();

};

#endif