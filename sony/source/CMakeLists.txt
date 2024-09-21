cmake_minimum_required(VERSION 3.30)
project(Evaluate)

set(SOURCE
    source/evaluate.cpp
)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} ${SOURCE})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)