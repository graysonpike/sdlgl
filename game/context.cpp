#include "context.h"


Context::Context(Graphics *graphics, Inputs *inputs, Clock *clock) : 
	graphics(graphics), inputs(inputs), clock(clock) {

	loop = static_cast<bool*>(malloc(sizeof(bool)));
	*loop = true;

}
