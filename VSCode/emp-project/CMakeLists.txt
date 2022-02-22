cmake_minimum_required(VERSION 3.21.3)

set(This example)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(HEADERS
    ${This}.hpp
)
set(SOURCES
    ${This}.cpp
)

# since google test will provide main function
add_library(${This} STATIC
    ${HEADERS}
    ${SOURCES}
)
set_target_properties(${This} PROPERTIES LINKER_LANGUAGE CXX)

# provide test in test directory
add_subdirectory(test)