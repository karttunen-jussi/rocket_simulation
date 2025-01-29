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
