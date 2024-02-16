// Example Game to Demonstrate Blank Screen

#include <sdlgl/game/clock.h>
#include <sdlgl/game/context.h>

int main() {

    // Load a window
    Graphics::initialize(640, 480);
    Context context(std::make_shared<Clock>());

    Graphics &graphics = Graphics::get_instance();
    Inputs &inputs = Inputs::get_instance();

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        inputs.update();
        context.clock->tick();
        graphics.clear_screen();
        graphics.present_renderer(context.clock->get_delta());
        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (inputs.get_quit()) {
            loop = false;
        }
    }

    return 0;
}
