#ifndef SDLGL_PARTICLE_EMITTER_H
#define SDLGL_PARTICLE_EMITTER_H

#include "../../game/physical_entity.h"
#include "particle.h"

class ParticleEmitter : public PhysicalEntity {
   protected:
    std::vector<SDL_Color> colors;
    int color_index;
    int particle_size;
    float particle_duration;
    int quantity;
    Timer life_timer;
    Timer emit_timer;
    bool emit_delay;
    bool stopping;
    std::vector<Particle *> particles;

    virtual void new_particle() = 0;
    virtual void reset_particle(Particle *particle) = 0;
    void handle_emission();
    SDL_Color next_color();

   public:
    ParticleEmitter(const std::shared_ptr<Scene> &scene, int x, int y,
                    std::vector<SDL_Color> colors, int quantity, int size,
                    float particle_duration = 1.0f, float lifetime = 0.0f,
                    bool emit_delay = true);
    void set_location(int x, int y);
    void stop();
    void update() override;
    void render() override;
    ~ParticleEmitter() override;
};

#endif