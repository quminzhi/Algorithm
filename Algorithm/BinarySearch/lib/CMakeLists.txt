cmake_minimum_required(VERSION 3.22.0)

set(LIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/includes")

add_library(
    foo SHARED
    includes/foo.hpp
    src/foo.cpp
)
target_include_directories(foo PUBLIC "${LIB_INCLUDE_DIR}")

add_library(
    binarysearch SHARED
    includes/binarysearch.hpp
    src/binarysearch.cpp
)
target_include_directories(binarysearch PUBLIC "${LIB_INCLUDE_DIR}")

# TODO: create an interface target for binarysearch foo2 foo3...
add_library(mylib INTERFACE)
target_link_libraries(
    mylib INTERFACE
    foo binarysearch   #  foo2, foo3 ...
)
target_include_directories(mylib INTERFACE "${LIB_INCLUDE_DIR}")