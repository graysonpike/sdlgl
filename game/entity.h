#ifndef SDLGL_ENTITY_H
#define SDLGL_ENTITY_H

#include <memory>

#include "scene.h"

class Scene;

// Class which has entities and manages an update+render loop
class Entity {
   protected:
    std::shared_ptr<Scene> scene;
    bool alive;

   public:
    Entity(const std::shared_ptr<Scene>& scene);

    void kill();
    bool is_alive();
    virtual void update() = 0;
    virtual void render() = 0;
    virtual ~Entity() = default;
};

#endif
