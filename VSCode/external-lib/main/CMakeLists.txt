add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    fact liba libb
    # lib_external is an inteface target which groups libc and libd
    lib_external
)