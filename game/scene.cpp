#include "scene.h"


Scene::Scene(Inputs *inputs, Graphics *graphics) {
	this->inputs = inputs;
	this->graphics = graphics;
}


void Scene::update() {
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->update();
	}
}


void Scene::render() {
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->render();
	}
}


void Scene::add_entity(Entity *entity) {
	entities.push_back(entity);
}

Inputs *Scene::get_inputs() {
	return inputs;
}

Graphics *Scene::get_graphics() {
	return graphics;
}

Scene::~Scene() {
	for(int i = 0; i < entities.size(); i++) {
		delete entities[i];
	}
}