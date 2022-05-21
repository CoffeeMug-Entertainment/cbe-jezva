cmake_minimum_required(VERSION 3.23.1)
project(BeanPong C CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE sources src/*.cpp src/*.hpp thirdparty/CoffeeBean/thirdparty/Simple-SDL2-Audio/src/audio.c)

add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/CoffeeBean/include)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/CoffeeBean/thirdparty/SDL2/include)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/CoffeeBean/thirdparty/stb)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/CoffeeBean/thirdparty/sokol)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/CoffeeBean/thirdparty/Simple-SDL2-Audio/src)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/CoffeeBean/thirdparty/sdl_stb_font)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/CoffeeBean/thirdparty/json/single_include)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/CoffeeBean/thirdparty/Xoshiro)

add_subdirectory(thirdparty/CoffeeBean)
include(thirdparty/CoffeeBean/cmake/cbe_defines.cmake)

IF(MINGW)
target_link_libraries(${PROJECT_NAME} -static-libstdc++)
target_link_libraries(${PROJECT_NAME} -static-libgcc)
target_link_libraries(${PROJECT_NAME} mingw32)
ENDIF()

IF(WIN32)
target_link_libraries(${PROJECT_NAME} SDL2main)
ENDIF()

target_link_libraries(${PROJECT_NAME} CoffeeBean)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})