// Example: Tilemap
// A tilemap with multiple layers is rendered

#include <sdlgl/game/context.h>
#include <sdlgl/ui/fps_display.h>
#include <sdlgl/graphics/tilemap.h>

#include <iostream>

int main() {
    Graphics::initialize(640, 480);
    Context context(std::make_shared<Clock>());
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    // Load resources
    Resources::get_instance().load_resources("resources.json");

    Tilemap tilemap = Resources::get_instance().get_tilemap("test_tilemap.json");

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
