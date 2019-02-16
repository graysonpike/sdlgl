#include "scene.h"
#include <iostream>

Scene::Scene(Inputs *inputs, Graphics *graphics) {
	this->inputs = inputs;
	this->graphics = graphics;
	delta = 0;
}


void Scene::update(float delta) {
	this->delta = delta;
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->is_alive() == false) {
			entities.erase(entities.begin() + i);
			continue;
		}
		entities[i]->update();
	}
}


void Scene::render() {
	for (int i = entities.size() - 1; i >= 0; i--) {
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

float Scene::get_delta() {
	return delta;
}

int Scene::get_entity_count() {
	return entities.size();
}

Scene::~Scene() {
	for(int i = 0; i < entities.size(); i++) {
		delete entities[i];
	}
}