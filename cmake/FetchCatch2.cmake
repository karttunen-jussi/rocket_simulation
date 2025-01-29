cmake_minimum_required(VERSION "3.29")

include(FetchContent)

# Add Catch2 unit testing framework to allow creating unit tests
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.0
)

FetchContent_MakeAvailable(Catch2)
