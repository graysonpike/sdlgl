#include "rotator.h"

#include <sdlgl/graphics/resources.h>

#include <vector>

#define SIZE (8)

Rotator::Rotator(const std::shared_ptr<Scene>& scene, int x, int y, float vx,
                 float vy, float rot_speed)
    : PhysicalEntity(scene, x, y, SIZE, SIZE),
      angle(.5f),
      rot_speed(rot_speed),
      is_touched(false),
      vx(vx),
      vy(vy),
      hitbox(Hitbox(0, 0, SIZE, SIZE)) {
    Resources& resources = Resources::get_instance();
    texture_normal = resources.get_texture("red_box");
    texture_light = resources.get_texture("light_red_box");
    scene->get_collider()->add_hitbox(
        &hitbox, this, 0, std::vector<int>{0},
        std::bind(&Rotator::collision_callback, this, std::placeholders::_1,
                  std::placeholders::_2));
}

void Rotator::collision_callback(Entity* entity, int type) {
    is_touched = true;
}

void Rotator::update() {
    float delta = scene->get_delta();
    x = x + vx * delta;
    y = y + vy * delta;
    hitbox.update_pos(x, y, angle);
    angle += delta * rot_speed;
    wrap_bounds();
}

void Rotator::render() {
    if (!is_touched) {
        texture_normal.draw(x, y, angle, false, false);
    } else {
        texture_light.draw(x, y, angle, false, false);
        is_touched = false;
    }
}