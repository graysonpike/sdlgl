// Example: Red Box
// A simple red box moving around the screen, controlled with the arrow keys

#include <iostream>

#include "../../graphics/graphics.h"
#include "../../game/clock.h"
#include "../../game/scene.h"
#include "../../input/inputs.h"
#include "../../ui/fps_display.h"

#include "sound_button.h"


int main() {

    Clock clock;
    Inputs inputs;
    Graphics graphics(640, 480);
    Scene scene(&graphics, new Audio(), &inputs);
    graphics.get_resources()->load_resources("resources.json");


    scene.add_entity(new SoundButton(
        &scene,
        91, 195, 91, 91,
        {30, 51, 100, 255},
        "select"));
    scene.add_entity(new SoundButton(
        &scene,
        273, 195, 91, 91,
        {153, 26, 35, 255},
        "cancel"));
    scene.add_entity(new SoundButton(
        &scene,
        455, 195, 91, 91,
        {26, 119, 26, 255},
        "send"));

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
        if(inputs.get_quit()) {
            loop = false;
        }

    }

    return 0;
}
