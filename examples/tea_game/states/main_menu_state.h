// Tea Game - Main Menu State
// Initial menu screen with navigable options

#ifndef TEA_GAME_MAIN_MENU_STATE_H
#define TEA_GAME_MAIN_MENU_STATE_H

#include <sdlgl/game/game_state.h>
#include <sdlgl/ui/menu.h>

class MainMenuState : public GameState {
   private:
    std::unique_ptr<Menu> menu;

    void setup_menu();

   public:
    MainMenuState();

    void on_enter() override;
    void on_exit() override;

    void handle_input() override;
    void update(float delta) override;
    void render() override;
};

#endif
