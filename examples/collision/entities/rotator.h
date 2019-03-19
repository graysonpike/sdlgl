#ifndef ROTATOR_H
#define ROTATOR_H

#include <sdlgl/game/physical_entity.h>
#include <sdlgl/collision/hitbox.h>

class Rotator : public PhysicalEntity {

	float angle;
	float speed;
	Hitbox hitbox;
	Texture texture_normal;
	Texture texture_light;
	bool is_touched;

	void collision_callback(Entity *entity, int type);

public:

	Rotator(Scene *scene, int x, int y, float speed);
	void update();
	void render();

};

#endif