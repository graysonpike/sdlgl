// Tea Game - Playing State implementation

#include "playing_state.h"

#include <sdlgl/graphics/graphics.h>
#include <sdlgl/graphics/resources.h>
#include <sdlgl/input/inputs.h>

#include "../entities/player.h"

PlayingState::PlayingState() : GameState("playing") {
    scene = std::make_shared<Scene>();
}

void PlayingState::on_enter() {
    // Load resources for this state
    room_builder_tilemap = std::make_unique<Tilemap>(
        Resources::get_instance().get_tilemap("room_builder"));
    furniture_tilemap = std::make_unique<Tilemap>(
        Resources::get_instance().get_tilemap("furniture"));

    // Create and add player to scene
    scene->add_entity(std::make_shared<Player>(scene, 384, 320));
}

void PlayingState::on_exit() {
    // Clean up resources if needed
    room_builder_tilemap.reset();
    furniture_tilemap.reset();
}

void PlayingState::on_pause() {
    // Game is paused (e.g., menu opened on top)
}

void PlayingState::on_resume() {
    // Game resumed (e.g., menu closed)
}

void PlayingState::handle_input() {
    // Input handling specific to playing state
    // Entity input is handled in their update() methods
}

void PlayingState::update(float delta) { scene->update(delta); }

void PlayingState::render() {
    // Clear screen with white background
    Graphics::get_instance().clear_screen((SDL_Color){255, 255, 255, 255});

    // Draw tilemaps (background layers)
    room_builder_tilemap->draw();
    furniture_tilemap->draw();

    // Render scene (entities)
    scene->render();
}
