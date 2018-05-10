#ifndef FPS_DISPLAY_H
#define FPS_DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

#include "../game/entity.h"
#include "../game/scene.h"
#include "../graphics/graphics.h"

class FPS_Display : public Entity {

	float fps;
	float update_delay_timer;
	std::string font;
	SDL_Color color;

public:

	FPS_Display(Scene *scene);
	FPS_Display(Scene *scene, std::string font, SDL_Color color);

	void update();
	void render();

};

#endif