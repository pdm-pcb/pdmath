set(
    pdmath_src
    ${CMAKE_SOURCE_DIR}/src/Vector.cpp
)

add_library(
    PDMath STATIC
    ${pdmath_src}
)

target_include_directories(
    PDMath PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(
    PDMath PRIVATE
    -march=native -mtune=native
    -Wall -Wextra -Wconversion -Wsign-conversion -pedantic
    -fdiagnostics-color=always
    -ggdb3
)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_target_properties(
    PDMath PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
)
