#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "entity.h"
#include "../input/inputs.h"
#include "../graphics/graphics.h"
#include "../collision/collider.h"

class Entity;
class Collider;
class Graphics;

struct EntityEntry
{
	Entity *entity;
	int entity_type;
	EntityEntry(Entity *entity, int entity_type) : entity(entity), entity_type(entity_type) {}
};

class Scene {

protected:

	Inputs *inputs;
	Graphics *graphics;
	Collider *collider;
	float delta;

	std::vector<EntityEntry> entities;

public:

	Scene(Inputs *inputs, Graphics *graphics);
	void update(float delta);
	void render();
	void add_entity(Entity *entity);
	void add_entity(Entity *entity, int entity_type);
	std::vector<Entity*> get_entities_of_type(int type);

	Inputs *get_inputs();
	Graphics *get_graphics();
	Collider *get_collider();
	float get_delta();
	int get_entity_count();

	~Scene();

};

#endif
