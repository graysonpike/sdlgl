#include "../../graphics/resources.h"
#include "player.h"

Player::Player(Scene *scene, int x, int y) {
	this->scene = scene;
	this->x = x;
	this->y = y;
	// Player begins facing down
	dir = 'd';
	// Set up sprites
	Resources *resources = scene->get_graphics()->get_resources();
	sprites[0] = resources->get_sprite("player_down");
}

void Player::update() {
	
}

void Player::render() {
	sprites[0].draw(scene->get_graphics()->get_renderer(), x, y, scene->get_delta());
}