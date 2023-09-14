#ifndef ENTITY_H
#define ENTITY_H

#include "scene.h"

class Scene;

// Class which has entities and manages an update+render loop
class Entity : public std::enable_shared_from_this<Entity>  {
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
