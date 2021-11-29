set(EXPORT_COMPILE_COMMANDS OFF)

add_library(
    glad STATIC
    glad.c
)

target_include_directories(
    glad SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/app/include
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
        /MP /permissive /sdl /Wall
        /D__STDC_WANT_SECURE_LIB__#0
        $<IF:$<CONFIG:Debug>,/Za /Zi,/GL /Gw /fp:fast>
    )
endif(WIN32)

set_target_properties(
    pdMath PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
)