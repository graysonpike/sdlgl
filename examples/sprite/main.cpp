// Example: Sprite
// An animated character that plays a walking animation when moving

#include <iostream>
#include <sdlgl/game/context.h>
#include <sdlgl/ui/fps_display.h>
#include "player.h"

int main() {

    Graphics::initialize(640, 480);
    Context context(std::make_shared<Clock>());
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    // Load resources
    Resources::get_instance().load_resources("resources.json");

    scene->add_entity(std::make_shared<FPS_Display>(scene, "base_text", (SDL_Color){0, 0, 0, 255}));
    scene->add_entity(std::make_shared<Player>(scene, 320.0f, 240.0f));

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        Inputs::get_instance().update();
        context.clock->tick();
        Graphics::get_instance().clear_screen((SDL_Color){255, 255, 255, 255});

        scene->update(context.clock->get_delta());
        scene->render();

        Graphics::get_instance().present_renderer(context.clock->get_delta());

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (Inputs::get_instance().get_quit()) {
            loop = false;
        }
    }

    return 0;
}
