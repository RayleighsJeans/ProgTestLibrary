cmake_minimum_required(VERSION 3.30)
project(ThinkCellIntervalMap)

set(SOURCE
    source/interval_map.cpp
)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} ${SOURCE})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)