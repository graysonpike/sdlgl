#ifndef SCENE_H
#define SCENE_H

#include <vector>

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
    Graphics *graphics;
    Audio *audio;
    Inputs *inputs;
    Collider *collider;

    float delta;

    std::unordered_map<std::string, std::vector<Entity *>> entities;

   public:
    Scene(Graphics *graphics, Audio *audio, Inputs *inputs);
    void update(float delta);
    void render() const;
    void add_entity(Entity *entity);
    void add_entity(Entity *entity, const std::vector<std::string> &tags);
    const std::vector<Entity *> &get_entities_with_tag(
        const std::string &tag) const;

    Inputs *get_inputs() const;
    Graphics *get_graphics() const;
    Collider *get_collider() const;
    Audio *get_audio() const;
    float get_delta() const;
    unsigned get_entity_count() const;

    ~Scene();
};

#endif
