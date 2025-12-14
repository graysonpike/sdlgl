cmake_minimum_required(VERSION 3.20)
project(TeaGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
        main.cpp
        game.cpp
        entities/player.cpp
        states/playing_state.cpp
        states/main_menu_state.cpp
)

add_compile_options(-g)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Resource directories
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(TARGET_RESOURCE_DIR "${CMAKE_BINARY_DIR}/res")
set(SOURCE_RESOURCES_JSON "${CMAKE_SOURCE_DIR}/resources.json")
set(TARGET_RESOURCES_JSON "${CMAKE_BINARY_DIR}/resources.json")

if(EMSCRIPTEN)
    # =====================
    # Emscripten Web Build
    # =====================
    message(STATUS "Building for Web (Emscripten)")

    # Include shared Emscripten SDL2 configuration
    include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/emscripten/EmscriptenSDL2.cmake)

    # SDLGL - for Emscripten, we need to compile it as part of the project
    # since it's not installed as a system library
    set(SDLGL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")

    # Collect SDLGL source files (including audio with miniaudio)
    set(SDLGL_SOURCES
        ${SDLGL_DIR}/audio/audio.cpp
        ${SDLGL_DIR}/audio/sound.cpp
        ${SDLGL_DIR}/collision/collider.cpp
        ${SDLGL_DIR}/collision/hitbox.cpp
        ${SDLGL_DIR}/game/clock.cpp
        ${SDLGL_DIR}/game/context.cpp
        ${SDLGL_DIR}/game/entity.cpp
        ${SDLGL_DIR}/game/physical_entity.cpp
        ${SDLGL_DIR}/game/scene.cpp
        ${SDLGL_DIR}/game/timer.cpp
        ${SDLGL_DIR}/game/game_state_manager.cpp
        ${SDLGL_DIR}/graphics/effects/emitter.cpp
        ${SDLGL_DIR}/graphics/effects/linear_emitter.cpp
        ${SDLGL_DIR}/graphics/effects/linear_particle.cpp
        ${SDLGL_DIR}/graphics/effects/particle.cpp
        ${SDLGL_DIR}/graphics/fps_counter.cpp
        ${SDLGL_DIR}/graphics/graphics.cpp
        ${SDLGL_DIR}/graphics/resources.cpp
        ${SDLGL_DIR}/graphics/sprite.cpp
        ${SDLGL_DIR}/graphics/texture.cpp
        ${SDLGL_DIR}/graphics/tileset.cpp
        ${SDLGL_DIR}/graphics/tilemap.cpp
        ${SDLGL_DIR}/graphics/text.cpp
        ${SDLGL_DIR}/graphics/character.cpp
        ${SDLGL_DIR}/input/inputs.cpp
        ${SDLGL_DIR}/ui/entity_count.cpp
        ${SDLGL_DIR}/ui/fps_display.cpp
        ${SDLGL_DIR}/ui/menu_background.cpp
        ${SDLGL_DIR}/ui/menu.cpp
        ${SDLGL_DIR}/ui/typewriter_text.cpp
        ${SDLGL_DIR}/utilities/math.cpp
        ${SDLGL_DIR}/utilities/noise.cpp
        ${SDLGL_DIR}/utilities/random.cpp
        ${SDLGL_DIR}/utilities/string_utils.cpp
    )

    # Add SDLGL sources to the executable
    target_sources(${PROJECT_NAME} PRIVATE ${SDLGL_SOURCES})

    # Include directories for SDLGL headers
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${SDLGL_DIR}/..  # So #include <sdlgl/...> works
        ${SDLGL_DIR}/dependencies  # For miniaudio.h
    )

    # Configure SDL2 for Emscripten
    emscripten_configure_sdl2_target(${PROJECT_NAME})

    # Preload assets
    emscripten_preload_assets(${PROJECT_NAME} ${RESOURCE_DIR} "res")
    emscripten_preload_assets(${PROJECT_NAME} ${SOURCE_RESOURCES_JSON} "resources.json")

    # Use custom HTML shell if it exists
    if(EXISTS "${CMAKE_SOURCE_DIR}/shell.html")
        emscripten_set_shell_file(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/shell.html")
    endif()

    # Output .html file
    set_target_properties(${PROJECT_NAME} PROPERTIES
        SUFFIX ".html"
    )

else()
    # =====================
    # Native Build
    # =====================
    message(STATUS "Building for Native platform")

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

    # Create a custom target for resource copying
    add_custom_target(copy_resources ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_DIR} ${TARGET_RESOURCE_DIR}
            COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE_RESOURCES_JSON} ${TARGET_RESOURCES_JSON}
            COMMENT "Copying resources to build directory"
    )

    add_dependencies(${PROJECT_NAME} copy_resources)

    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer sdlgl::sdlgl)

endif()
