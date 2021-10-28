#include "pdmath/Camera.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Camera gives correct View-to-World matrix", "[camera][matrices]") {
    Camera camera(Vec3(2, -1, -4), Vec3(-569, 399, -61), Vec3(0, 1, 0));

    Mat4 vtw(0.099331f, 0.569014f,  0.816305f,  2.0f,
             0.0f,      0.820363f, -0.571843f, -1.0f,
            -0.995054f, 0.056801f,  0.081487f, -4.0f,
             0.0f,       0.0f,        0.0f,     1.0f);

    REQUIRE(camera.view_to_world() == vtw);
}