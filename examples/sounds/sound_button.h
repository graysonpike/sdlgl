#include "../../game/entity.h"
#include "../../game/scene.h"

class SoundButton : public Entity {

	int x, y, width, height;
	SDL_Color color;
	SDL_Color active_color;
	Sound sound;
	SDL_Color get_lighter_color(SDL_Color color);

public:

	SoundButton(Scene *scene, int x, int y, int width, int height, SDL_Color color, std::string sound);
	void render();
	void update();
};