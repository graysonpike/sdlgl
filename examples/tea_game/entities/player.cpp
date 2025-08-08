#include "player.h"

#include <sdlgl/graphics/resources.h>
#include <sdlgl/input/inputs.h>
#include <iostream>

#define MOVE_UP SDL_SCANCODE_W
#define MOVE_DOWN SDL_SCANCODE_S
#define MOVE_LEFT SDL_SCANCODE_A
#define MOVE_RIGHT SDL_SCANCODE_D
#define SPEED 150.0f

Player::Player(const std::shared_ptr<Scene>& scene, int x, int y)
    : PhysicalEntity(scene, x, y, 32, 32),
      current_direction(STANDING),
      is_moving(false),
      speed(SPEED) {
    
    // Get character from resources
    Resources& resources = Resources::get_instance();
    character = resources.get_character("adult_character");
    
    // Set initial facing and animation
    character.set_facing("down");
    character.set_current_animation("idle");
    
    // Set specific layer styles by index
    character.set_style(0, 1);   // Bodies = 1
    character.set_style(1, 0);   // Eyes = 0
    character.set_style(2, 31);  // Outfits = 31
    character.set_style(3, 2);  // Hairstyles = 2
}

void Player::handle_input() {
    Inputs& inputs = Inputs::get_instance();
    float delta = scene->get_delta();
    
    Direction new_direction = STANDING;
    is_moving = false;
    
    // Handle movement input
    if (inputs.is_key_down(MOVE_UP)) {
        y -= speed * delta;
        new_direction = UP;
        is_moving = true;
    } else if (inputs.is_key_down(MOVE_DOWN)) {
        y += speed * delta;
        new_direction = DOWN;
        is_moving = true;
    }
    
    if (inputs.is_key_down(MOVE_LEFT)) {
        x -= speed * delta;
        new_direction = LEFT;
        is_moving = true;
    } else if (inputs.is_key_down(MOVE_RIGHT)) {
        x += speed * delta;
        new_direction = RIGHT;
        is_moving = true;
    }
    
    // Update direction if it changed
    if (new_direction != current_direction) {
        current_direction = new_direction;
        update_facing();
        update_animation();
    } else if (!is_moving && current_direction != STANDING) {
        current_direction = STANDING;
        update_animation();
    }
}

void Player::update_facing() {
    switch (current_direction) {
        case UP:
            character.set_facing("up");
            break;
        case DOWN:
            character.set_facing("down");
            break;
        case LEFT:
            character.set_facing("left");
            break;
        case RIGHT:
            character.set_facing("right");
            break;
        case STANDING:
            // Keep current facing when standing
            break;
    }
}

void Player::update_animation() {
    if (is_moving) {
        character.set_current_animation("walking");
    } else {
        character.set_current_animation("idle");
    }
}

void Player::update() {
    handle_input();
}

void Player::render() {
    character.draw(x, y, scene->get_delta());
}
