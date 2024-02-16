#ifndef FPS_DISPLAY_H
#define FPS_DISPLAY_H

#include "SDL.h"

#include <string>

#include "../game/entity.h"
#include "../game/scene.h"
#include "../graphics/graphics.h"

class FPS_Display : public Entity {
    float fps;
    float update_delay_timer;
    std::string font;
    SDL_Color color;

   public:
    FPS_Display(const std::shared_ptr<Scene>& scene);
    FPS_Display(const std::shared_ptr<Scene>& scene, std::string font,
                SDL_Color color);

    void update() override;
    void render() override;
};

#endif