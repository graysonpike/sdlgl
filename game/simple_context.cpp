#include "simple_context.h"


SimpleContext::SimpleContext(Graphics *graphics, Audio *audio, Inputs *inputs, Clock *clock) :
	Context(graphics, audio, inputs, clock), scene(new Scene(graphics, audio, inputs)) {}

SimpleContext::SimpleContext(Graphics *graphics) : Context(graphics) {
	scene = new Scene(graphics, audio, inputs);
}
