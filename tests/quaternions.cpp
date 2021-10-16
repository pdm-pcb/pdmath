#include "pdmath/Quaternion.hpp"
#include "pdmath/Vector3.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

#include <cmath>
#include <numbers>

TEST_CASE("Quaternions are constructed properly", "[quaternions]") {
    float theta = (-7.0f * std::numbers::pi_v<float>)/8.0f;
    Vec3 axis(2.0f, 3.0f, 3.0f);

    Quat q(theta, axis);
    REQUIRE(q == Quat(0.19509f, -0.418208f, -0.627312f, -0.627312f));

    theta = std::numbers::pi_v<float>/8.0f;
    axis = Vec3(-2.0f, -1.0f, 4.0f);

    q = Quat(theta, axis);
    REQUIRE(q == Quat(0.980785f, -0.085144f, -0.042572f, 0.170288f));
};

TEST_CASE("Quaternions can be multiplied", "[quaternions]") {
    Quat q1(0.19509f, 0.653857f, 0.326928f, -0.653857f);
    Quat q2(4.0f, 3.0f, -4.0f, -2.0f);

    REQUIRE((q1 *  q2) == Quat(-1.181213f, -0.068586f, -0.126505f, -6.601821f));
    REQUIRE((q1 *= q2) == Quat(-1.181213f, -0.068586f, -0.126505f, -6.601821f));

    q1 = Quat(0.980785f, -0.0851444f, -0.042572f, 0.170289f);
    q2 = Quat(-2.0f, -2.0f, -3.0f, 1.0f);

    REQUIRE((q1 *  q2) == Quat(-2.429865f, -1.322988f, -3.112645f, 0.810496f));
    REQUIRE((q1 *= q2) == Quat(-2.429865f, -1.322988f, -3.112645f, 0.810496f));
};

TEST_CASE("Quaternions multiplied by their inverse yields the identiy",
          "[quaternions]") {
    Quat q1(0.19509f, 0.653857f, 0.326928f, -0.653857f);
    REQUIRE((q1 * q1.inverted()) == Quat::identity);

    q1 = Quat(0.980785f, -0.100373f, 0.100373f, 0.133831f);
    REQUIRE((q1 * q1.inverted()) == Quat::identity);
};

TEST_CASE("Quaternions rotate vectors properly", "[vectors][quaternions]") {
    Vec3 p(-5.0f, -4.0f, -2.0f);
    Vec3 axis(0.426401f, -0.639602f, 0.639602f);
    float theta = (-7.0f * std::numbers::pi_v<float>)/8.0f;

    Quat q(theta, axis);
    Quat p_(0.0f, p);

    Quat qp_(q * p_);
    REQUIRE(qp_ == Quat(-0.836414f, -4.739324f, 1.5197847f, 4.4192119f));

    Quat qp_qinv(qp_ * q.inverted());
    Quat result(0.0f, -3.8955910f, -5.8259802f, -4.4589624f);

    std::cout << qp_qinv << std::endl;
    std::cout << result << std::endl;

    REQUIRE(qp_qinv == result);

    p     = Vec3(2.0f, 4.0f, -7.0f);
    axis  = Vec3(0.857493f, -0.514496f, 0.0f);
    theta = -std::numbers::pi_v<float>/2.0f;

    q  = Quat(theta, axis);
    p_ = Quat(0.0f, p);

    qp_ = Quat(q * p_);
    REQUIRE(qp_ == Quat(-0.2425363f, -1.1324118f, -1.4159467f, -8.1027107f));

    qp_qinv = Quat(qp_ * q.inverted());
    REQUIRE(qp_qinv == Quat(0.0f, -3.8955910f, -5.8259802f, -4.4589624f));
}