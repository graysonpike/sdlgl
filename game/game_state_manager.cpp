// SDLGL - GameStateManager implementation

#include "game_state_manager.h"

GameStateManager::GameStateManager()
    : pending_pop_count(0),
      pending_change(nullptr),
      has_pending_change(false) {}

void GameStateManager::push(std::shared_ptr<GameState> state) {
    pending_push.push_back(state);
}

void GameStateManager::pop() { pending_pop_count++; }

void GameStateManager::change(std::shared_ptr<GameState> state) {
    pending_change = state;
    has_pending_change = true;
}

std::shared_ptr<GameState> GameStateManager::current() const {
    if (states.empty()) {
        return nullptr;
    }
    return states.top();
}

void GameStateManager::apply_pending_changes() {
    // Handle change operation (pop + push)
    if (has_pending_change) {
        if (!states.empty()) {
            states.top()->on_exit();
            states.pop();
        }
        if (pending_change) {
            pending_change->set_state_manager(this);
            states.push(pending_change);
            states.top()->on_enter();
        }
        pending_change = nullptr;
        has_pending_change = false;
    }

    // Handle pop operations
    while (pending_pop_count > 0 && !states.empty()) {
        states.top()->on_exit();
        states.pop();
        pending_pop_count--;

        // Resume the state that was underneath
        if (!states.empty()) {
            states.top()->on_resume();
        }
    }
    pending_pop_count = 0;

    // Handle push operations
    for (auto& state : pending_push) {
        // Pause the current state before pushing new one
        if (!states.empty()) {
            states.top()->on_pause();
        }
        state->set_state_manager(this);
        states.push(state);
        states.top()->on_enter();
    }
    pending_push.clear();
}

void GameStateManager::handle_input() {
    if (!states.empty()) {
        states.top()->handle_input();
    }
}

void GameStateManager::update(float delta) {
    // Apply any pending state changes at the start of update
    apply_pending_changes();

    if (!states.empty()) {
        states.top()->update(delta);
    }
}

void GameStateManager::render() {
    if (!states.empty()) {
        states.top()->render();
    }
}
