cmake_minimum_required(VERSION 3.23.1)
project(CoffeeBean)

file(GLOB_RECURSE sources src/*.cpp src/*.c thirdparty/Simple-SDL2-Audio/src/audio.c)
file(GLOB_RECURSE includes include/*.hpp include/*.h)

include(cmake/cbe_defines.cmake)

add_library(${PROJECT_NAME} ${sources} ${includes})
add_definitions("-Wall -Wextra -pedantic")
include_directories(include)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/SDL2/include)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/stb)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/sokol)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/Simple-SDL2-Audio/src)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC thirdparty/sdl_stb_font) #Not system, but this thing has a ton of warnings
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/json/single_include)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/Xoshiro)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)
