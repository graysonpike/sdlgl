#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <sdlgl/game/context.h>
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


void game_loop(Context context, Scene *scene) {

    context.inputs->update();
    context.clock->tick();
    context.graphics->clear_screen((SDL_Color){255, 255, 255, 255});

    scene->update(context.clock->get_delta());
    scene->render();

    context.audio->update(context.clock->get_delta());

    if (context.inputs->get_quit()) {
        *context.loop = false;
    }

    context.graphics->present_renderer(context.clock->get_delta());

}


int main() {

    srand(time(NULL));

    Context context(new Graphics(640, 480), new Audio(), new Inputs(), new Clock());
    context.graphics->get_resources()->load_resources("resources.json");
    context.graphics->set_debug_visuals(true);

    Scene *scene = new Scene(context.graphics, context.audio, context.inputs);
    scene->add_entity(new FPS_Display(
        scene, "base_text", {0, 0, 0, 255}));
    scene->add_entity(new EntityCount(
        scene, "base_text", {0, 0, 0, 255}));
    for (int i = 0; i < NUM_ROTATORS; i++) {
        SDL_Point p = rand_coord(context.graphics);
        scene->add_entity(new Rotator(scene, p.x, p.y, rand_float(-100, 100), rand_float(-100, 100), rand_float(-10, 10)));
    }

    while (*context.loop) {
        game_loop(context, scene);
    }

    return 0;
}
