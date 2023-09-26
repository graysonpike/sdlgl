// Example: Red Box
// A simple red box moving around the screen, controlled with the arrow keys

#include <iostream>
#include <sdlgl/game/context.h>
#include "player.h"

int main() {

    Graphics::get_instance().initialize(640, 480);
    Context context(std::make_shared<Clock>());
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    // Load resources
    context.graphics->get_resources()->load_resources("resources.json");

    scene->add_entity(std::make_shared<FPS_Display>(scene, "base_text",
                                                    (SDL_Color){0, 0, 0, 255}));
    scene->add_entity(std::make_shared<Player>(scene, 320.0f, 240.0f));

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        context.inputs->update();
        context.clock->tick();
        context.graphics->clear_screen({255, 255, 255, 255});

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
