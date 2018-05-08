// Example: Red Box
// A simple red box moving around the screen, controlled with WASD

#include "../../graphics/graphics.h"
#include "../../game/clock.h"
#include "../../input/inputs.h"

#include "demo_world.h"
#include "box.h"


int main() {

    Clock clock;
    Inputs inputs;

    // Load a window
    Graphics graphics(640, 480);

    DemoWorld world(&inputs, &graphics);
    world.add_entity(new Box(&world));

    // Enter a simple update loop
    bool loop = true;
    while (loop) {

        inputs.update();
        clock.tick();
        graphics.clear_screen();

        world.update(clock.get_delta());
        world.render();

        graphics.present_renderer(clock.get_delta());

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if(inputs.get_quit()) {
            loop = false;
        }

    }

    return 0;
}
