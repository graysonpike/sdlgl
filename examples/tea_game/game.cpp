// Tea Game - Game class implementation

#include "game.h"

#include <sdlgl/graphics/graphics.h>
#include <sdlgl/graphics/resources.h>
#include <sdlgl/input/inputs.h>

#include "states/main_menu_state.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// Static callback wrapper for Emscripten
static void emscripten_main_loop_callback() { Game::instance().main_loop(); }

Game::Game() : running(false) {
    context = std::make_shared<Context>(std::make_shared<Clock>());
}

Game& Game::instance() {
    static Game game;
    return game;
}

void Game::load_resources() {
    Resources::get_instance().load_resources("resources.json");
}

void Game::setup_initial_state() {
    // Start with the main menu
    state_manager.push(std::make_shared<MainMenuState>());
}

void Game::run() {
    Graphics::initialize(768, 640);

    load_resources();
    setup_initial_state();

    running = true;

#ifdef __EMSCRIPTEN__
    // Use Emscripten's main loop (0 = use requestAnimationFrame, 1 = simulate
    // infinite loop)
    emscripten_set_main_loop(emscripten_main_loop_callback, 0, 1);
#else
    // Native main loop
    while (running) {
        main_loop();
    }
#endif
}

void Game::main_loop() {
    if (!running) {
#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#endif
        return;
    }

    // Check if we still have states to run
    if (state_manager.is_empty()) {
        shutdown();
        return;
    }

    // Update input and timing
    Inputs::get_instance().update();
    context->clock->tick();
    float delta = context->clock->get_delta();

    // Let the current state handle everything
    state_manager.handle_input();
    state_manager.update(delta);
    state_manager.render();

    // Present frame
    Graphics::get_instance().present_renderer(delta);

    // Check for quit
    if (Inputs::get_instance().get_quit()) {
        shutdown();
    }
}

void Game::shutdown() {
    running = false;
#ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
#endif
}
