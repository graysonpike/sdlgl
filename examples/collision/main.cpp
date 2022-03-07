#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <sdlgl/game/context.h>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/graphics/resources.h>
#include <sdlgl/game/clock.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/input/inputs.h>
#include <sdlgl/ui/fps_display.h>
#include <sdlgl/ui/entity_count.h>

#include "entities/rotator.h"
#include "entities/mover.h"


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

    // Load a window
    Context context(new Graphics(720, 640), new Audio(), new Inputs(), new Clock());
    context.graphics->get_resources()->load_resources("resources.json");
    context.graphics->set_debug_visuals(true);

    Scene *scene = new Scene(context.graphics, context.audio, context.inputs);
    
    scene->add_entity(new FPS_Display(
        scene, "base_text", (SDL_Color){0, 0, 0, 255}));
    scene->add_entity(new EntityCount(
        scene, "base_text", (SDL_Color){0, 0, 0, 255}));
    scene->add_entity(new Rotator(scene, context.graphics->get_width()/2, context.graphics->get_height()/2, 0.0f));
    scene->add_entity(new Mover(scene, 100, 100));

    while (*context.loop) {
        game_loop(context, scene);
    }

    return 0;
}
