add_library(
    fact STATIC
    src/fact.cpp
    include/fact.hpp
)

# ${CMAKE_CURRENT_SOURCE_DIR} means "/Users/minzhiqu/Desktop/Study/OS/Test3/lib"
target_include_directories(fact PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
# target_compile_definitions(fact PUBLIC FACT_VERSION=4)

add_library(
    liba STATIC
    src/a.cpp
    include/a.hpp
)
target_include_directories(liba PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(liba PRIVATE libe)

add_library(
    libb STATIC
    src/b.cpp
    include/b.hpp
)
target_include_directories(libb PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")