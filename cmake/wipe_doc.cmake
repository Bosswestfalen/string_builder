# Delete doc/html
# Doxygen seems not to delete files that are not needed anymore (e.g. the bug page).
# This script wipes the generated html files, so that no zombie-files remain in the git repo
# ToDo:
# - is there a doxygen command for that? (Did not find one so far)
# - is cmake_minimum_required required?

cmake_minimum_required(VERSION 3.9)

file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/../doc/html")

