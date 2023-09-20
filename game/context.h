#ifndef CONTEXT_H
#define CONTEXT_H

#include "../audio/audio.h"
#include "../graphics/graphics.h"
#include "../input/inputs.h"
#include "./clock.h"
#include "./scene.h"

class Context {
   public:
    std::shared_ptr<Clock> clock;
    std::shared_ptr<bool> loop;

    Context(const std::shared_ptr<Clock>& clock);
};

#endif