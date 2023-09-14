#ifndef PARTICLE_H
#define PARTICLE_H

#include "../../game/physical_entity.h"
#include "../../game/timer.h"

class Particle : public PhysicalEntity {
    SDL_Color color;
    Timer timer;

   public:
    Particle(const std::shared_ptr<Scene> &scene, int x, int y, int size,
             SDL_Color color, float duration);
    void render() override;
    void reset(int x, int y);
    bool is_finished();
};

#endif