#include "linear_particle.h"


LinearParticle::LinearParticle(Scene *scene, int x, int y, int size, int vx, int vy, SDL_Color color, float duration) :
    Particle(scene, x, y, size, color, duration),
    vx(vx), vy(vy) {}


void LinearParticle::update() {
    
    x += vx * scene->get_delta();
    y += vy * scene->get_delta();

}


void LinearParticle::reset(int x, int y, int vx, int vy) {

    Particle::reset(x, y);
    this->vx = vx;
    this->vy = vy;

}