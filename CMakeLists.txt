cmake_minimum_required(VERSION 3.7)
project(algorithms_cpp)

set(CMAKE_CXX_STANDARD 14)

macro (add_sources)
    file (RELATIVE_PATH _relPath "${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach (_src ${ARGN})
        if (_relPath)
            list (APPEND SRCS "${_relPath}/${_src}")
        else()
            list (APPEND SRCS "${_src}")
        endif()
    endforeach()
    if (_relPath)
        # propagate SRCS to parent directory
        set (SRCS ${SRCS} PARENT_SCOPE)
    endif()
endmacro()

add_sources(main.cpp)
add_subdirectory(src/priorityqueue)
add_subdirectory(src/special_cases/navigation_routing)

add_executable(algorithms_cpp ${SRCS})