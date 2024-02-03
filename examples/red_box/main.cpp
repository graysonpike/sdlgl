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
    Graphics::initialize(640, 480);
    Context context(std::make_shared<Clock>());

    Resources::get_instance().load_resources("resources.json");

    // Create and populate scene
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->add_entity(std::make_shared<Box>(scene));
    scene->add_entity(std::make_shared<FPS_Display>(
        scene, "base_text", (SDL_Color){255, 255, 255, 255}));

    Graphics& graphics = Graphics::get_instance();
    Inputs& inputs = Inputs::get_instance();
    graphics.set_debug_visuals(true);

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        inputs.update();
        context.clock->tick();
        graphics.clear_screen();

        scene->update(context.clock->get_delta());
        scene->render();

        graphics.present_renderer(context.clock->get_delta());

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (inputs.get_quit()) {
            loop = false;
        }
    }

    return 0;
}
