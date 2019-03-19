#ifndef MOVER_H
#define MOVER_H

#include <sdlgl/game/physical_entity.h>
#include <sdlgl/collision/hitbox.h>

class Mover : public PhysicalEntity {

	float angle;
	Hitbox hitbox;
	Texture texture_normal;
	Texture texture_light;
	bool is_touched;

	void collision_callback(Entity *entity, int type);
	void move(Inputs *inputs, float delta);

public:

	Mover(Scene *scene, int x, int y);
	void update();
	void render();

};

#endif