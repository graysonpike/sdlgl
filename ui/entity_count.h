#ifndef SDLGL_ENTITY_COUNT_H
#define SDLGL_ENTITY_COUNT_H

#include <string>

#include "../game/entity.h"
#include "../game/scene.h"
#include "../graphics/graphics.h"
#include "SDL.h"

class EntityCount : public Entity {
    float update_delay_timer;
    unsigned entity_count;
    std::string font;
    SDL_Color color;

   public:
    EntityCount(std::shared_ptr<Scene>& scene);
    EntityCount(std::shared_ptr<Scene>& scene, std::string font,
                SDL_Color color);

    void update() override;
    void render() override;
};

#endif