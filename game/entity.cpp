#include "entity.h"

Entity::Entity(Scene *scene) : scene(scene), alive(true) { alive = true; };

void Entity::kill() { alive = false; }

bool Entity::is_alive() { return this->alive; }
