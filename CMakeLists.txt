cmake_minimum_required(VERSION "3.29")

project("SmallExamples"
        LANGUAGES "CXX"
        DESCRIPTION "Small C++ and CMake examples for teaching purposes")

set(CMAKE_CXX_STANDARD "23")
set(CMAKE_CXX_EXTENSIONS "OFF")

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_compile_options(-O2 -g)

add_executable("HelloWorld" hello_world.cpp)
add_executable("SineWaveCsvData" sine_wave_csv_data.cpp)

# Fetch Catch2 unit testing framework to allow creating unit tests
include(cmake/FetchCatch2.cmake)

add_executable("UnitTestExample" test_example.cpp)
target_link_libraries("UnitTestExample" PRIVATE Catch2::Catch2WithMain)
