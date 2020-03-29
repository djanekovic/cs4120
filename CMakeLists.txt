cmake_minimum_required(VERSION 3.12)
project(xic CXX)

find_package(FLEX REQUIRED)
FLEX_TARGET(XI_scanner src/xi++-scanner.ll
            ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp
            COMPILE_FLAGS "--c++ -d")
file(GLOB src_files src/*.cpp)
include_directories(include)

set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
add_executable(xic ${src_files} ${FLEX_XI_scanner_OUTPUTS})

set_property(TARGET xic PROPERTY CXX_STANDARD 17)
