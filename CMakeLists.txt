cmake_minimum_required(VERSION 3.7)
project(algorithms_cpp)

set(CMAKE_CXX_STANDARD 14)

set(MAIN_SOURCES main.cpp)
file(GLOB_RECURSE directionProject src/special_cases/direction_calcultion/*.cpp src/special_cases/direction_calcultion/*.h)
file(GLOB_RECURSE priorityQueue src/priorityqueue/*.cpp src/priorityqueue/*.h)
file(GLOB_RECURSE navigationProject src/special_cases/navigation_routing/*.cpp src/special_cases/navigation_routing/*.h)

add_executable(algorithms_cpp ${MAIN_SOURCES} ${priorityQueue} ${directionProject} ${navigationProject})