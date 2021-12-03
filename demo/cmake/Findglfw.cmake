include(FindPackageHandleStandardArgs)

find_path(
    glfw_INCLUDE_DIR
    GLFW/glfw3.h
)

find_library(
    glfw_LIBRARY
    NAMES glfw
)

if(EXISTS ${glfw_INCLUDE_DIR})
    message(STATUS "Using local GLFW")
    find_package_handle_standard_args(
        glfw DEFAULT_MSG
        glfw_INCLUDE_DIR
        glfw_LIBRARY
    )
endif()

if(NOT glfw_FOUND)
    message(STATUS "Using external GLFW")

    include(FetchContent)

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        origin/3.3-stable
    )
    FetchContent_MakeAvailable(glfw)
    FetchContent_GetProperties(glfw)

    set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    if(NOT glfw_POPULATED)
        FetchContent_Populate(glfw)

        add_subdirectory(
            ${glfw_SOURCE_DIR}
            ${glfw_BINARY_DIR}
        )
    endif()

endif()

get_target_property(
    glfw_INCLUDE_DIRS glfw
    INTERFACE_INCLUDE_DIRECTORIES
)

set_target_properties(
    glfw PROPERTIES
    INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${glfw_INCLUDE_DIRS}"
)
