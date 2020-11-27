#include "scene.h"
#include <iostream>

Scene::Scene(Inputs *inputs, Graphics *graphics) {
	this->inputs = inputs;
	this->graphics = graphics;
	collider = new Collider();
	delta = 0;
}


void Scene::update(float delta) {
	this->delta = delta;
	collider->check_collisions();
	for (uint i = 0; i < entities.size(); i++) {
		if (entities[i].entity->is_alive() == false) {
			delete entities[i].entity;
			entities.erase(entities.begin() + i);
			continue;
		}
		entities[i].entity->update();
	}
}


void Scene::render() {
	for (int i = entities.size() - 1; i >= 0; i--) {
		entities[i].entity->render();
	}
}


void Scene::add_entity(Entity *entity) {
	entities.push_back(EntityEntry(entity, 0));
}

void Scene::add_entity(Entity *entity, int entity_type) {
	entities.push_back(EntityEntry(entity, entity_type));
}

std::vector<Entity*> Scene::get_entities_of_type(int entity_type) {
	std::vector<Entity*> query;
	for (uint i = 0; i < entities.size(); i++) {
		if (entities[i].entity_type == entity_type) {
			query.push_back(entities[i].entity);
		}
	}
	return query;
}

Inputs *Scene::get_inputs() {
	return inputs;
}

Graphics *Scene::get_graphics() {
	return graphics;
}

Collider *Scene::get_collider() {
	return collider;
}

float Scene::get_delta() {
	return delta;
}

int Scene::get_entity_count() {
	return entities.size();
}

Scene::~Scene() {
	for(uint i = 0; i < entities.size(); i++) {
		delete entities[i].entity;
	}
}