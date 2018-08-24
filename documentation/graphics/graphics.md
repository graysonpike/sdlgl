# Graphics
Documentation for Version 1.0


### Overview
The **Graphics** class is used to access Resources, the Font Renderer, the FPS Counter, the Rendering Context, and the Window Reference. It is typically used in the `render()` method of Entities:
```
void Box::render() {
	SDL_Renderer *renderer = scene->get_graphics()->get_renderer();

	// Draw box
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect box_rect = {(int)x, (int)y, width, height};
	SDL_RenderDrawRect(renderer, &box_rect);

}
```
> From `box.cpp` in the red_box example.

Typically, one instance of Graphics is instantiated at the beginning of the game and used by all Scenes in the game. Scenes require a reference to a Graphics in their constructor.
