#ifndef PARTICLE_H
#define PARTICLE_H

#include "../../game/physical_entity.h"
#include "../../game/timer.h"


class Particle : public PhysicalEntity {

    SDL_Color color;
    Timer timer;

public:

    Particle(Scene *scene, int x, int y, int size, SDL_Color color, float duration);
    void render();
    void reset(int x, int y);
    bool is_finished();

};

#endif