// Example: Red Box
// A simple red box moving around the screen, controlled with the arrow keys

#include <iostream>

#include <sdlgl/game/clock.h>
#include <sdlgl/game/context.h>
#include "sound_button.h"

int main() {
    Graphics::initialize(640, 480);
    Context context(std::make_shared<Clock>());
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    Resources::get_instance().load_resources("resources.json");

    Audio::get_instance();

    scene->add_entity(std::make_shared<SoundButton>(
        scene, 91, 195, 91, 91, (SDL_Color){30, 51, 100, 255}, "select.wav"));
    scene->add_entity(std::make_shared<SoundButton>(
        scene, 273, 195, 91, 91, (SDL_Color){153, 26, 35, 255}, "cancel.wav"));
    scene->add_entity(std::make_shared<SoundButton>(
        scene, 455, 195, 91, 91, (SDL_Color){26, 119, 26, 255}, "send.wav"));

    Graphics &graphics = Graphics::get_instance();
    Inputs &inputs = Inputs::get_instance();

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        inputs.update();
        context.clock->tick();
        graphics.clear_screen((SDL_Color){255, 255, 255, 255});
        scene->update(context.clock->get_delta());
        scene->render();

        graphics.present_renderer(context.clock->get_delta());

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (inputs.get_quit()) {
            loop = false;
        }
    }

    return 0;
}
