#include <iostream>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/graphics/effects/linear_emitter.h>
#include <sdlgl/game/clock.h>
#include <sdlgl/ui/fps_display.h>
#include <sdlgl/ui/entity_count.h>


int main() {

    Clock clock;
    Inputs inputs;

    // Load a window
    Graphics graphics(640, 480);

    // Create and populate scene
    Scene scene(&inputs, &graphics);

    // Load resources
    graphics.get_resources()->load_resources("resources.json");

    std::vector<SDL_Color> explosion_colors;
    explosion_colors.push_back({50, 50, 50});
    explosion_colors.push_back({100, 100, 100});
    explosion_colors.push_back({150, 150, 150});
    explosion_colors.push_back({255, 87, 69});
    explosion_colors.push_back({255, 168, 69});
    explosion_colors.push_back({255, 209, 69});
    std::vector<SDL_Color> fire_colors;
    fire_colors.push_back({255, 87, 69});
    fire_colors.push_back({255, 168, 69});
    fire_colors.push_back({255, 209, 69});
    LinearParticleEmitter *fire = new LinearParticleEmitter(&scene, 426, 240, -20, 20, -40, -10, fire_colors, 100, 3, 1.5f);
    scene.add_entity(fire);
    scene.add_entity(new FPS_Display(
        &scene, "base_text", {0, 0, 0, 255}));
    scene.add_entity(new EntityCount(
        &scene, "base_text", {0, 0, 0, 255}));

    graphics.set_debug_visuals(true);


    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        inputs.update();
        clock.tick();
        graphics.clear_screen({255, 255, 255, 255});

        scene.update(clock.get_delta());
        scene.render();

        graphics.present_renderer(clock.get_delta());

        if (inputs.is_key_down_event(SDL_SCANCODE_SPACE)) {
            scene.add_entity(new LinearParticleEmitter(&scene, 213, 240, -100, 100, -100, 100, explosion_colors, 50, 3, 0.3f, 0.1f, false));
        }

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if(inputs.get_quit()) {
            loop = false;
        }
    }

    return 0;
}