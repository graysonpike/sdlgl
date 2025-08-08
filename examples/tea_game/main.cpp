// Example: Tea Game
// A tea-themed game built on top of the tilemap system

#include <sdlgl/game/context.h>
#include <sdlgl/graphics/tilemap.h>
#include <sdlgl/ui/menu_background.h>

#include "entities/player.h"

int main() {
    Graphics::initialize(768, 640);
    Context context(std::make_shared<Clock>());
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    // Load resources
    Resources::get_instance().load_resources("resources.json");

    Tilemap room_builder_tilemap =
        Resources::get_instance().get_tilemap("room_builder");
    Tilemap furniture_tilemap =
        Resources::get_instance().get_tilemap("furniture");
    
    MenuBackground menu_background =
        Resources::get_instance().get_menu_background("default");

    // Create and add player to scene
    scene->add_entity(std::make_shared<Player>(scene, 384, 320));

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        Inputs::get_instance().update();
        context.clock->tick();
        Graphics::get_instance().clear_screen((SDL_Color){255, 255, 255, 255});

        room_builder_tilemap.draw();
        furniture_tilemap.draw();

        scene->update(context.clock->get_delta());
        scene->render();

        // Draw menu background after scene rendering
        menu_background.draw_background(0, 0, 3, 2);

        Graphics::get_instance().present_renderer(context.clock->get_delta());

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (Inputs::get_instance().get_quit()) {
            loop = false;
        }
    }

    return 0;
}
