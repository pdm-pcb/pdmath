include(FetchContent)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        v0.1.34
)
FetchContent_MakeAvailable(glad)
FetchContent_GetProperties(glad)

target_link_libraries(
    glad PUBLIC
    ${CMAKE_DL_LIBS}
)

if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    set(GLAD_PROFILE "core")
    set(GLAD_API "gl=4.6")
    set(GLAD_GENERATOR "c")
    add_subdirectory(
        ${glad_SOURCE_DIR}
        ${glad_BINARY_DIR}
    )
endif()

get_target_property(
    glad_INCLUDE_DIRS glad
    INTERFACE_INCLUDE_DIRECTORIES
)

set_target_properties(
    glad PROPERTIES
    INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${glad_INCLUDE_DIRS}"
)