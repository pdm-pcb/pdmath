#include "pdmath/Matrix.hpp"
#include "pdmath/Vector.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

#include <numbers>
#include <cmath>

using namespace pdm;
using namespace Catch;

TEST_CASE("Spaceship 'forward' vector manipulation", "[vectors][matrices]") {
    // 'forward' vector
    Vec3 z_vec(-1, -4, -1);
    // 'up' vector
    Vec3 y_vec(-4, 2, -4);
    // because j-hat cros k-hat is i-hat
    Vec3 x_vec = y_vec.cross(z_vec);

    // now we need to rotate left about the 'up' axis by pi/5 radians
    float theta     = std::numbers::pi_v<float> / 5.0f;
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);

    Vec3 k = y_vec;
    k.normalize();
    Vec3 k_cross_v = k.cross(z_vec);
    float k_dot_v  = k.dot(z_vec);

    Vec3 zrot = z_vec * cos_theta + k_cross_v * sin_theta +
                k * k_dot_v * (1 - cos_theta);

    REQUIRE(zrot == Vec3(-2.5723727, -3.2360680, 0.9543387));
}