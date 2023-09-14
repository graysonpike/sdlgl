#ifndef MOVER_H
#define MOVER_H

#include <sdlgl/collision/hitbox.h>
#include <sdlgl/game/physical_entity.h>

class Mover : public PhysicalEntity {
    float angle;
    Hitbox hitbox;
    Texture texture_normal;
    Texture texture_light;
    bool is_touched;

    void collision_callback(Entity* entity, int type);
    void move(const std::shared_ptr<Inputs>& inputs, float delta);

   public:
    Mover(const std::shared_ptr<Scene>& scene, int x, int y);
    void update();
    void render();
};

#endif