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

    Mat3 position(x_vec, y_vec, z_vec);

    std::cout << "Pos:\n" << position << std::endl;

    // now we need to rotate left about the 'up' axis by pi/5 radians
    float theta     = std::numbers::pi_v<float> / 5.0f;
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);
    Mat3 rot_z(cos_theta,  0,  sin_theta,
               0,          1,  0,
               -sin_theta, 0,  cos_theta);

    std::cout << "Rot:\n" << rot_z << std::endl;

    Mat3 result = rot_z * position;

    std::cout << "New:\n" << result << std::endl;

    Vec3 new_z = rot_z * z_vec;

    std::cout << "ZVec:\n" << new_z << std::endl;
}