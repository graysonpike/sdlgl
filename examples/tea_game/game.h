// Tea Game - Game class
// Encapsulates the main game loop and state management

#ifndef TEA_GAME_H
#define TEA_GAME_H

#include <sdlgl/game/context.h>
#include <sdlgl/game/game_state_manager.h>

class Game {
   private:
    std::shared_ptr<Context> context;
    GameStateManager state_manager;
    bool running;

    // Private constructor for singleton
    Game();

    void load_resources();
    void setup_initial_state();

   public:
    // Singleton access (needed for Emscripten callback)
    static Game& instance();

    // Prevent copying
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Main game loop methods
    void run();
    void main_loop();
    void shutdown();

    // Accessors
    bool is_running() const { return running; }
    std::shared_ptr<Context> get_context() const { return context; }
    GameStateManager& get_state_manager() { return state_manager; }
};

#endif
