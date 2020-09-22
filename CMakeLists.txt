cmake_minimum_required(VERSION 3.12)
project(xic)

set(CMAKE_CXX_COMPILER clang++-10)
add_compile_options(-g -Wall -Werror -Wextra -std=c++20)

include_directories(include)
file(GLOB src_files src/*.cpp)
add_executable(xic ${src_files})


