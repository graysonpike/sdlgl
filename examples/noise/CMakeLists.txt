cmake_minimum_required(VERSION 3.20) # Adjust the version as necessary
project(NoiseExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
        main.cpp
)

add_compile_options(-g)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/sdl2)

# SDL2
find_package(SDL2 REQUIRED)

# SDL2_image
find_package(SDL2_image REQUIRED)

# SDL2_ttf
find_package(SDL2_ttf REQUIRED)

# SDL2_mixer
find_package(SDL2_mixer REQUIRED)

# SDLGL
find_package(sdlgl REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer sdlgl::sdlgl)

