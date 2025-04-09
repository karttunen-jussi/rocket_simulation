cmake_minimum_required(VERSION "3.29")

project("RocketSimulation"
        LANGUAGES "CXX"
        DESCRIPTION "Newton's laws of motion based 2D physic simulation presenting rocket movement")

set(CMAKE_CXX_STANDARD   "23")
set(CMAKE_CXX_EXTENSIONS "OFF")

# Get the compiler options to be applied to build targets
include(cmake/CompilerOptions.cmake)

# Fetch Catch2 unit testing framework to allow creating unit tests
include(cmake/FetchCatch2.cmake)

add_subdirectory(source)
