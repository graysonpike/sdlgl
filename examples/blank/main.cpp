// Example Game to Demonstrate Blank Screen

#include "../../graphics/graphics.h"
#include "../../game/clock.h"
#include "../../input/inputs.h"


int main() {

    Clock clock;
    Inputs inputs;

    // Load a window
    Graphics graphics(640, 480);

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        inputs.update();
        clock.tick();
        graphics.clear_screen();
        graphics.present_renderer(clock.get_delta());
        // If ESC or 'X' button is pressed, leave the update loop and exit
        if(inputs.get_quit()) {
            loop = false;
        }
    }

    return 0;
}
