add_library(
    pdMath STATIC
    Point.cpp
    Vector.cpp
)

target_include_directories(
    pdMath PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(
    pdMath PRIVATE
    -march=native -mtune=native
    -Wall -Wextra -Wconversion -Wsign-conversion -pedantic
    -fdiagnostics-color=always
    -ggdb3
)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_target_properties(
    pdMath PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
)
