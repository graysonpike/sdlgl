#ifndef COLLIDER_H
#define COLLIDER_H

#include <functional>
#include <vector>

#include "../game/entity.h"
#include "hitbox.h"

class Entity;

class Collider {
    struct HitboxInfo {
        Hitbox *hitbox;
        Entity *entity;
        int type;
        std::vector<int> targets;
        std::function<void(Entity *, int)> callback;
    };

    std::vector<HitboxInfo> hitboxes;

   public:
    void add_hitbox(Hitbox *hitbox, Entity *entity, int type,
                    std::vector<int> targets,
                    std::function<void(Entity *, int)> callback);
    void check_collisions();
};

#endif