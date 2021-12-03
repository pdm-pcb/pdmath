include(FindPackageHandleStandardArgs)

find_path(
    glm_INCLUDE_DIR
    glm/glm.hpp
)

if(EXISTS ${glm_INCLUDE_DIR})
    message(STATUS "Using local glm")
    find_package_handle_standard_args(
        glm DEFAULT_MSG
        glm_INCLUDE_DIR
    )
endif()

if(NOT glm_FOUND)
    message(STATUS "Using external glm")

    include(FetchContent)

    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        0.9.9.8
    )
    FetchContent_MakeAvailable(glm)
    FetchContent_GetProperties(glm)

    if(NOT glm_POPULATED)
        FetchContent_Populate(glm)
    endif()

endif()

get_target_property(
    glm_INCLUDE_DIRS glm
    INTERFACE_INCLUDE_DIRECTORIES
)

set_target_properties(
    glm PROPERTIES
    INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${glm_INCLUDE_DIRS}"
)