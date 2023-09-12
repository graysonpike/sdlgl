#include "mover.h"

#include <sdlgl/graphics/resources.h>

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

Mover::Mover(Scene *scene, int x, int y)
    : PhysicalEntity(scene, x, y, 64, 64),
      angle(0),
      is_touched(false),
      hitbox(Hitbox(0, 0, 64, 64)) {
    Resources *resources = scene->get_graphics()->get_resources();
    texture_normal = resources->get_texture("black_box");
    texture_light = resources->get_texture("light_black_box");
    scene->get_collider()->add_hitbox(
        &hitbox, this, 0, std::vector<int>{1},
        std::bind(&Mover::collision_callback, this, _1, _2));
}

void Mover::collision_callback(Entity *entity, int type) { is_touched = true; }

void Mover::move(Inputs *inputs, float delta) {
    if (inputs->is_key_down(MOVE_UP)) {
        y -= SPEED * delta;
    } else if (inputs->is_key_down(MOVE_DOWN)) {
        y += SPEED * delta;
    }

    if (inputs->is_key_down(MOVE_LEFT)) {
        x -= SPEED * delta;
    } else if (inputs->is_key_down(MOVE_RIGHT)) {
        x += SPEED * delta;
    }

    if (inputs->is_key_down(ROTATE_CLOCK)) {
        angle += ROT_SPEED * delta;
    } else if (inputs->is_key_down(ROTATE_COUNTER)) {
        angle -= ROT_SPEED * delta;
    }
}

void Mover::update() {
    float delta = scene->get_delta();
    Inputs *inputs = scene->get_inputs();
    move(inputs, delta);
    hitbox.update_pos(x, y, angle);
}

void Mover::render() {
    SDL_Renderer *renderer = scene->get_graphics()->get_renderer();
    if (!is_touched) {
        texture_normal.draw(renderer, x, y, angle, false, false);
    } else {
        texture_light.draw(renderer, x, y, angle, false, false);
        is_touched = false;
    }
    hitbox.render_corners(renderer);
}