set(
    PDMATH_SRC
    Point3.cpp
    Vector3.cpp
    Matrix3.cpp
    Point4.cpp
    Vector4.cpp
    Matrix4.cpp
    Quaternion.cpp
    Line.cpp
    Plane.cpp
    Camera.cpp
    BSphere.cpp
    AABBox.cpp
    OBBox.cpp
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
    tests PRIVATE
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" or
       CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Using gcc/Clang flags for pdmath library.")
        -march=native -mtune=native
        -Wall -Wextra -Wconversion -Wsign-conversion -pedantic
        "$<IF:$<CONFIG:Debug>,-ggdb3,-Ofast>"
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "Using MSVC flags for pdmath library.")
        /MP /std:c++20 /permissive /Za /sdl /Wall /Wl
        "$<IF:$<CONFIG:Debug>,/Zi,/GL /Gw /fp:fast>"
    endif()
)

set(EXPORT_COMPILE_COMMANDS ON)

set_target_properties(
    pdMath PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
)