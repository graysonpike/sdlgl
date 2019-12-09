#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "entity.h"
#include "../input/inputs.h"
#include "../graphics/graphics.h"
#include "../collision/collider.h"

class Entity;
class Collider;

class Scene {

protected:

	Inputs *inputs;
	Graphics *graphics;
	Collider *collider;
	float delta;

	std::vector<Entity*> entities;

public:

	Scene(Inputs *inputs, Graphics *graphics);
	void update(float delta);
	void render();
	void add_entity(Entity *entity);

	Inputs *get_inputs();
	Graphics *get_graphics();
	Collider *get_collider();
	float get_delta();
	int get_entity_count();

	~Scene();

};

#endif
