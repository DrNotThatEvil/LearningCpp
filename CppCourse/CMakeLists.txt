cmake_minimum_required(VERSION 3.7)

set(CMAKE_BUILD_TYPE Debug)

project(FireDemo)

find_package(SDL2 REQUIRED)
include_directories(include)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")


add_executable(FireDemo ${SOURCES})
target_link_libraries(FireDemo ${SDL2_LIBRARIES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
