cmake_minimum_required(VERSION 3.12)
project(xic)

add_compile_options(-g -Wall -Werror -Wextra -std=c++17)

include_directories(include)
file(GLOB src_files src/*.cpp)
add_executable(xic ${src_files})


