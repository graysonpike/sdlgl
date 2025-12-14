// Example: Text Wrapping Demo
// Demonstrates the new text wrapping functionality in the Text class

#include <sdlgl/game/clock.h>
#include <sdlgl/game/context.h>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/graphics/resources.h>
#include <sdlgl/graphics/text.h>
#include <sdlgl/input/inputs.h>
#include <sdlgl/ui/typewriter_text.h>

int main() {
    Graphics::initialize(800, 600);
    Context context(std::make_shared<Clock>());

    // Load resources
    Resources::get_instance().load_resources("resources.json");

    // Create TypewriterText examples
    TypewriterText typewriter1(
        50, 150,
        "This is a typewriter text example without max width. It will type out "
        "character by character with a nice effect.",
        "base_text", 0.05f);
    TypewriterText typewriter2(
        50, 250,
        "This is another typewriter example with max width of 200 pixels. It "
        "will wrap the text when it reaches the limit.",
        "base_text", 0.05f, 200);

    // Start the typewriter effects
    typewriter1.start();
    typewriter2.start();

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        Inputs::get_instance().update();
        context.clock->tick();
        Graphics::get_instance().clear_screen((SDL_Color){255, 255, 255, 255});

        // Update typewriter effects
        typewriter1.update(context.clock->get_delta());
        typewriter2.update(context.clock->get_delta());

        // Example 1: Basic text without wrapping
        Text::draw_text_left_justified(
            50, 50, "This is a basic text without wrapping", "base_text");

        // Example 2: Text with wrapping (200 pixel width)
        Text::draw_text_left_justified(
            50, 100,
            "This is a longer text that will wrap to multiple lines when it "
            "exceeds the maximum width",
            "base_text", 200);

        // Example 3: Centered text with wrapping
        Text::draw_text_center_justified(
            400, 200,
            "This centered text will also wrap when it gets too long for the "
            "specified width",
            "base_text", 150);

        // Example 4: Large text with wrapping
        Text::draw_text_left_justified(
            50, 300,
            "This is a large text example that demonstrates wrapping with a "
            "different font size and color",
            "large_text", {255, 0, 0}, 250);

        // Example 5: Centered text (both horizontally and vertically) with
        // wrapping
        Text::draw_text_centered(400, 450,
                                 "This text is centered both horizontally and "
                                 "vertically and will wrap when needed",
                                 "base_text", {0, 0, 255}, 180);

        // Example 6: Very short max width to show aggressive wrapping
        Text::draw_text_left_justified(50, 500,
                                       "This text will wrap very aggressively "
                                       "due to the very short maximum width",
                                       "base_text", 80);

        // Render typewriter effects
        typewriter1.render();
        typewriter2.render();

        // Instructions
        Text::draw_text_left_justified(
            50, 400, "Press SPACE to reset typewriter effects", "base_text",
            {0, 100, 0});

        Graphics::get_instance().present_renderer(context.clock->get_delta());

        // Handle space bar to reset typewriter effects
        if (Inputs::get_instance().is_key_down_event(SDL_SCANCODE_SPACE)) {
            printf("Space bar pressed! Resetting typewriter effects.\n");
            typewriter1.reset();
            typewriter2.reset();
        }

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (Inputs::get_instance().get_quit()) {
            loop = false;
        }
    }

    return 0;
}
