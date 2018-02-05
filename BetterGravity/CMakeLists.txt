cmake_minimum_required(VERSION 3.7)

set(CMAKE_BUILD_TYPE Debug)

project(GravitySim)

find_package(SDL2 REQUIRED)
include_directories(include)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic")

add_executable(GravitySim ${SOURCES})
target_link_libraries(GravitySim ${SDL2_LIBRARIES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
