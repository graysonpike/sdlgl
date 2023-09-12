#ifndef LINEAR_PARTICLE_H
#define LINEAR_PARTICLE_H

#include "particle.h"

class LinearParticle : public Particle {
    int vx;
    int vy;

   public:
    LinearParticle(Scene *scene, int x, int y, int size, int vx, int vy,
                   SDL_Color color, float duration);
    void update();
    void reset(int x, int y, int vx, int vy);
};

#endif