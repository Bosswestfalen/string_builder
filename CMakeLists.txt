#ToDo: Handle CMAKE_BUILD_TYPE=Release (e.g. testing? no coverage)

cmake_minimum_required(VERSION 3.9)

project("to_string" VERSION 0.1.0 LANGUAGES CXX)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

set(TARGET_NAME "to_string")

add_library(${TARGET_NAME} INTERFACE)

include(CTest)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

