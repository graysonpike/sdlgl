#ifndef PARTICLES_H
#define PARTICLES_H

#include "../../game/physical_entity.h"
#include "linear_particle.h"


class Particles : public PhysicalEntity {

    int vx_min;
    int vx_max;
    int vy_min;
    int vy_max;
    std::vector<SDL_Color> colors;
    int color_index;
    int particle_size;
    float particle_duration;
    int quantity;
    Timer life_timer;
    Timer emit_timer;
    bool emit_delay;
    bool stopping;
    std::vector<LinearParticle> particles;

    void get_random_velocity(int *vx, int *vy);

public:

    Particles(Scene *scene, int x, int y, int vx_min, int vx_max, int vy_min, int vy_max, std::vector<SDL_Color> colors, int quantity, int size, float particle_duration=1.0f, float lifetime=0.0f, bool emit_delay=true);
    void set_location(int x, int y);
    void set_velocity(int vx_min, int vx_max, int vy_min, int vy_max);
    void stop();
    void update();
    void render();
    
};

#endif