set(
    PDMATH_SRC
    Point.cpp
    Vector.cpp
    Line.cpp
    Plane.cpp
)

add_library(
    pdMath STATIC
    ${PDMATH_SRC}
)

target_include_directories(
    pdMath PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(
    pdMath PRIVATE
    -march=native -mtune=native
    -Wall -Wextra -Wconversion -Wsign-conversion -pedantic
    "$<IF:$<CONFIG:Debug>,-ggdb3,-Ofast>"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_target_properties(
    pdMath PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    CXX_CLANG_TIDY clang-tidy
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
)

add_library(
    pdMath-logging STATIC
    ${PDMATH_SRC}
)

target_include_directories(
    pdMath-logging PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions(
    pdMath-logging PRIVATE
    -DSOLVER_LOG
)

target_compile_options(
    pdMath-logging PRIVATE
    -march=native -mtune=native
    -Wall -Wextra -Wconversion -Wsign-conversion -pedantic
    "$<IF:$<CONFIG:Debug>,-ggdb3,-Ofast>"
)

set_target_properties(
    pdMath-logging PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
)

