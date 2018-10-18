#ifndef ENTITY_H
#define ENTITY_H

#include "scene.h"

class Scene;

// Class which has entities and manages an update+render loop
class Entity {

protected:

	Scene *scene;

public:

    Entity();
    Entity(Scene *scene);
    
	virtual void update()=0;
	virtual void render()=0;
	
};

#endif
