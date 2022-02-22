cmake_minimum_required(VERSION 3.21.3)

project(test VERSION 1.0.0)

# add external library
add_subdirectory(external)

# add internal library after external library for some library in internal call functions in external library
add_subdirectory(lib)

# then add executable
add_subdirectory(main)