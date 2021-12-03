set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(glad REQUIRED)
find_package(glfw REQUIRED)
find_package(imgui REQUIRED)
find_package(glm REQUIRED)
add_subdirectory(stb_image)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    demo
    main.cpp
    src/Shader.cpp
    src/VertexBuffer.cpp
    src/IndexBuffer.cpp
    src/VertexArray.cpp
    src/Renderer.cpp
    src/GLDebugger.cpp
    src/Texture.cpp
)

target_include_directories(
    demo PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/demo/include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${glm_SOURCE_DIR}
)

target_link_libraries(
    demo PRIVATE
    pdMath
    stb_image
    glad
    glfw
    ${GLFW_LIBRARIES}
    glm
)

if(UNIX)
    message(STATUS "Using gcc/Clang flags for pdmath demo.")
    target_compile_options(
        demo PRIVATE
        -march=native -mtune=native
        -Wall -Wextra -Wconversion -Wsign-conversion -pedantic
        $<IF:$<CONFIG:Debug>,-ggdb3,-Ofast>
    )
endif(UNIX)

if(WIN32)
    message(STATUS "Using MSVC flags for pdmath demo.")
    target_compile_options(
        demo PRIVATE
        /MP /permissive /sdl /Wall /wd4820 /wd5045 /wd4514
        /external:W0
        /D__STDC_WANT_SECURE_LIB__#0
        /D_CRT_SECURE_NO_WARNINGS
        $<IF:$<CONFIG:Debug>,/Za /Zi,/GL /Gw /fp:fast>
    )
endif(WIN32)

set_target_properties(
    demo PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_SOURCE_DIR}/bin/
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/bin/debug/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release/
)