#include "context.h"

Context::Context(Graphics *graphics, Audio *audio, Inputs *inputs, Clock *clock)
    : graphics(graphics), audio(audio), inputs(inputs), clock(clock) {
    loop = static_cast<bool *>(malloc(sizeof(bool)));
    *loop = true;
}

Context::Context(Graphics *graphics)
    : Context(graphics, new Audio(), new Inputs(), new Clock()) {}
