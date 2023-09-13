#include "scene.h"

#include <iostream>

Scene::Scene(Graphics *graphics, Audio *audio, Inputs *inputs) {
    this->graphics = graphics;
    this->audio = audio;
    this->inputs = inputs;
    collider = new Collider();
    delta = 0;
}

void Scene::update(float delta) {
    this->delta = delta;
    collider->check_collisions();

    std::vector<Entity *> &all_entities = entities["all"];

    // Remove dead entities using the erase-remove idiom
    all_entities.erase(std::remove_if(all_entities.begin(), all_entities.end(),
                                      [](Entity *entity) {
                                          if (!entity->is_alive()) {
                                              delete entity;
                                              return true;
                                          }
                                          return false;
                                      }),
                       all_entities.end());

    for (Entity *entity : all_entities) {
        entity->update();
    }
}

void Scene::render() const {
    const std::vector<Entity *> &all_entities = get_entities_with_tag("all");
    for (Entity *entity : all_entities) {
        entity->render();
    }
}

void Scene::add_entity(Entity *entity) { entities["all"].push_back(entity); }

void Scene::add_entity(Entity *entity, const std::vector<std::string> &tags) {
    add_entity(entity);
    for (const std::string &tag : tags) {
        if (tag != "all") {
            entities[tag].push_back(entity);
        }
    }
}

const std::vector<Entity *> &Scene::get_entities_with_tag(
    const std::string &tag) const {
    auto it = entities.find(tag);
    if (it != entities.end()) {
        return it->second;
    }
    // Handle the case where the tag isn't found. You cannot return a temporary.
    static const std::vector<Entity *> empty_vector;
    return empty_vector;
}

Inputs *Scene::get_inputs() const { return inputs; }

Graphics *Scene::get_graphics() const { return graphics; }

Collider *Scene::get_collider() const { return collider; }

Audio *Scene::get_audio() const { return audio; }

float Scene::get_delta() const { return delta; }

unsigned Scene::get_entity_count() const {
    auto it = entities.find("all");
    if (it != entities.end()) {
        const std::vector<Entity *> &vec = it->second;
        return vec.size();
    }
    return 0;
}

Scene::~Scene() {
    const std::vector<Entity *> &all_entities = get_entities_with_tag("all");
    for (Entity *entity : all_entities) {
        delete entity;
    }
}