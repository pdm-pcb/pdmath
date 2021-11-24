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
)

target_include_directories(
    app SYSTEM PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    app PRIVATE
    pdMath
    glad
    glfw
    ${GLFW_LIBRARIES}
)