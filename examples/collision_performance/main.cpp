#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <sdlgl/graphics/graphics.h>
#include <sdlgl/game/clock.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/input/inputs.h>
#include <sdlgl/ui/fps_display.h>
#include <sdlgl/ui/entity_count.h>

#include "entities/rotator.h"

#define NUM_ROTATORS (1000)


SDL_Point rand_coord(Graphics *graphics) {
    return {rand() % graphics->get_width(), rand() % graphics->get_height()};
}


float rand_float(float min, float max) {
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}


int main() {

    srand(time(NULL));

    Clock clock;
    Inputs inputs;

    // Load a window
    Graphics graphics(640, 480);

    // Load resources
    graphics.get_resources()->load_resources("resources.json");
    graphics.set_debug_visuals(true);

    // Create and populate scene
    Scene scene(&inputs, &graphics);
    scene.add_entity(new FPS_Display(
        &scene, "base_text", {0, 0, 0, 255}));
    scene.add_entity(new EntityCount(
        &scene, "base_text", {0, 0, 0, 255}));
    for (int i = 0; i < NUM_ROTATORS; i++) {
        SDL_Point p = rand_coord(&graphics);
        scene.add_entity(new Rotator(&scene, p.x, p.y, rand_float(-100, 100), rand_float(-100, 100), rand_float(-10, 10)));
    }

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
