#include "emitter.h"

ParticleEmitter::ParticleEmitter(const std::shared_ptr<Scene>& scene, int x,
                                 int y, std::vector<SDL_Color> colors,
                                 int quantity, int size,
                                 float particle_duration, float lifetime,
                                 bool emit_delay)
    : PhysicalEntity(scene, x, y, 0, 0),
      colors(colors),
      color_index(0),
      particle_size(size),
      particle_duration(particle_duration),
      quantity(quantity),
      life_timer(lifetime),
      emit_timer(particle_duration / (float)quantity),
      emit_delay(emit_delay) {
    if (lifetime != 0) {
        life_timer.reset();
    }
}

void ParticleEmitter::handle_emission() {
    if (!emit_delay && particles.size() == 0) {
        for (int i = 0; i < quantity; i++) {
            new_particle();
        }
        return;
    }

    if (!stopping && particles.size() < (unsigned int)quantity &&
        emit_timer.is_done()) {
        new_particle();
        emit_timer.reset();
    }
}

SDL_Color ParticleEmitter::next_color() {
    SDL_Color color = colors[color_index];
    color_index++;
    color_index = color_index % colors.size();
    return color;
}

void ParticleEmitter::stop() { stopping = true; }

void ParticleEmitter::update() {
    if (life_timer.get_duration() != 0 && life_timer.is_done()) {
        stopping = true;
    }

    handle_emission();

    for (unsigned int i = 0; i < particles.size(); i++) {
        particles[i]->update();
        if (!stopping && particles[i]->is_finished()) {
            reset_particle(particles[i]);
        }
    }

    if (stopping) {
        bool done = true;
        for (unsigned int i = 0; i < particles.size(); i++) {
            if (!particles[i]->is_finished()) {
                done = false;
            }
        }
        if (done) {
            kill();
        }
    }
}

void ParticleEmitter::render() {
    for (unsigned int i = 0; i < particles.size(); i++) {
        particles[i]->render();
    }
}

ParticleEmitter::~ParticleEmitter() {
    for (unsigned int i = 0; i < particles.size(); i++) {
        delete particles[i];
    }
}