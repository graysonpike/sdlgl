#include "rotator.h"

#include <sdlgl/graphics/resources.h>

#include <vector>

using namespace std::placeholders;

Rotator::Rotator(const std::shared_ptr<Scene>& scene, int x, int y, float speed)
    : PhysicalEntity(scene, x, y, 64, 64),
      angle(.5f),
      speed(speed),
      is_touched(false),
      hitbox(Hitbox(0, 0, 64, 64)) {
    const std::shared_ptr<Resources>& resources = scene->get_graphics()->get_resources();
    texture_normal = resources->get_texture("red_box");
    texture_light = resources->get_texture("light_red_box");
    int hitbox_type = 0;
    std::vector<int> hitbox_targets = {1};
    scene->get_collider()->add_hitbox(
        &hitbox, this, hitbox_type, hitbox_targets,
        std::bind(&Rotator::collision_callback, this, std::placeholders::_1,
                  std::placeholders::_2));
}

void Rotator::collision_callback(Entity* entity, int type) {
    is_touched = true;
}

void Rotator::update() {
    float delta = scene->get_delta();
    hitbox.update_pos(x, y, angle);
    angle += delta * speed;
}

void Rotator::render() {
    const std::shared_ptr<SDL_Renderer>& renderer = scene->get_graphics()->get_renderer();
    if (!is_touched) {
        texture_normal.draw(renderer, x, y, angle, false, false);
    } else {
        texture_light.draw(renderer, x, y, angle, false, false);
        is_touched = false;
    }
    hitbox.render_corners(renderer);
}