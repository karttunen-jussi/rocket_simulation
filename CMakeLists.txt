cmake_minimum_required(VERSION "3.29")

project("SmallExamples"
        LANGUAGES "CXX"
        DESCRIPTION "Small C++ and CMake examples for teaching purposes")

set(CMAKE_CXX_STANDARD "23")
set(CMAKE_CXX_EXTENSIONS "OFF")

add_compile_options(
        -O2
        -g2
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -pedantic-errors
        -fdiagnostics-color)

set("CompileOptionsGccExhaustive"
        -fimplicit-constexpr
        -fstrict-aliasing
        -fstrict-enums
        -ftrivial-auto-var-init=zero
        -Walloca
        -Walloc-zero
        -Warith-conversion
        -Warray-bounds=2
        -Wattribute-alias=2
        -Wbuiltin-declaration-mismatch
        -Wbuiltin-macro-redefined
        -Wcast-qual
        -Wcast-align=strict
        -Wchanges-meaning
        -Wconversion
        -Wdeprecated
        -Wdisabled-optimization
        -Wdouble-promotion
        -Wduplicated-branches
        -Wduplicated-cond
        -Wextra-semi
        -Wfloat-equal
        -Wformat=2
        -Wformat-signedness
        -Wimplicit-fallthrough=5
        -Winvalid-constexpr
        -Winvalid-imported-macros
        -Winvalid-pch
        -Winvalid-utf8
        -Wlogical-op
        -Wmismatched-tags
        -Wmissing-declarations
        -Wmissing-include-dirs
        -Wmissing-template-keyword
        -Wmultichar
        -Wmultiple-inheritance
        -Wnormalized
        -Wnull-dereference
        -Wnrvo
        -Wold-style-cast
        -Wpacked
        -Wplacement-new=2
        -Wredundant-decls
        -Wredundant-tags
        -Wshadow
        -Wshift-negative-value
        -Wshift-overflow=2
        -Wsign-conversion
        -Wsign-promo
        -Wstrict-null-sentinel
        -Wstrict-overflow=3
        -Wsuggest-attribute=const
        -Wsuggest-final-methods
        -Wsuggest-final-types
        -Wsuggest-override
        -Wswitch-default
        -Wswitch-enum
        -Wtrampolines
        -Wtrivial-auto-var-init
        -Wundef
        -Wuninitialized
        -Wunused
        -Wunused-const-variable
        -Wunused-macros
        -Wunsafe-loop-optimizations
        -Wuseless-cast
        -Wvector-operation-performance
        -Wvla
        -Wwrite-strings
        -Wxor-used-as-pow
        -Wzero-as-null-pointer-constant)

# Fetch Catch2 unit testing framework to allow creating unit tests
include(cmake/FetchCatch2.cmake)

add_subdirectory(source)
