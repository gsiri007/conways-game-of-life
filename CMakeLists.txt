cmake_minimum_required(VERSION 3.16)
project(conways-game-of-life)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(SDL_X11_XSCRNSAVER OFF CACHE BOOL "Disable X11 screensaver support" FORCE)
set(SDL_X11_XTEST OFF CACHE BOOL "Disable X11 XTest support" FORCE)
set(SDL_ALSA OFF CACHE BOOL "Disable ALSA support" FORCE)
set(SDL_JACK OFF CACHE BOOL "Disable JACK support" FORCE)
set(SDL_PIPEWIRE OFF CACHE BOOL "Disable PipeWire support" FORCE)
set(SDL_PULSEAUDIO OFF CACHE BOOL "Disable PulseAudio support" FORCE)
set(SDL_SNDIO OFF CACHE BOOL "Disable sndio support" FORCE)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL_ttf")
    add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)
else()
    find_package(SDL3_ttf REQUIRED)
endif()

add_executable(conways-game-of-life
    main.cpp
    Game.cpp
    Cells.cpp
    Cells.hpp
    Game.hpp
)

target_link_libraries(conways-game-of-life PRIVATE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
)
