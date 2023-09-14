// Example: Red Box
// A simple red box moving around the screen, controlled with the arrow keys

#include <sdlgl/game/clock.h>
#include <sdlgl/game/context.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/input/inputs.h>
#include <sdlgl/ui/fps_display.h>

#include <iostream>

#include "box.h"

int main() {
    Context context(std::make_shared<Graphics>(640, 480),
                    std::make_shared<Audio>(), std::make_shared<Inputs>(),
                    std::make_shared<Clock>());

    // Load resources
    context.graphics->get_resources()->load_resources("resources.json");

    // Create and populate scene
    std::shared_ptr<Scene> scene = std::make_shared<Scene>(
        context.graphics, context.audio, context.inputs);
    scene->add_entity(std::make_shared<Box>(scene));
    scene->add_entity(std::make_shared<FPS_Display>(
        scene, "base_text", (SDL_Color){255, 255, 255, 255}));

    context.graphics->set_debug_visuals(true);

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        context.inputs->update();
        context.clock->tick();
        context.graphics->clear_screen();

        scene->update(context.clock->get_delta());
        scene->render();

        context.graphics->present_renderer(context.clock->get_delta());

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (context.inputs->get_quit()) {
            loop = false;
        }
    }

    return 0;
}
