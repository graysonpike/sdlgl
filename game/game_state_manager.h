// SDLGL - GameStateManager
// Manages a stack of game states for scene/menu transitions

#ifndef SDLGL_GAME_STATE_MANAGER_H
#define SDLGL_GAME_STATE_MANAGER_H

#include <memory>
#include <stack>
#include <vector>

#include "game_state.h"

class GameStateManager {
   private:
    std::stack<std::shared_ptr<GameState>> states;

    // Pending operations (applied at safe points to avoid mid-iteration issues)
    std::vector<std::shared_ptr<GameState>> pending_push;
    int pending_pop_count;
    std::shared_ptr<GameState> pending_change;
    bool has_pending_change;

    void apply_pending_changes();

   public:
    GameStateManager();

    // State management - changes are deferred until next update cycle
    void push(std::shared_ptr<GameState> state);
    void pop();
    void change(std::shared_ptr<GameState> state);  // Pop current, push new

    // Main loop - call these from your game loop
    void handle_input();
    void update(float delta);
    void render();

    // Query
    bool is_empty() const { return states.empty() && pending_push.empty(); }
    std::shared_ptr<GameState> current() const;
    size_t size() const { return states.size(); }
};

#endif
