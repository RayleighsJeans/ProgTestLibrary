cmake_minimum_required(VERSION 3.30)
project(
    ExpressionParser,
    VERSION 1.0.0
    DESCRIPTION "Simple arithmetic expression parser"
    LANGUAGES CXX
    )

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message("Project_Name: ${PROJECT_NAME}")
message("Project_Dir: ${PROJECT_DIR}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

SET(CMAKE_CXX_FLAGS
    "-Ofast -DNDEBUG -march=native -fpic -ftree-vectorize -std=c++23 -Wpedantic -pedantic-errors -Wall")

set(SOURCE
    source/evaluate.cpp
    include/operators.hpp
    include/evaluate.hpp
)
add_executable(eval ${SOURCE})

include(CTest)
enable_testing()

add_subdirectory(test)