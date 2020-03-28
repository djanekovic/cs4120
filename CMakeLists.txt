cmake_minimum_required(VERSION 3.13.4)
project(xic CXX)

find_package(FLEX REQUIRED)
FLEX_TARGET(XI_scanner src/xi++-scanner.ll
            ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp
            COMPILE_FLAGS "--c++ -d")
file(GLOB src_files src/*.cpp)
include_directories(include)

add_executable(xic ${src_files} ${FLEX_XI_scanner_OUTPUTS})
