#ifndef SIMPLE_CONTEXT_H
#define SIMPLE_CONTEXT_H

#include "./context.h"


class SimpleContext : public Context {

public:

	Scene *scene;

	SimpleContext(Graphics *graphics);
	SimpleContext(Graphics *graphics, Audio *audio, Inputs *inputs, Clock *clock);

};

#endif