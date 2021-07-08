# CMakeLists.txt -- Top-level CMake script

cmake_minimum_required (VERSION 3.11)
project (singleton CXX)

set (CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard to build all targets.")
set (CMAKE_CXX_STANDARD_REQUIRED 17 CACHE BOOL "CMAKE_CXX_STANDARD selected C++ standard is a requirement.")
add_compile_options( -g -Wall -Wextra -pedantic )

add_executable(singleton.x singleton.cpp main.cpp)
