include(FetchContent)

message(NOTICE "Fetch GLM")

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        0.9.9.8
)
FetchContent_MakeAvailable(glm)
FetchContent_GetProperties(glm)

if(NOT glm_POPULATED)
    message(STATUS "Configuring GLM")
    FetchContent_Populate(glm)
endif()

get_target_property(
    glm_INCLUDE_DIRS glm
    INTERFACE_INCLUDE_DIRECTORIES
)

set_target_properties(
    glm PROPERTIES
    INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${glm_INCLUDE_DIRS}"
)