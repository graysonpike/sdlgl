#include "../../graphics/resources.h"
#include "../../input/inputs.h"
#include "player.h"


#define KEY_UP      SDL_SCANCODE_UP
#define KEY_DOWN    SDL_SCANCODE_DOWN
#define KEY_LEFT    SDL_SCANCODE_LEFT
#define KEY_RIGHT   SDL_SCANCODE_RIGHT

#define SPEED 200


Player::Player(Scene *scene, int x, int y) {
	this->scene = scene;
	this->x = x;
	this->y = y;
	// Player begins facing down
	dir = STANDING;
	// Set up sprites
	Resources *resources = scene->get_graphics()->get_resources();
	sprites[UP] = resources->get_sprite("player_up");
	sprites[DOWN] = resources->get_sprite("player_down");
	sprites[LEFT] = resources->get_sprite("player_left");
	sprites[RIGHT] = resources->get_sprite("player_right");
	standing_texture = resources->get_texture("player_standing");
}

void Player::update() {
	Inputs *inputs = scene->get_inputs();
	float delta = scene->get_delta();
	this->dir = STANDING;

	if(inputs->is_key_down(KEY_UP)) {
		this->dir = UP;
		this->y -= delta * SPEED;
	}
	if(inputs->is_key_down(KEY_DOWN)) {
		this->dir = DOWN;
		this->y += delta * SPEED;
	}
	if(inputs->is_key_down(KEY_RIGHT)) {
		this->dir = RIGHT;
		this->x += delta * SPEED;
	}
	if(inputs->is_key_down(KEY_LEFT)) {
		this->dir = LEFT;
		this->x -= delta * SPEED;
	}
}

void Player::render() {
	if(dir == STANDING) {
		standing_texture.draw(scene->get_graphics()->get_renderer(), x, y);
	} else {
		sprites[dir].draw(scene->get_graphics()->get_renderer(), x, y, scene->get_delta());
	}
}