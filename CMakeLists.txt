cmake_minimum_required(VERSION 3.15)

project(flappy-frog
        LANGUAGES C CXX
        VERSION 0.1.0
        DESCRIPTION "A little game of a flappy frog")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

option(BUILD_TESTS "Also build the tests" ON)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
