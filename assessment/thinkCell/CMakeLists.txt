cmake_minimum_required(VERSION 3.22)
project(
    ExpressionParser,
    VERSION 1.0.0
    DESCRIPTION "Custom interval map for ThinkCell."
    LANGUAGES CXX
)

message("-- CMAKE_SYSTEM_INFO_FILE: ${CMAKE_SYSTEM_INFO_FILE}")
message("-- CMAKE_SYSTEM_NAME:      ${CMAKE_SYSTEM_NAME}")
message("-- CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message("-- CMAKE_SYSTEM:           ${CMAKE_SYSTEM}")

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message("Project_Name: ${PROJECT_NAME}")
message("Project_Dir: ${PROJECT_DIR}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

    SET(CMAKE_CXX_FLAGS
        "-g -O3 -std=c++23 -Wpedantic -pedantic-errors -Wall")

set(SOURCE
    include/interval_map.hpp
)
add_executable(interval_map ${SOURCE})

if (UNIX)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()

enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(test)