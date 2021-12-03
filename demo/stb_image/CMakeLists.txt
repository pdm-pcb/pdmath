add_library(
    stb_image STATIC
    stb_image.c
)

target_include_directories(
    stb_image SYSTEM PRIVATE
    ${CMAKE_SOURCE_DIR}/demo/include
)

if(UNIX)
    target_compile_options(
        stb_image PRIVATE
        -march=native -mtune=native
        -Ofast
    )
endif(UNIX)

if(WIN32)
    target_compile_options(
        stb_image PRIVATE
        /MP /permissive /sdl
        /D__STDC_WANT_SECURE_LIB__#0
        /D_CRT_SECURE_NO_WARNINGS
        /GL /Gw /fp:fast
    )
endif(WIN32)

set_target_properties(
    stb_image PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED on
    C_EXTENSIONS off
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib
)