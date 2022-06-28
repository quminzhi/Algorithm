cmake_minimum_required(VERSION 3.22.0)

set(LIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/includes")

add_library(
    problems SHARED
    includes/problems.hpp
    src/problems.cpp
)
target_include_directories(problems PUBLIC "${LIB_INCLUDE_DIR}")

add_library(
    search SHARED
    includes/search.hpp
    src/search.cpp
)
target_include_directories(search PUBLIC "${LIB_INCLUDE_DIR}")

# TODO: create an interface target for search problems2 problems3...
add_library(mylib INTERFACE)
target_link_libraries(
    mylib INTERFACE
    problems search   #  problems2, problems3 ...
)
target_include_directories(mylib INTERFACE "${LIB_INCLUDE_DIR}")