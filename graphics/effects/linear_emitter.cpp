#include "linear_emitter.h"

#include "../../utilities/random.h"
#include "linear_particle.h"

LinearParticleEmitter::LinearParticleEmitter(
    const std::shared_ptr<Scene> &scene, int x, int y, int vx_min, int vx_max,
    int vy_min, int vy_max, std::vector<SDL_Color> colors, int quantity,
    int size, float particle_duration, float lifetime, bool emit_delay)
    : ParticleEmitter(scene, x, y, colors, quantity, size, particle_duration,
                      lifetime, emit_delay),
      vx_min(vx_min),
      vx_max(vx_max),
      vy_min(vy_min),
      vy_max(vy_max) {}

std::pair<int, int> LinearParticleEmitter::get_random_velocity() {
    int vx = Random::randint(vx_min, vx_max);
    int vy = Random::randint(vy_min, vy_max);
    float normalizing_factor =
        sqrt((vx * vx) + (vy * vy)) / (abs(vx) + abs(vy));
    vx *= normalizing_factor;
    vy *= normalizing_factor;
    return std::pair<int, int>(vx, vy);
}

void LinearParticleEmitter::new_particle() {
    std::pair<int, int> v = get_random_velocity();
    particles.push_back(new LinearParticle(scene, x, y, particle_size, v.first,
                                           v.second, next_color(),
                                           particle_duration));
}

void LinearParticleEmitter::reset_particle(Particle *particle) {
    LinearParticle *p = static_cast<LinearParticle *>(particle);
    std::pair<int, int> v = get_random_velocity();
    p->reset(x, y, v.first, v.second);
}

void LinearParticleEmitter::set_velocity(int vx_min, int vx_max, int vy_min,
                                         int vy_max) {
    this->vx_min = vx_min;
    this->vy_max = vx_max;
    this->vx_min = vy_min;
    this->vy_max = vy_max;
}