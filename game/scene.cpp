#include "scene.h"

#include <iostream>

Scene::Scene(const std::shared_ptr<Graphics>& graphics,
             const std::shared_ptr<Audio>& audio,
             const std::shared_ptr<Inputs>& inputs)
    : graphics(graphics),
      audio(audio),
      inputs(inputs),
      collider(std::make_shared<Collider>()),
      delta(0) {}

void Scene::update(float new_delta) {
    this->delta = new_delta;
    collider->check_collisions();

    std::vector<std::shared_ptr<Entity>>& all_entities = entities["all"];

    // Remove dead entities using the erase-remove idiom
    all_entities.erase(
        std::remove_if(all_entities.begin(), all_entities.end(),
                       [](const std::shared_ptr<Entity>& entity) {
                           return !entity->is_alive();
                       }),
        all_entities.end());

    for (const std::shared_ptr<Entity>& entity : all_entities) {
        entity->update();
    }
}

void Scene::render() const {
    const std::vector<std::shared_ptr<Entity>>& all_entities =
        get_entities_with_tag("all");
    for (const std::shared_ptr<Entity>& entity : all_entities) {
        entity->render();
    }
}

void Scene::add_entity(const std::shared_ptr<Entity>& entity) {
    entities["all"].push_back(entity);
}

void Scene::add_entity(const std::shared_ptr<Entity>& entity,
                       const std::vector<std::string>& tags) {
    add_entity(entity);
    for (const std::string& tag : tags) {
        if (tag != "all") {
            entities[tag].push_back(entity);
        }
    }
}

const std::vector<std::shared_ptr<Entity>>& Scene::get_entities_with_tag(
    const std::string& tag) const {
    auto it = entities.find(tag);
    if (it != entities.end()) {
        return it->second;
    }
    // Handle the case where the tag isn't found. You cannot return a temporary.
    static const std::vector<std::shared_ptr<Entity>> empty_vector;
    return empty_vector;
}

std::shared_ptr<Inputs> Scene::get_inputs() const { return inputs; }

std::shared_ptr<Graphics> Scene::get_graphics() const { return graphics; }

std::shared_ptr<Collider> Scene::get_collider() const { return collider; }

std::shared_ptr<Audio> Scene::get_audio() const { return audio; }

float Scene::get_delta() const { return delta; }

unsigned Scene::get_entity_count() const {
    const std::vector<std::shared_ptr<Entity>> all_entities =
        get_entities_with_tag("all");
    return all_entities.size();
}
