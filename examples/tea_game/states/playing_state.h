// Tea Game - Playing State
// Main gameplay state with player, tilemaps, etc.

#ifndef TEA_GAME_PLAYING_STATE_H
#define TEA_GAME_PLAYING_STATE_H

#include <sdlgl/game/game_state.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/graphics/tilemap.h>
#include <sdlgl/ui/menu_background.h>

class PlayingState : public GameState {
   private:
    std::shared_ptr<Scene> scene;

    // Game resources
    std::unique_ptr<Tilemap> room_builder_tilemap;
    std::unique_ptr<Tilemap> furniture_tilemap;
    std::unique_ptr<MenuBackground> menu_background;

   public:
    PlayingState();

    void on_enter() override;
    void on_exit() override;
    void on_pause() override;
    void on_resume() override;

    void handle_input() override;
    void update(float delta) override;
    void render() override;

    std::shared_ptr<Scene> get_scene() const { return scene; }
};

#endif
