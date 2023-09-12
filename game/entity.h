#ifndef ENTITY_H
#define ENTITY_H

#include "scene.h"

class Scene;

// Class which has entities and manages an update+render loop
class Entity {
   protected:
    Scene *scene;
    bool alive;

   public:
    Entity(Scene *scene);

    void kill();
    bool is_alive();
    virtual void update() = 0;
    virtual void render() = 0;
    virtual ~Entity() = default;
};

#endif
