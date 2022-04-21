cmake_minimum_required(VERSION 3.22.0)

set(CMAKE_BUILD_TYPE Debug)
set(This solutionTests)

set(SOURCES
    ${This}.cpp
)

add_executable(${This} ${SOURCES})
target_link_libraries(${This} PUBLIC
    gtest_main
    ${PROJECT_NAME}
)

add_test(
    NAME ${This}
    COMMAND ${This}
)