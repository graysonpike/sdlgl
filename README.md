# sdlgl


## An SDL2 Game Library

This is a simple game framework library I'm creating for use in my own games. SDLGL currently provides support for 
* A simple and extensible Entity + Scene organization
* A simple 'Update and Render' game loop with time delta
* Multi-channel audio mixing for sound effects and music
* Easily configurable (JSON-defined) resources supporting:
	* Animated sprites
	* Static textures
	* Sound effects
	* Music tracks
* Collision detection system for rotatable rects
* An FPS counter
* Font renderer
* Direct access to the SDL2 rendering context
* Multiple clean, well commented example programs


## Demo Projects

In addition to the example programs, I have some other projects that are built with SDLGL.

### [SDLGL Knight Game](https://github.com/graysonpike/sdlgl-knight-game)
![Knight game gameplay](screenshots/knight.gif)

### [SDLGL Visuals](https://github.com/graysonpike/sdlgl-visuals)
![Perlin noise waves simulation](screenshots/waves.gif)

### [SDGL Tank Game](https://github.com/graysonpike/sdlgl-tank-game)
![Tank game gameplay](screenshots/tanks.png)



## Installation

To install SDLGL, you will have to build from source. The Makefile currently requires a linux environment and the following packages:

```
sudo apt-get install -y g++ libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

Finally, use the Makefile to build and install the library for development:
```
make
make install
```
