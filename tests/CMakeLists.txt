set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

get_target_property(
    CATCH2_IID  Catch2
    INTERFACE_INCLUDE_DIRECTORIES
)

set_target_properties(
    Catch2 PROPERTIES
    INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${CATCH2_IID}"
)

add_executable(
    tests
    points.cpp
    vectors.cpp
    lines_and_planes.cpp
    matrices.cpp
    quaternions.cpp
    camera.cpp
    collisions.cpp
    homeworks.cpp
)

target_include_directories(
    tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    tests PRIVATE
    pdMath
    Catch2::Catch2WithMain
)

if(UNIX)
    message(STATUS "Using gcc/Clang flags for pdmath tests.")
    target_compile_options(
        tests PRIVATE
        -march=native -mtune=native
        -Wall -Wextra -Wconversion -Wsign-conversion -pedantic
        $<IF:$<CONFIG:Debug>,-ggdb3,-Ofast>
    )
endif(UNIX)

if(WIN32)
    message(STATUS "Using MSVC flags for pdmath tests.")
    target_compile_options(
        tests PRIVATE
        /MP /permissive /sdl /Wall
        /external:W0
        /D__STDC_WANT_SECURE_LIB__#0
        $<IF:$<CONFIG:Debug>,/Za /Zi,/GL /Gw /fp:fast>
    )
endif(WIN32)

set_target_properties(
    tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_SOURCE_DIR}/bin/
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/bin/debug/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release/
)
