cmake_minimum_required(VERSION "3.29")

project("SmallExamples"
        LANGUAGES "CXX"
        DESCRIPTION "Small C++ and CMake examples for teaching purposes")

set(CMAKE_CXX_STANDARD "23")
set(CMAKE_CXX_EXTENSIONS "OFF")

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_compile_options(-O2 -g)

# Fetch Catch2 unit testing framework to allow creating unit tests
include(cmake/FetchCatch2.cmake)

add_subdirectory(source)
