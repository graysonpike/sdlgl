// Example: Red Box
// A simple red box moving around the screen, controlled with the arrow keys

#include <iostream>

#include "../../game/clock.h"
#include "../../game/context.h"
#include "../../ui/fps_display.h"
#include "sound_button.h"

int main() {
    Context context(std::make_shared<Graphics>(640, 480),
                    std::make_shared<Audio>(), std::make_shared<Inputs>(),
                    std::make_shared<Clock>());
    std::shared_ptr<Scene> scene = std::make_shared<Scene>(
        context.graphics, context.audio, context.inputs);
    context.graphics->get_resources()->load_resources("resources.json");

    scene->add_entity(std::make_shared<SoundButton>(
        scene, 91, 195, 91, 91, (SDL_Color){30, 51, 100, 255}, "select"));
    scene->add_entity(std::make_shared<SoundButton>(
        scene, 273, 195, 91, 91, (SDL_Color){153, 26, 35, 255}, "cancel"));
    scene->add_entity(std::make_shared<SoundButton>(
        scene, 455, 195, 91, 91, (SDL_Color){26, 119, 26, 255}, "send"));

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        context.inputs->update();
        context.clock->tick();
        context.graphics->clear_screen((SDL_Color){255, 255, 255, 255});

        scene->update(context.clock->get_delta());
        scene->render();

        context.graphics->present_renderer(context.clock->get_delta());

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (context.inputs->get_quit()) {
            loop = false;
        }
    }

    return 0;
}
