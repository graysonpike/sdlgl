cmake_minimum_required(VERSION 3.20) # Choose an appropriate version
project(sdlgl VERSION 1.0 DESCRIPTION "SDLGL Library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-g3 -Wall)

set(SOURCES
        audio/audio.cpp
        audio/sound.cpp
        collision/collider.cpp
        collision/hitbox.cpp
        game/clock.cpp
        game/context.cpp
        game/entity.cpp
        game/physical_entity.cpp
        game/scene.cpp
        game/timer.cpp
        graphics/effects/emitter.cpp
        graphics/effects/linear_emitter.cpp
        graphics/effects/linear_particle.cpp
        graphics/effects/particle.cpp
        graphics/fps_counter.cpp
        graphics/graphics.cpp
        graphics/resources.cpp
        graphics/sprite.cpp
        graphics/texture.cpp
        graphics/tileset.cpp
        graphics/tilemap.cpp
        graphics/text.cpp
        input/inputs.cpp
        ui/entity_count.cpp
        ui/fps_display.cpp
        utilities/math.cpp
        utilities/noise.cpp
        utilities/random.cpp
)

add_library(sdlgl STATIC ${SOURCES})

# SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

# SDL2_image
find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Image)

# SDL2_ttf
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# SDL2_mixer
find_package(SDL2_mixer REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

set_target_properties(sdlgl PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "/usr/local/include"
)

export(TARGETS sdlgl
        NAMESPACE sdlgl::
        FILE "${CMAKE_CURRENT_BINARY_DIR}/sdlglTargets.cmake")

install(TARGETS sdlgl
        EXPORT sdlglTargets
        ARCHIVE DESTINATION /usr/local/lib
)

install(EXPORT sdlglTargets
        FILE sdlglTargets.cmake
        NAMESPACE sdlgl::
        DESTINATION lib/cmake/sdlgl)

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/sdlglConfig.cmake"
        DESTINATION lib/cmake/sdlgl)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/
        DESTINATION /usr/local/include/sdlgl
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".git" EXCLUDE
        PATTERN "build" EXCLUDE
        PATTERN ".idea" EXCLUDE
        PATTERN "examples" EXCLUDE
        PATTERN "screenshots" EXCLUDE
)
