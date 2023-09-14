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

#include "entities/mover.h"
#include "entities/rotator.h"

void game_loop(Context& context, std::shared_ptr<Scene>& scene) {
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

    // Load a window
    Context context(std::make_shared<Graphics>(720, 640),
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
    scene->add_entity(
        std::make_shared<Rotator>(scene, context.graphics->get_width() / 2,
                                  context.graphics->get_height() / 2, 0.0f));
    scene->add_entity(std::make_shared<Mover>(scene, 100, 100));

    while (*context.loop) {
        game_loop(context, scene);
    }

    return 0;
}
