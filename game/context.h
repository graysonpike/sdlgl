#ifndef CONTEXT_H
#define CONTEXT_H

#include "../input/inputs.h"
#include "../graphics/graphics.h"
#include "./scene.h"
#include "./clock.h"


class Context {

public:

    Graphics *graphics;
    Inputs *inputs;
    Clock *clock;
    bool *loop;

    Context(Graphics *graphics, Inputs *inputs, Clock *clock);
};

#endif