#include "player.h"

#define KEY_UP SDL_SCANCODE_UP
#define KEY_DOWN SDL_SCANCODE_DOWN
#define KEY_LEFT SDL_SCANCODE_LEFT
#define KEY_RIGHT SDL_SCANCODE_RIGHT

#define SPEED 200

Player::Player(const std::shared_ptr<Scene>& scene, float x, float y)
    : PhysicalEntity(scene, x, y, 0, 0) {
    // Player begins facing down
    dir = STANDING;
    // Set up sprites
    Resources& resources = Resources::get_instance();
    sprites[UP] = resources.get_sprite("player_up");
    sprites[DOWN] = resources.get_sprite("player_down");
    sprites[LEFT] = resources.get_sprite("player_left");
    sprites[RIGHT] = resources.get_sprite("player_right");
    standing_texture = resources.get_texture("player_standing");

    w = standing_texture.get_width();
    h = standing_texture.get_height();
}

void Player::update() {
    Inputs& inputs = Inputs::get_instance();
    float delta = scene->get_delta();
    dir = STANDING;

    if (inputs.is_key_down(KEY_UP)) {
        dir = UP;
        y -= delta * SPEED;
    }
    if (inputs.is_key_down(KEY_DOWN)) {
        dir = DOWN;
        y += delta * SPEED;
    }
    if (inputs.is_key_down(KEY_RIGHT)) {
        dir = RIGHT;
        x += delta * SPEED;
    }
    if (inputs.is_key_down(KEY_LEFT)) {
        dir = LEFT;
        x -= delta * SPEED;
    }

    clamp();
}

void Player::render() {
    if (dir == STANDING) {
        standing_texture.draw(x, y);
    } else {
        sprites[dir].draw(x, y, scene->get_delta());
    }
}
