#include "demo_world.h"


void DemoWorld::update(float delta) {
	this->delta = delta;
	Scene::update();
}

float DemoWorld::get_delta() {
	return delta;
}