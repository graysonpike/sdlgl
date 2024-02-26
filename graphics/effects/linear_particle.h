#ifndef SDLGL_LINEAR_PARTICLE_H
#define SDLGL_LINEAR_PARTICLE_H

#include "particle.h"

class LinearParticle : public Particle {
    int vx;
    int vy;

   public:
    LinearParticle(const std::shared_ptr<Scene>& scene, int x, int y, int size,
                   int vx, int vy, SDL_Color color, float duration);
    void update();
    void reset(int x, int y, int vx, int vy);
};

#endif