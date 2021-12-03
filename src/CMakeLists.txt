add_library(
    pdMath STATIC
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

target_include_directories(
    pdMath PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

if(UNIX)
    message(STATUS "Using gcc/Clang flags for pdmath pdmath library.")
    target_compile_options(
        tests PRIVATE
        -march=native -mtune=native
        -Wall -Wextra -Wconversion -Wsign-conversion -pedantic
        $<IF:$<CONFIG:Debug>,-ggdb3,-Ofast>
    )
endif(UNIX)

if(WIN32)
    message(STATUS "Using MSVC flags for pdmath pdmath library.")
    target_compile_options(
        tests PRIVATE
        /MP /permissive /sdl /Wall /wd4514 /wd4505
        /external:W0
        /D__STDC_WANT_SECURE_LIB__#0
        /D_CRT_SECURE_NO_WARNINGS
        $<IF:$<CONFIG:Debug>,/Za /Zi,/GL /Gw /fp:fast>
    )
endif(WIN32)

set(EXPORT_COMPILE_COMMANDS ON)

set_target_properties(
    pdMath PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
)