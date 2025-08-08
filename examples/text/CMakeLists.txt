cmake_minimum_required(VERSION 3.20) # Adjust the version as necessary
project(TextExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g)

# Add the executable
add_executable(TextExample main.cpp)

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

add_custom_command(
        TARGET TextExample POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_DIR} ${TARGET_RESOURCE_DIR}
        COMMENT "Copying resources to build directory"
)

add_custom_command(
        TARGET TextExample POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE_RESOURCES_JSON} ${TARGET_RESOURCES_JSON}
        COMMENT "Copying resources.json to build directory"
)

target_link_libraries(TextExample PRIVATE SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer sdlgl::sdlgl)
