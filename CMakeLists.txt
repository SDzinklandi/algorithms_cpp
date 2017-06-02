cmake_minimum_required(VERSION 3.7)
project(algorithms_cpp)

set(CMAKE_CXX_STANDARD 14)

# The main cpp must be builded
set(MAIN_SOURCES main.cpp)

# This are all general algorithms
#file(GLOB_RECURSE priorityQueue src/priorityqueue/*.cpp src/priorityqueue/*.h)

# This contains all projects. You can just build one project at a time
#file(GLOB_RECURSE project src/special_cases/direction_calcultion/*.cpp src/special_cases/direction_calcultion/*.h)
file(GLOB_RECURSE project src/special_cases/navigation_routing/*.cpp src/special_cases/navigation_routing/*.h)

add_executable(algorithms_cpp ${MAIN_SOURCES} ${project})