# ToDo: Make test depent on build?
# ToDo: including src dir is ugly, at least <bosswestfalen/string_builder.hpp>

#--------------------
# Global set-up
#--------------------
include_directories(${CMAKE_SOURCE_DIR}/src)

#--------------------
# Unit Tests
#--------------------
set(UNIT_DIR "${CMAKE_SOURCE_DIR}/test/src/unit")
set(TP_DIR "${CMAKE_SOURCE_DIR}/test/third_party")
add_library(catch_main OBJECT "${UNIT_DIR}/main.cpp")
target_include_directories(catch_main PRIVATE "${TP_DIR}/catch")

file(GLOB files "${UNIT_DIR}/test_*.cpp")
foreach(file_path ${files})
    get_filename_component(test_name ${file_path} NAME_WE)
    add_executable(${test_name} $<TARGET_OBJECTS:catch_main> ${file_path})
    target_include_directories(${test_name} PRIVATE "${TP_DIR}/catch")
    add_test(NAME "unit${test_name}" COMMAND ${test_name})
endforeach()

