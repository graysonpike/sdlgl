#ifndef BOX_H
#define BOX_H

#include "../../game/entity.h"
#include "../../game/scene.h"
#include "SDL.h"

class Box : public Entity {
    float x, y;
    int width, height;
    SDL_Color color;

   public:
    Box(const std::shared_ptr<Scene>& scene);
    Box(const std::shared_ptr<Scene>& scene, float x, float y, int width,
        int height, SDL_Color color);
    void update() override;
    void render() override;
};

#endif