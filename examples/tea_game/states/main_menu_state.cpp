// Tea Game - Main Menu State implementation

#include "main_menu_state.h"

#include <sdlgl/game/game_state_manager.h>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/graphics/resources.h>

#include "../game.h"
#include "playing_state.h"

MainMenuState::MainMenuState() : GameState("main_menu") {}

void MainMenuState::setup_menu() {
    // Get menu background from resources
    MenuBackground background =
        Resources::get_instance().get_menu_background("default");

    menu = std::make_unique<Menu>(background, "base_text");
    menu->set_title("Cozy Tea Game");

    // Add menu items with callbacks
    menu->add_item("Play", [this]() {
        state_manager->change(std::make_shared<PlayingState>());
    });

    menu->add_item("Credits", []() {
        // TODO: Show credits screen
    });

    menu->add_item("Exit", []() { Game::instance().shutdown(); });
}

void MainMenuState::on_enter() { setup_menu(); }

void MainMenuState::on_exit() { menu.reset(); }

void MainMenuState::handle_input() { menu->handle_input(); }

void MainMenuState::update(float delta) {
    // Menu animations could go here
}

void MainMenuState::render() {
    // Clear screen with a nice background color
    Graphics::get_instance().clear_screen((SDL_Color){200, 220, 240, 255});

    // Draw the menu (automatically centered)
    menu->render();
}
