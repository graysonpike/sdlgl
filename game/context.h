#ifndef CONTEXT_H
#define CONTEXT_H

#include "../audio/audio.h"
#include "../graphics/graphics.h"
#include "../input/inputs.h"
#include "./clock.h"
#include "./scene.h"

class Context {
   public:
    std::shared_ptr<Graphics> graphics;
    std::shared_ptr<Audio> audio;
    std::shared_ptr<Inputs> inputs;
    std::shared_ptr<Clock> clock;
    std::shared_ptr<bool> loop;

    explicit Context(const std::shared_ptr<Graphics>& graphics);
    Context(const std::shared_ptr<Graphics>& graphics,
            const std::shared_ptr<Audio>& audio,
            const std::shared_ptr<Inputs>& inputs,
            const std::shared_ptr<Clock>& clock);
};

#endif