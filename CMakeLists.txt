cmake_minimum_required(VERSION 3.7)
project(algorithms_cpp)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp src/priorityqueue/priorityqueue.h src/priorityqueue/priorityqueue.cpp src/priorityqueue/Element.cpp src/priorityqueue/Element.h src/priorityqueue/Node.cpp src/priorityqueue/Node.h)
add_executable(algorithms_cpp ${SOURCE_FILES})