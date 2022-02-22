set(LIB_EXTERNAL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/include")

# TODO: add external library libc
add_library(
    libc SHARED
    lib/src/c.cpp
    lib/include/c.hpp
)
target_include_directories(libc PUBLIC ${LIB_EXTERNAL_INCLUDE_DIR})

# TODO: add external library libd
add_library(
    libd SHARED
    lib/src/d.cpp
    lib/include/d.hpp
)
target_include_directories(libd PUBLIC ${LIB_EXTERNAL_INCLUDE_DIR})

# TODO: add external library libd
add_library(
    libe SHARED
    lib/src/e.cpp
    lib/include/e.hpp
)
target_include_directories(libe PUBLIC ${LIB_EXTERNAL_INCLUDE_DIR})

# TODO: create an interface target for libc and libd
add_library(lib_external INTERFACE)
target_link_libraries(
    lib_external INTERFACE
    libc libd
)
target_include_directories(lib_external INTERFACE ${LIB_EXTERNAL_INCLUDE_DIR})