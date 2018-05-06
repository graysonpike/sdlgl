// Example Game to Demonstrate Blank Screen

#include <unistd.h>
#include "../../graphics/graphics.h"
#include "../../game/clock.h"


int main() {

    Clock clock;

    // Load a window
    Graphics graphics(640, 480);

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        clock.tick();
        graphics.clear_screen();
        graphics.present_renderer(clock.get_delta());
        // If total time elapsed is longer than 5 seconds, leave the update loop
        if(clock.get_total_delta() > 5) {
            loop = false;
        }
    }

    return 0;
}
