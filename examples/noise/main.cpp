#include <sdlgl/game/clock.h>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/utilities/noise.h>

void draw_point(SDL_Renderer *renderer, int x, int y) {
    double input_x = x * 0.01;
    double input_y = y * 0.01;
    int alpha = (int)(PerlinNoise::generate(input_x, input_y) * 255);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
    SDL_RenderDrawPoint(renderer, x, y);
}

void draw_noise(SDL_Renderer *renderer) {
    for (unsigned int i = 0; i < 640; i++) {
        for (unsigned int j = 0; j < 480; j++) {
            draw_point(renderer, i, j);
        }
    }
}

int main() {
    PerlinNoise::init();

    Clock clock;
    Inputs inputs;

    // Load a window
    Graphics graphics(640, 480);

    // Enter a simple update loop
    bool loop = true;
    while (loop) {
        inputs.update();
        clock.tick();
        graphics.clear_screen();
        draw_noise(graphics.get_renderer());
        graphics.present_renderer(clock.get_delta());
        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (inputs.get_quit()) {
            loop = false;
        }
    }

    return 0;
}