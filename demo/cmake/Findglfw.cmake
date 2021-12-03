include(FetchContent)

message(NOTICE "Fetch GLFW")

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        origin/3.3-stable
)
FetchContent_MakeAvailable(glfw)
FetchContent_GetProperties(glfw)

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "GLFW - no docs" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "GLFW - no tests" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW - no examples" FORCE)

if(NOT glfw_POPULATED)
    message(STATUS "Configuring GLFW")
    FetchContent_Populate(glfw)

    add_subdirectory(
        ${glfw_SOURCE_DIR}
        ${glfw_BINARY_DIR}
    )
endif()
