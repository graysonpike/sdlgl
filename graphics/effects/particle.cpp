#include "particle.h"

#include "../../graphics/graphics.h"

Particle::Particle(const std::shared_ptr<Scene>& scene, int x, int y, int size,
                   SDL_Color color, float duration)
    : PhysicalEntity(scene, x, y, size, size), color(color), timer(duration) {
    timer.reset();
}

void Particle::render() {
    const std::shared_ptr<SDL_Renderer>& renderer =
        Graphics::get_instance().get_renderer();

    int alpha = 255 * timer.remaining();

    // Draw box
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, alpha);
    SDL_Rect box_rect = {(int)x, (int)y, w, h};
    SDL_RenderFillRect(renderer.get(), &box_rect);
}

void Particle::reset(int x, int y) {
    timer.reset();
    this->x = x;
    this->y = y;
}

bool Particle::is_finished() { return timer.is_done(); }
