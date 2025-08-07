#include "entity.h"

Entity::Entity(const std::shared_ptr<Scene>& scene)
    : scene(scene), alive(true) {};

void Entity::kill() { alive = false; }

bool Entity::is_alive() { return this->alive; }
