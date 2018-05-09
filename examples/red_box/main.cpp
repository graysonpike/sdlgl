// Example: Red Box
// A simple red box moving around the screen, controlled with the arrow keys

#include "../../graphics/graphics.h"
#include "../../game/clock.h"
#include "../../game/scene.h"
#include "../../input/inputs.h"

#include "box.h"


int main() {

    Clock clock;
    Inputs inputs;

    // Load a window
    Graphics graphics(640, 480);

    Scene scene(&inputs, &graphics);
    scene.add_entity(new Box(&scene));

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
        if(inputs.get_quit()) {
            loop = false;
        }

    }

    return 0;
}
