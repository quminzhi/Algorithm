cmake_minimum_required(VERSION 3.21.3)

set(This exampleTests)

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