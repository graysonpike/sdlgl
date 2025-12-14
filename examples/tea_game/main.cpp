// Example: Tea Game
// A tea-themed game built on top of the tilemap system

#include <sdlgl/game/context.h>
#include <sdlgl/graphics/tilemap.h>
#include <sdlgl/ui/menu_background.h>

#include "entities/player.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// Game state structure for the main loop
struct GameState {
    std::shared_ptr<Context> context;
    std::shared_ptr<Scene> scene;
    Tilemap* room_builder_tilemap;
    Tilemap* furniture_tilemap;
    MenuBackground* menu_background;
    bool running;
};

// Global game state (needed for Emscripten callback)
static GameState* g_game_state = nullptr;

void main_loop() {
    if (!g_game_state || !g_game_state->running) {
#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#endif
        return;
    }

    Inputs::get_instance().update();
    g_game_state->context->clock->tick();
    Graphics::get_instance().clear_screen((SDL_Color){255, 255, 255, 255});

    g_game_state->room_builder_tilemap->draw();
    g_game_state->furniture_tilemap->draw();

    g_game_state->scene->update(g_game_state->context->clock->get_delta());
    g_game_state->scene->render();

    // Draw menu background after scene rendering
    g_game_state->menu_background->draw_background(100, 100, 3, 2);

    Graphics::get_instance().present_renderer(
        g_game_state->context->clock->get_delta());

    // If ESC or 'X' button is pressed, leave the update loop and exit
    if (Inputs::get_instance().get_quit()) {
        g_game_state->running = false;
#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#endif
    }
}

int main() {
    Graphics::initialize(768, 640);

    // Initialize game state
    GameState game_state;
    game_state.context = std::make_shared<Context>(std::make_shared<Clock>());
    game_state.scene = std::make_shared<Scene>();
    game_state.running = true;

    // Load resources
    Resources::get_instance().load_resources("resources.json");

    // Create tilemaps and menu background on heap (pointers for game state)
    Tilemap room_builder_tilemap =
        Resources::get_instance().get_tilemap("room_builder");
    Tilemap furniture_tilemap =
        Resources::get_instance().get_tilemap("furniture");
    MenuBackground menu_background =
        Resources::get_instance().get_menu_background("default");

    game_state.room_builder_tilemap = &room_builder_tilemap;
    game_state.furniture_tilemap = &furniture_tilemap;
    game_state.menu_background = &menu_background;

    // Create and add player to scene
    game_state.scene->add_entity(
        std::make_shared<Player>(game_state.scene, 384, 320));

    // Set global pointer for callback
    g_game_state = &game_state;

#ifdef __EMSCRIPTEN__
    // Use Emscripten's main loop (0 = use requestAnimationFrame, 1 = simulate
    // infinite loop)
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    // Native main loop
    while (game_state.running) {
        main_loop();
    }
#endif

    return 0;
}
