cmake_minimum_required(VERSION 3.20) # Adjust the version as necessary
project(TeaGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
        main.cpp
        entities/player.cpp
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

set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(TARGET_RESOURCE_DIR "${CMAKE_BINARY_DIR}/res")
set(SOURCE_RESOURCES_JSON "${CMAKE_SOURCE_DIR}/resources.json")
set(TARGET_RESOURCES_JSON "${CMAKE_BINARY_DIR}/resources.json")

# Create a custom target for resource copying
add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_DIR} ${TARGET_RESOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE_RESOURCES_JSON} ${TARGET_RESOURCES_JSON}
        COMMENT "Copying resources to build directory"
)

add_dependencies(${PROJECT_NAME} copy_resources)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer sdlgl::sdlgl)

