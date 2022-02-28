#ifndef CONTEXT_H
#define CONTEXT_H

#include "../input/inputs.h"
#include "../graphics/graphics.h"
#include "./scene.h"
#include "./clock.h"
#include "../audio/audio.h"


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