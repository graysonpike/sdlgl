#ifndef PLAYER_H
#define PLAYER_H

#include "../../game/entity.h"
#include "../../game/scene.h"
#include "../../graphics/sprite.h"

class Player : public Entity {

	int x, y;
	char dir;
	Sprite sprites[5];

public:

	Player(Scene *scene, int x, int y);
	void update();
	void render();

};

#endif