#ifndef CONTEXT_H
#define CONTEXT_H

#include "../audio/audio.h"
#include "../graphics/graphics.h"
#include "../input/inputs.h"
#include "./clock.h"
#include "./scene.h"

class Context {
   public:
    Graphics *graphics;
    Audio *audio;
    Inputs *inputs;
    Clock *clock;
    bool *loop;

    Context(Graphics *graphics);
    Context(Graphics *graphics, Audio *audio, Inputs *inputs, Clock *clock);
};

#endif