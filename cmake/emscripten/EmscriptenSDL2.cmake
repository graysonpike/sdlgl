# EmscriptenSDL2.cmake
# Shared CMake configuration for building SDL2 games with Emscripten
#
# Usage: include this file in your CMakeLists.txt after detecting Emscripten
#   if(EMSCRIPTEN)
#       include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/emscripten/EmscriptenSDL2.cmake)
#       target_link_libraries(${PROJECT_NAME} PRIVATE ${EMSCRIPTEN_SDL2_LINK_FLAGS})
#   endif()

if(NOT EMSCRIPTEN)
    message(FATAL_ERROR "EmscriptenSDL2.cmake should only be included when building with Emscripten")
endif()

# SDL2 port flags for Emscripten
# Note: We use SDL2 Audio (not SDL2_mixer) as miniaudio's device backend
set(EMSCRIPTEN_SDL2_FLAGS
    "-sUSE_SDL=2"
    "-sUSE_SDL_IMAGE=2"
    "-sUSE_SDL_TTF=2"
)

# SDL2_image format support (png only to avoid quoting issues)
# Add more formats by modifying this list if needed
set(EMSCRIPTEN_SDL2_IMAGE_FORMATS "-sSDL2_IMAGE_FORMATS=[png]")

# Memory settings (adjust as needed for your game)
set(EMSCRIPTEN_MEMORY_FLAGS
    "-sALLOW_MEMORY_GROWTH=1"
    "-sINITIAL_MEMORY=67108864"  # 64MB initial
    "-sSTACK_SIZE=1048576"       # 1MB stack for audio processing
)

# Audio settings - needed for miniaudio with SDL Audio backend
set(EMSCRIPTEN_AUDIO_FLAGS
    "-sFORCE_FILESYSTEM=1"       # Required for file-based audio loading
)

# WebGL settings
set(EMSCRIPTEN_GL_FLAGS
    "-sUSE_WEBGL2=1"
    "-sFULL_ES2=1"
)

# Export settings for the main loop
set(EMSCRIPTEN_EXPORT_FLAGS
    "-sEXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
)

# Combine all link flags
set(EMSCRIPTEN_SDL2_LINK_FLAGS
    ${EMSCRIPTEN_SDL2_FLAGS}
    ${EMSCRIPTEN_SDL2_IMAGE_FORMATS}
    ${EMSCRIPTEN_MEMORY_FLAGS}
    ${EMSCRIPTEN_AUDIO_FLAGS}
    ${EMSCRIPTEN_GL_FLAGS}
    ${EMSCRIPTEN_EXPORT_FLAGS}
)

# Convert list to string for use in target_link_options
string(JOIN " " EMSCRIPTEN_SDL2_LINK_FLAGS_STRING ${EMSCRIPTEN_SDL2_LINK_FLAGS})

# Compiler flags (apply to compilation as well)
set(EMSCRIPTEN_SDL2_COMPILE_FLAGS ${EMSCRIPTEN_SDL2_FLAGS})

# Function to configure an SDL2 target for Emscripten
# Usage: emscripten_configure_sdl2_target(target_name)
function(emscripten_configure_sdl2_target TARGET_NAME)
    if(NOT EMSCRIPTEN)
        return()
    endif()

    # Add compile options
    target_compile_options(${TARGET_NAME} PRIVATE ${EMSCRIPTEN_SDL2_COMPILE_FLAGS})

    # Add link options
    target_link_options(${TARGET_NAME} PRIVATE ${EMSCRIPTEN_SDL2_LINK_FLAGS})
endfunction()

# Function to setup asset preloading for Emscripten
# Usage: emscripten_preload_assets(target_name asset_dir [virtual_dir])
function(emscripten_preload_assets TARGET_NAME ASSET_DIR)
    if(NOT EMSCRIPTEN)
        return()
    endif()

    # Optional virtual directory argument (defaults to same as source)
    if(ARGC GREATER 2)
        set(VIRTUAL_DIR ${ARGV2})
    else()
        get_filename_component(VIRTUAL_DIR ${ASSET_DIR} NAME)
    endif()

    # Must be a single argument with @ separator
    set(PRELOAD_ARG "--preload-file=${ASSET_DIR}@${VIRTUAL_DIR}")
    target_link_options(${TARGET_NAME} PRIVATE ${PRELOAD_ARG})
endfunction()

# Function to use a custom HTML shell template
# Usage: emscripten_set_shell_file(target_name shell_file_path)
function(emscripten_set_shell_file TARGET_NAME SHELL_FILE)
    if(NOT EMSCRIPTEN)
        return()
    endif()

    target_link_options(${TARGET_NAME} PRIVATE
        "--shell-file=${SHELL_FILE}"
    )
endfunction()

message(STATUS "EmscriptenSDL2 module loaded - SDL2 web build support enabled")
