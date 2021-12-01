set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
Include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        origin/3.3-stable
)

FetchContent_MakeAvailable(glfw)

get_target_property(
    GLFW_INCLUDE_DIRS glfw
    INTERFACE_INCLUDE_DIRECTORIES
)

set_target_properties(
    glfw PROPERTIES
    INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${GLFW_INCLUDE_DIRS}"
)

add_subdirectory(glad)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    app
    main.cpp
    src/Shader.cpp
    src/VertexBuffer.cpp
    src/IndexBuffer.cpp
    src/VertexArray.cpp
)

target_include_directories(
    app PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/app/include
)

target_include_directories(
    app SYSTEM PRIVATE
    ${CMAKE_SOURCE_DIR}/app/include/glad
)

target_link_libraries(
    app PRIVATE
    pdMath
    glad
    glfw
    ${GLFW_LIBRARIES}
)

if(UNIX)
    message(STATUS "Using gcc/Clang flags for pdmath app.")
    target_compile_options(
        app PRIVATE
        -march=native -mtune=native
        -Wall -Wextra -Wconversion -Wsign-conversion -pedantic
        $<IF:$<CONFIG:Debug>,-ggdb3,-Ofast>
    )
endif(UNIX)

if(WIN32)
    message(STATUS "Using MSVC flags for pdmath app.")
    target_compile_options(
        app PRIVATE
        /MP /permissive /sdl /Wall
        /external:W0
        /D__STDC_WANT_SECURE_LIB__#0
        /D_CRT_SECURE_NO_WARNINGS
        $<IF:$<CONFIG:Debug>,/Za /Zi,/GL /Gw /fp:fast>
    )
endif(WIN32)

set_target_properties(
    app PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_SOURCE_DIR}/bin/
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/bin/debug/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release/
)