// Example: Dialogue System Demo
// Demonstrates the TypewriterText class for creating dialogue effects

#include <sdlgl/game/clock.h>
#include <sdlgl/game/context.h>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/graphics/resources.h>
#include <sdlgl/input/inputs.h>
#include <sdlgl/ui/typewriter_text.h>
#include <iostream>

int main() {
    Graphics::initialize(800, 600);
    Context context(std::make_shared<Clock>());

    // Load resources
    Resources::get_instance().load_resources("resources.json");

    // Create a dialogue TypewriterText
    std::cout << "Before dialogue" << std::endl;
    TypewriterText dialogue(50, 200, "Welcome to the dialogue system! This demonstrates how the TypewriterText class can be used to create engaging dialogue effects in games. The text appears character by character, creating a natural reading experience.", "base_text", 0.03f, 400);
    
    // Start the dialogue
    dialogue.start();

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        Inputs::get_instance().update();
        context.clock->tick();
        Graphics::get_instance().clear_screen((SDL_Color){255, 255, 255, 255});

        // Update dialogue
         dialogue.update(context.clock->get_delta());

         // Render dialogue
         dialogue.render();

        // Instructions
        Text::draw_text_left_justified(50, 100, "Dialogue System Demo", "base_text", {0, 0, 0});
        Text::draw_text_left_justified(50, 400, "Press SPACE to restart dialogue", "base_text", {0, 100, 0});
        Text::draw_text_left_justified(50, 420, "Press ESC to exit", "base_text", {100, 0, 0});

        Graphics::get_instance().present_renderer(context.clock->get_delta());

        // Handle space bar to restart dialogue
        if (Inputs::get_instance().is_key_down_event(SDL_SCANCODE_SPACE)) {
            printf("Space bar pressed! Restarting dialogue.\n");
            dialogue.reset();
        }

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (Inputs::get_instance().get_quit()) {
            loop = false;
        }
    }

    return 0;
}
