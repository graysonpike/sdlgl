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

SDL_Point rand_coord() {
    Graphics& graphics = Graphics::get_instance();
    return {rand() % graphics.get_width(), rand() % graphics.get_height()};
}

float rand_float(float min, float max) {
    return min + static_cast<float>(rand()) /
                     (static_cast<float>(RAND_MAX / (max - min)));
}

void game_loop(Context& context, std::shared_ptr<Scene>& scene) {
    Graphics& graphics = Graphics::get_instance();
    Inputs& inputs = Inputs::get_instance();
    inputs.update();
    context.clock->tick();
    graphics.clear_screen((SDL_Color){255, 255, 255, 255});

    scene->update(context.clock->get_delta());
    scene->render();

    if (inputs.get_quit()) {
        *context.loop = false;
    }

    graphics.present_renderer(context.clock->get_delta());
}

int main() {
    //    srand(time(NULL));

    // Load a window
    Graphics::initialize(720, 640);
    Context context(std::make_shared<Clock>());
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    Resources::get_instance().load_resources("resources.json");
    Graphics::get_instance().set_debug_visuals(true);

    scene->add_entity(std::make_shared<FPS_Display>(scene, "base_text",
                                                    (SDL_Color){0, 0, 0, 255}));
    scene->add_entity(std::make_shared<EntityCount>(scene, "base_text",
                                                    (SDL_Color){0, 0, 0, 255}));
    for (int i = 0; i < NUM_ROTATORS; i++) {
        SDL_Point p = rand_coord();
        scene->add_entity(std::make_shared<Rotator>(
            scene, p.x, p.y, rand_float(-100, 100), rand_float(-100, 100),
            rand_float(-10, 10)));
    }

    while (*context.loop) {
        game_loop(context, scene);
    }

    return 0;
}
