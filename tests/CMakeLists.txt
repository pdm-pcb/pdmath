Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

add_executable(
    tests
    vectors.cpp
)

target_include_directories(
    tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    tests PRIVATE
    PDMath
    Catch2::Catch2WithMain
)

set_target_properties(
    tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

