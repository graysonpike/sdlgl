#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <unordered_map>

#include "../audio/audio.h"
#include "../collision/collider.h"
#include "../graphics/graphics.h"
#include "../input/inputs.h"
#include "entity.h"

class Entity;
class Collider;
class Graphics;

class Scene {
   protected:
    std::shared_ptr<Collider> collider;

    float delta;

    std::unordered_map<std::string, std::vector<std::shared_ptr<Entity>>>
        entities;

   public:
    Scene();
    void update(float new_delta);
    void render() const;
    void add_entity(const std::shared_ptr<Entity>& entity);
    void add_entity(const std::shared_ptr<Entity>& entity,
                    const std::vector<std::string>& tags);
    const std::vector<std::shared_ptr<Entity>>& get_entities_with_tag(
        const std::string& tag) const;

    std::shared_ptr<Collider> get_collider() const;
    float get_delta() const;
    unsigned get_entity_count() const;
};

#endif
