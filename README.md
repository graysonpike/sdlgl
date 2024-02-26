# sdlgl


## An SDL2 Game Library

This is a simple game framework library I'm creating for use in my own games.
SDLGL currently provides support for 
* A simple and extensible Entity + Scene organization
* A simple 'Update and Render' game loop
* Audio mixing for sound effects and music built on [miniaudio](https://github.com/mackron/miniaudio)
* Easily configurable (JSON-defined) resources supporting:
	* Animated sprites
	* Static textures
	* Sound effects
	* Music tracks
* Collision detection system for rotatable rectangles
* Font renderer
* Debugging UI elements
* Access to the SDL2 rendering context
* Multiple example programs demonstrating each engine feature

## Demo Projects

In addition to the example programs, I have some other projects that are
built with SDLGL.

### [SDLGL Knight Game](https://github.com/graysonpike/sdlgl-knight-game)
![Knight game gameplay](screenshots/knight.gif)

### [SDLGL Visuals](https://github.com/graysonpike/sdlgl-visuals)
![Perlin noise waves simulation](screenshots/waves.gif)

### [SDGL Tank Game](https://github.com/graysonpike/sdlgl-tank-game)
![Tank game gameplay](screenshots/tanks.png)

## Dependencies

To install SDLGL, you will have to build from source. Before building, there are 4 dependencies required for static linking:
- SDL2
- SDL2 Image
- SDL2 TTF
- SDL2 Mixer

### Installing Dependencies on Linux (Debian/Ubuntu)
You can use apt to install the libraries.
```
sudo apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

### MacOS
You can use homebrew to install the libraries.
```
brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf
```

## Building and Installation
Currently, no binaries are published for SDLGL. A CMake configuration is provided to enable easy building across platforms.
This project provides SDL2 CMake modules to enable CMake to find the SDL2 libraries on all systems. The modules are taken from
[this repository](https://github.com/aminosbh/sdl2-cmake-modules) by [Amine B. Hassouna](https://github.com/aminosbh).

To generate the build files:
```shell
cmake -S . -B build
```

To build the library:
```shell
cd build
make
```

To install the library:
```shell
# From within the build directory
sudo cmake --install . 

# Or from within the project root
sudo cmake --install build
```

The library will be installed to:
- Headers to `/usr/local/include`
- Static library archive to `/usr/local/lib`
- CMake targets export file and CMake configuration file (`sdlglTargets.cmake`) to `/usr/local/lib/cmake/sdlgl`

## Development

### Additional Development Requirements
In addition to the build requirements, additional tools are required for development.
You can install them with the following commands:
#### Linux (Debian/Ubuntu)
```shell
sudo apt install clang-format
```
#### macOS
```shell
brew install clang-format
```

### Formatting
This project is auto-formatted to the Google style (modified to an indent of 4 spaces)
using the clang-format tool.

To run the auto-formatter on all files, use the following command:
```shell
bash clang_format_project.sh
```

## License
SDLGL is licensed under the [MIT License](https://github.com/graysonpike/sdlgl/blob/master/LICENSE).

This library uses the [JSON C++ library by Niels Lohmann](https://github.com/nlohmann/json) which is licensed under the MIT License.