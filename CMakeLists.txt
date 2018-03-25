#ToDo: Handle CMAKE_BUILD_TYPE=Release (e.g. testing? no coverage)

#--------------------
# Global Set-Up
#--------------------
cmake_minimum_required(VERSION 3.9)

project("bosswestfalen::to_string" VERSION 0.1.0 LANGUAGES CXX)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

set(TARGET_NAME "to_string")

add_library(${TARGET_NAME} INTERFACE)

#--------------------
# Documentation
#--------------------
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/doc")
    set(DOXYGEN_STRIP_FROM_PATH "src")
    doxygen_add_docs(doc "${CMAKE_SOURCE_DIR}/src")
endif()

#--------------------
# Test
# found a lot at https://github.com/nlohmann/json
#--------------------
include(CTest)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

