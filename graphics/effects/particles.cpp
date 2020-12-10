#include <utility>
#include <math.h>
#include "../../utilities/random.h"
#include "../../utilities/math.h"
#include "particles.h"
#include "linear_particle.h"


Particles::Particles(Scene *scene, int x, int y,
    int vx_min, int vx_max, int vy_min, int vy_max,
    std::vector<SDL_Color> colors, int quantity, int size,
    float particle_duration, float lifetime, bool emit_delay) :
    PhysicalEntity(scene, x, y, 0, 0),
    vx_min(vx_min),
    vx_max(vx_max),
    vy_min(vy_min),
    vy_max(vy_max),
    colors(colors),
    color_index(0),
    particle_size(size),
    particle_duration(particle_duration),
    quantity(quantity),
    life_timer(lifetime),
    emit_timer(particle_duration / (float)quantity),
    emit_delay(emit_delay)
{

    if (lifetime != 0) {
        life_timer.reset();
    }

    emit_timer.reset();
    if (!emit_delay) {
        for (int i = 0; i < quantity; i++) {
            int vx;
            int vy;
            get_random_velocity(&vx, &vy);
            SDL_Color color = colors[color_index];
            color_index ++;
            color_index = color_index % colors.size();
            particles.push_back(LinearParticle(scene, x, y, particle_size, vx, vy, color, particle_duration));
            emit_timer.reset();
        }
    }

}


void Particles::set_location(int x, int y) {

    this->x = x;
    this->y = y;

}


void Particles::set_velocity(int vx_min, int vx_max, int vy_min, int vy_max) {

    this->vx_min = vx_min;
    this->vy_max = vx_max;
    this->vx_min = vy_min;
    this->vy_max = vy_max;

}


void Particles::stop() {
    stopping = true;
}


void Particles::get_random_velocity(int *vx, int *vy) {

    int _vx = Random::randint(vx_min, vx_max);
    int _vy = Random::randint(vy_min, vy_max);
    float normalizing_factor = sqrt((_vx * _vx) + (_vy * _vy)) / (abs(_vx) + abs(_vy));
    *vx = (float)(_vx * normalizing_factor);
    *vy = (float)(_vy * normalizing_factor);

}


void Particles::update() {

    if (life_timer.get_duration() != 0 && life_timer.is_done()) {
        stopping = true;
    }

    if (emit_delay) {
        if (!stopping && particles.size() < (unsigned int)quantity && emit_timer.is_done()) {
            int vx;
            int vy;
            get_random_velocity(&vx, &vy);
            SDL_Color color = colors[color_index];
            color_index ++;
            color_index = color_index % colors.size();
            particles.push_back(LinearParticle(scene, x, y, particle_size, vx, vy, color, particle_duration));
            emit_timer.reset();
        }
    }

    for (unsigned int i = 0; i < particles.size(); i++) {
        particles[i].update();
        if (!stopping && particles[i].is_finished()) {
            int vx;
            int vy;
            get_random_velocity(&vx, &vy);
            particles[i].reset(x, y, vx, vy);
        }
    }

    if (stopping) {
        bool done = true;
        for (unsigned int i = 0; i < particles.size(); i++) {
            if (!particles[i].is_finished()) {
                done = false;
            }
        }
        if (done) {
            kill();
        }
    }

}


void Particles::render() {

    for (unsigned int i = 0; i < particles.size(); i++) {
        particles[i].render();
    }

}