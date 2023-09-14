#ifndef ROTATOR_H
#define ROTATOR_H

#include <sdlgl/collision/hitbox.h>
#include <sdlgl/game/physical_entity.h>

class Rotator : public PhysicalEntity {
    float angle;
    float rot_speed;
    float vx, vy;
    Hitbox hitbox;
    Texture texture_normal;
    Texture texture_light;
    bool is_touched;

    void collision_callback(Entity* entity, int type);

   public:
    Rotator(const std::shared_ptr<Scene>& scene, int x, int y, float vx,
            float vy, float rot_speed);
    void update() override;
    void render() override;
};

#endif