cmake_minimum_required(VERSION 3.23.1)
project(CoffeeBean)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE sources src/*.cpp src/*.c thirdparty/Simple-SDL2-Audio/src/audio.c)
file(GLOB_RECURSE includes include/*.hpp include/*.h)

include(cmake/cbe_defines.cmake)

add_library(${PROJECT_NAME} ${sources} ${includes})
add_definitions("-Wall -Wextra -pedantic")
include_directories(include)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/SDL2/include)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/stb)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/dr_libs)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/sokol)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/Simple-SDL2-Audio/src)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC thirdparty/sdl_stb_font) #Not system, but this thing has a ton of warnings
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/json/single_include)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/Xoshiro)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/box2d/include)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(thirdparty/box2d/)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2 box2d)

option(BUILD_BEANPONG "Build the example probject" OFF)
if(BUILD_BEANPONG)
    file(GLOB_RECURSE beanpong_sources example/BeanPong/src/*.c example/BeanPong/src/*.cpp example/BeanPong/src/*.h example/BeanPong/src/*.hpp)
    add_executable(BeanPong ${beanpong_sources})
    IF(MINGW)
        target_link_libraries(BeanPong -static-libstdc++)
        target_link_libraries(BeanPong -static-libgcc)
        target_link_libraries(BeanPong mingw32)
    ENDIF(MINGW)

    IF(WIN32)
        target_link_libraries(BeanPong SDL2main)
    ENDIF(WIN32)

    target_link_libraries(BeanPong CoffeeBean)

    file(COPY example/BeanPong/assets DESTINATION ${CMAKE_BINARY_DIR})
endif(BUILD_BEANPONG)

