#ifndef SDLGL_LINEAR_PARTICLE_EMITTER_H
#define SDLGL_LINEAR_PARTICLE_EMITTER_H

#include <utility>

#include "emitter.h"

class LinearParticleEmitter : public ParticleEmitter {
    int vx_min;
    int vx_max;
    int vy_min;
    int vy_max;

    std::pair<int, int> get_random_velocity();
    void new_particle();
    void reset_particle(Particle* particle);

   public:
    LinearParticleEmitter(const std::shared_ptr<Scene>& scene, int x, int y,
                          int vx_min, int vx_max, int vy_min, int vy_max,
                          std::vector<SDL_Color> colors, int quantity, int size,
                          float particle_duration = 1.0f, float lifetime = 0.0f,
                          bool emit_delay = true);
    void set_velocity(int vx_min, int vx_max, int vy_min, int vy_max);
};

#endif