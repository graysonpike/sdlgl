#include "mover.h"

#include <sdlgl/graphics/resources.h>
#include <sdlgl/input/inputs.h>

#include <functional>
#include <vector>

#define MOVE_UP SDL_SCANCODE_W
#define MOVE_DOWN SDL_SCANCODE_S
#define MOVE_LEFT SDL_SCANCODE_A
#define MOVE_RIGHT SDL_SCANCODE_D
#define ROTATE_CLOCK SDL_SCANCODE_E
#define ROTATE_COUNTER SDL_SCANCODE_Q
#define SPEED (100.0f)
#define ROT_SPEED (1.0f)

using namespace std::placeholders;

Mover::Mover(const std::shared_ptr<Scene>& scene, int x, int y)
    : PhysicalEntity(scene, x, y, 64, 64),
      angle(0),
      is_touched(false),
      hitbox(Hitbox(0, 0, 64, 64)) {
    Resources& resources = Resources::get_instance();
    texture_normal = resources.get_texture("black_box");
    texture_light = resources.get_texture("light_black_box");
    int hitbox_type = 1;
    std::vector<int> hitbox_targets = {0};
    scene->get_collider()->add_hitbox(
        &hitbox, this, hitbox_type, hitbox_targets,
        std::bind(&Mover::collision_callback, this, std::placeholders::_1,
                  std::placeholders::_2));
}

void Mover::collision_callback(Entity* entity, int type) { is_touched = true; }

void Mover::move() {
    float delta = scene->get_delta();
    Inputs& inputs = Inputs::get_instance();
    if (inputs.is_key_down(MOVE_UP)) {
        y -= SPEED * delta;
    } else if (inputs.is_key_down(MOVE_DOWN)) {
        y += SPEED * delta;
    }

    if (inputs.is_key_down(MOVE_LEFT)) {
        x -= SPEED * delta;
    } else if (inputs.is_key_down(MOVE_RIGHT)) {
        x += SPEED * delta;
    }

    if (inputs.is_key_down(ROTATE_CLOCK)) {
        angle += ROT_SPEED * delta;
    } else if (inputs.is_key_down(ROTATE_COUNTER)) {
        angle -= ROT_SPEED * delta;
    }
}

void Mover::update() {
    move();
    hitbox.update_pos(x, y, angle);
}

void Mover::render() {
    if (!is_touched) {
        texture_normal.draw(x, y, angle, false, false);
    } else {
        texture_light.draw(x, y, angle, false, false);
        is_touched = false;
    }
    hitbox.render_corners();
}