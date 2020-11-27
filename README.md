# sdlgl


### A SDL2 Game Library

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

I'm currently working on improving documentation coverage. Documentation can be found in the `documentation/` directory.

### Installation

To install SDLGL, you will have to build from source. The Makefile currently requires a linux environment and the following packages:

```
sudo apt-get install -y g++ libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

Finally, use the Makefile to build and install the library for development:
```
make
make install
```
