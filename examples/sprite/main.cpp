// Example: Red Box
// A simple red box moving around the screen, controlled with the arrow keys

#include <iostream>

#include "../../game/clock.h"
#include "../../game/scene.h"
#include "../../graphics/graphics.h"
#include "../../input/inputs.h"
#include "../../ui/fps_display.h"
#include "player.h"

int main() {
    Clock clock;
    Inputs inputs;

    // Load a window
    Graphics graphics(640, 480);

    // Load resources
    graphics.get_resources()->load_resources("resources.json");

    // Create and populate scene
    Scene scene(&graphics, new Audio(), &inputs);
    scene.add_entity(new Player(&scene, 320.0f, 240.0f));
    scene.add_entity(new FPS_Display(&scene, "base_text", {0, 0, 0, 255}));

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        inputs.update();
        clock.tick();
        graphics.clear_screen({255, 255, 255, 255});

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
