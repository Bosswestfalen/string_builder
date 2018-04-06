# ToDo: Make test depent on build?
# ToDo: including src dir is ugly, at least <bosswestfalen/string_builder.hpp>
# ToDo: Check for coverage tools, what about branch coverage?

#--------------------
# Global set-up
#--------------------
option(SB_TEST_COVERAGE "Build test suite with code coverage information" ON)

if(SB_TEST_COVERAGE)
    message(STATUS "Building with code coverage information")
    if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        message(FATAL_ERROR "SB_TEST_COVERAGE requires GCC.")
    endif()

    # Only use flags needed for code coverage
    set(CMAKE_CXX_FLAGS "--coverage -g -O0 -fprofile-arcs -ftest-coverage")
    #assume gcov is available
    set(SB_INFO_FILE "${TARGET_NAME}.info")
    add_custom_target(lcov_html
        COMMAND lcov --directory . --capture --output-file ${SB_INFO_FILE} --gcov-tool gcov --rc lcov_branch_coverage=0
        COMMAND lcov -e ${SB_INFO_FILE} ${CMAKE_SOURCE_DIR}/src/${SOURCE_FILE_NAME} --output-file ${SB_INFO_FILE} --rc lcov_branch_coverage=0
        COMMAND genhtml --title "${PROJECT_NAME}" --legend --demangle-cpp -output-directory html  ${SB_INFO_FILE}
        COMMENT "Generating HTML report test/html/index.html")
endif()

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

