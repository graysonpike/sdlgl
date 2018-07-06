#ifndef PLAYER_H
#define PLAYER_H

#include "../../game/entity.h"
#include "../../game/scene.h"
#include "../../graphics/sprite.h"
#include "../../graphics/texture.h"

class Player : public Entity {

	float x, y, width, height;
	enum { UP, DOWN, LEFT, RIGHT, STANDING } dir;
	Sprite sprites[4];
	Texture standing_texture;

	void clamp();

public:

	Player(Scene *scene, float x, float y);
	void update();
	void render();

};

#endif