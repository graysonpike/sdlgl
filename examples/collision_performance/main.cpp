#include <sdlgl/game/clock.h>
#include <sdlgl/game/context.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/input/inputs.h>
#include <sdlgl/ui/entity_count.h>
#include <sdlgl/ui/fps_display.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

#include "entities/rotator.h"

#define NUM_ROTATORS (1000)

SDL_Point rand_coord(const std::shared_ptr<Graphics> graphics) {
    return {rand() % graphics->get_width(), rand() % graphics->get_height()};
}

float rand_float(float min, float max) {
    return min + static_cast<float>(rand()) /
                     (static_cast<float>(RAND_MAX / (max - min)));
}

void game_loop(const Context& context, const std::shared_ptr<Scene>& scene) {
    context.inputs->update();
    context.clock->tick();
    context.graphics->clear_screen((SDL_Color){255, 255, 255, 255});

    scene->update(context.clock->get_delta());
    scene->render();

    context.audio->update(context.clock->get_delta());

    if (context.inputs->get_quit()) {
        *context.loop = false;
    }

    context.graphics->present_renderer(context.clock->get_delta());
}

int main() {
    srand(time(NULL));

    Context context(std::make_shared<Graphics>(640, 480),
                    std::make_shared<Audio>(), std::make_shared<Inputs>(),
                    std::make_shared<Clock>());
    context.graphics->get_resources()->load_resources("resources.json");
    context.graphics->set_debug_visuals(true);

    std::shared_ptr<Scene> scene = std::make_shared<Scene>(
        context.graphics, context.audio, context.inputs);
    scene->add_entity(std::make_shared<FPS_Display>(scene, "base_text",
                                                    (SDL_Color){0, 0, 0, 255}));
    scene->add_entity(std::make_shared<EntityCount>(scene, "base_text",
                                                    (SDL_Color){0, 0, 0, 255}));
    for (int i = 0; i < NUM_ROTATORS; i++) {
        SDL_Point p = rand_coord(context.graphics);
        scene->add_entity(std::make_shared<Rotator>(
            scene, p.x, p.y, rand_float(-100, 100), rand_float(-100, 100),
            rand_float(-10, 10)));
    }

    while (*context.loop) {
        game_loop(context, scene);
    }

    return 0;
}
