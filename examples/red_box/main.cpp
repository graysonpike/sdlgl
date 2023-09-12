// Example: Red Box
// A simple red box moving around the screen, controlled with the arrow keys

#include <sdlgl/game/clock.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/input/inputs.h>
#include <sdlgl/ui/fps_display.h>

#include <iostream>

#include "box.h"

int main() {
    Clock clock;
    Inputs inputs;

    // Load a window
    Graphics graphics(640, 480);

    // Load resources
    graphics.get_resources()->load_resources("resources.json");

    // Create and populate scene
    Scene scene(&graphics, new Audio(), &inputs);
    scene.add_entity(new Box(&scene));
    scene.add_entity(
        new FPS_Display(&scene, "base_text", {255, 255, 255, 255}));

    graphics.set_debug_visuals(true);

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        inputs.update();
        clock.tick();
        graphics.clear_screen();

        scene.update(clock.get_delta());
        scene.render();

        graphics.present_renderer(clock.get_delta());

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (inputs.get_quit()) {
            loop = false;
        }
    }

    return 0;
}
