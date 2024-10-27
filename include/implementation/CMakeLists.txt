cmake_minimum_required(VERSION 3.22)
project(
    Implementations,
    VERSION 1.0.0
    DESCRIPTION "Implementations of common structures and paradigms + tests."
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

if (Apple)
    SET(CMAKE_CXX_FLAGS
        "-g -O3 -ffp-model=precise -std=c++23 -Wpedantic -pedantic-errors -Wall")
else()
    SET(CMAKE_CXX_FLAGS
        "-g -O3 -std=c++23 -Wpedantic -pedantic-errors -Wall")
endif()

set(SOURCE
    graphs/adjacencyImpl.hpp
    graphs/basicGraphImpl.hpp
    graphs/graphImpl.hpp
    graphs/vertexImpl.hpp
    lists/linkedListImpl.hpp
    lists/nodesImpl.hpp
    tables/hashTableImpl.hpp
    trees/basicTreeImpl.hpp
    trees/treeAVLImpl.hpp
    main.cpp
)

add_executable(implementations ${SOURCE})

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