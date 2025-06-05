# Minimum CMake version
cmake_minimum_required(VERSION 3.15)

set(CMAKE_BUILD_TYPE "Debug")

# Project name and version
project(coolgame_99 VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the absolute path to the SDL3 and SDL_image directories
set(SDL3_DIR "/Users/deniz_kaya/Projects/3pty_repos/SDL")
set(SDL3_LIB_DIR "/Users/deniz_kaya/Projects/3pty_repos/SDL/build")

set(SDL_IMAGE_DIR "/Users/deniz_kaya/Projects/3pty_repos/SDL_image")
set(SDL_IMAGE_LIB_DIR "/Users/deniz_kaya/Projects/3pty_repos/SDL_image/build")

# Add SDL3 and SDL_image source directories
add_subdirectory(${SDL3_DIR} ${CMAKE_BINARY_DIR}/sdl3)
add_subdirectory(${SDL_IMAGE_DIR} ${CMAKE_BINARY_DIR}/sdl_image)

link_directories(${SDL3_LIB_DIR})
link_directories(${SDL_IMAGE_LIB_DIR})

# Specify the executable file
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(coolgame_99 ${SRC_FILES})
# add_executable(coolgame_99 main.cpp draw.cpp helpers.cpp classes.cpp entity.cpp textureManager.cpp app.cpp peripherals.cpp drawer.cpp levelMap.cpp collisionManager.cpp VectorTwo.cpp BodyTwo.cpp collisions.cpp)

# Link SDL3 and SDL_image libraries
target_link_libraries(coolgame_99 PRIVATE SDL3 SDL3_image)

# Include the SDL3 and SDL_image headers
target_include_directories(coolgame_99 PRIVATE 
    ${SDL3_DIR}/include
    ${SDL_IMAGE_DIR}/include
)