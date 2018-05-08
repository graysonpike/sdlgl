#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "./entity.h"
#include "../input/inputs.h"
#include "../graphics/graphics.h"


// Class which has entities and manages an update+render loop
class Scene {

protected:

	Inputs *inputs;
	Graphics *graphics;

	std::vector<Entity*> entities;

public:

	Scene(Inputs *inputs, Graphics *graphics);
	void update();
	void render();
	void add_entity(Entity *entity);

	Inputs *get_inputs();
	Graphics *get_graphics();

	~Scene();

};

#endif
