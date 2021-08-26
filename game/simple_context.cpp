#include "simple_context.h"


SimpleContext::SimpleContext(Graphics *graphics, Inputs *inputs, Clock *clock) :
	Context(graphics, inputs, clock), scene(new Scene(inputs, graphics)) {}
