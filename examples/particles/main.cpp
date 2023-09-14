#include <sdlgl/game/clock.h>
#include <sdlgl/game/context.h>
#include <sdlgl/graphics/effects/linear_emitter.h>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/ui/entity_count.h>
#include <sdlgl/ui/fps_display.h>

#include <iostream>

class ParticleExample {
    std::vector<SDL_Color> fire_colors;
    std::vector<SDL_Color> explosion_colors;

    void game_loop(Context context, const std::shared_ptr<Scene>& scene) {
        if (context.inputs->is_key_down_event(SDL_SCANCODE_SPACE)) {
            scene->add_entity(std::make_shared<LinearParticleEmitter>(
                scene, 213, 240, -100, 100, -100, 100, explosion_colors, 50, 3,
                0.3f, 0.1f, false));
        }

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

   public:
    int start() {
        Context context(std::make_shared<Graphics>(640, 480),
                        std::make_shared<Audio>(), std::make_shared<Inputs>(),
                        std::make_shared<Clock>());
        std::shared_ptr<Scene> scene = std::make_shared<Scene>(
            context.graphics, context.audio, context.inputs);
        context.graphics->get_resources()->load_resources("resources.json");

        explosion_colors.push_back((SDL_Color){50, 50, 50});
        explosion_colors.push_back((SDL_Color){100, 100, 100});
        explosion_colors.push_back((SDL_Color){150, 150, 150});
        explosion_colors.push_back((SDL_Color){255, 87, 69});
        explosion_colors.push_back((SDL_Color){255, 168, 69});
        explosion_colors.push_back((SDL_Color){255, 209, 69});

        fire_colors.push_back((SDL_Color){255, 87, 69});
        fire_colors.push_back((SDL_Color){255, 168, 69});
        fire_colors.push_back((SDL_Color){255, 209, 69});
        std::shared_ptr<LinearParticleEmitter> fire =
            std::make_shared<LinearParticleEmitter>(
                scene, 426, 240, -20, 20, -40, -10, fire_colors, 100, 3, 1.5f);
        scene->add_entity(fire);
        scene->add_entity(std::make_shared<FPS_Display>(
            scene, "base_text", (SDL_Color){0, 0, 0, 255}));
        scene->add_entity(std::make_shared<EntityCount>(
            scene, "base_text", (SDL_Color){0, 0, 0, 255}));

        context.graphics->set_debug_visuals(true);

        while (*context.loop) {
            game_loop(context, scene);
        }

        return 0;
    }
};

int main() {
    ParticleExample program = ParticleExample();
    return program.start();
}