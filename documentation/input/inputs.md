# Inputs
Documentation for Version 1.0


### Overview
The **Inputs** class is used to respond to mouse button events, the cursor position, key press events, key states, and window button events. It is typically used in the `update()` method of Entities:
```
void Box::update() {
	Inputs *inputs = scene->get_inputs();

	if(inputs->is_key_down(KEY_UP)) {
		y -= SPEED * scene->get_delta();
	}

	if(inputs->is_key_down(KEY_DOWN)) {
		y += SPEED * scene->get_delta();
	}

	if(inputs->is_key_down(KEY_LEFT)) {
		x -= SPEED * scene->get_delta();
	}

	if(inputs->is_key_down(KEY_RIGHT)) {
		x += SPEED * scene->get_delta();
	}
}
```
> From `box.cpp` in the red_box example.

Typically, one instance of Inputs is instantiated at the beginning of the game and used by all Scenes in the game. Scenes require a reference to a Inputs in their constructor.
