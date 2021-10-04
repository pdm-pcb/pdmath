add_executable(
    solver
    main.cpp
)

target_include_directories(
    solver PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    solver PRIVATE
    pdMath-logging
)

set_target_properties(
    solver PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/
)

