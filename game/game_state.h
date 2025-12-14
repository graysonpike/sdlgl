// SDLGL - GameState base class
// Abstract base class for different game states (menus, gameplay, etc.)

#ifndef SDLGL_GAME_STATE_H
#define SDLGL_GAME_STATE_H

#include <memory>
#include <string>

// Forward declaration
class GameStateManager;

class GameState {
   protected:
    GameStateManager* state_manager;
    std::string name;

   public:
    explicit GameState(const std::string& name)
        : state_manager(nullptr), name(name) {}
    virtual ~GameState() = default;

    // Called by GameStateManager when this state is set
    void set_state_manager(GameStateManager* manager) {
        state_manager = manager;
    }

    // Lifecycle methods
    virtual void on_enter() {}   // Called when state becomes active
    virtual void on_exit() {}    // Called when state is being removed
    virtual void on_pause() {}   // Called when another state is pushed on top
    virtual void on_resume() {}  // Called when state above is popped

    // Main loop methods
    virtual void handle_input() = 0;
    virtual void update(float delta) = 0;
    virtual void render() = 0;

    // Accessors
    const std::string& get_name() const { return name; }
};

#endif
