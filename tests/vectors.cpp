#include "pdmath/Vector.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Dot products are correct and symmetrical", "[vectors]") {
    vec3 u(-1,  7,  7);
    vec3 v(-5, -4, -4);
    REQUIRE(u.dot(v) == -51.0f);
    REQUIRE(v.dot(u) == -51.0f);

    u = vec3(10, -5, 7);
    v = vec3(2,  -4, 6);
    REQUIRE(u.dot(v) == 82.0f);
    REQUIRE(v.dot(u) == 82.0f);

    u = vec3(-4, -7, 5);
    v = vec3(-3,  6, 9);
    REQUIRE(u.dot(v) == 15.0f);
    REQUIRE(v.dot(u) == 15.0f);
}

TEST_CASE("Euclidean norm is correct", "[vectors]") {
    vec3 v(-5, -10, -6);
    REQUIRE(v.length() == Catch::Approx(12.68858f).margin(vec3::epsilon));

    v = vec3(10, -1, -1);
    REQUIRE(v.length() == Catch::Approx(10.0995f).margin(vec3::epsilon));

    v = vec3(10, -6, 8);
    REQUIRE(v.length() == Catch::Approx(14.14214f).margin(vec3::epsilon));

}

TEST_CASE("Normalized vectors have length 1", "[vectors]") {
    vec3 v(-5, -5, 3);
    REQUIRE(v.length() == Catch::Approx(7.68115f).margin(vec3::epsilon));
    v.normalize();
    REQUIRE(v.length() == Catch::Approx(1.0f).margin(vec3::epsilon));

    v = vec3(2, -2, 1);
    REQUIRE(v.length() == Catch::Approx(3.0f).margin(vec3::epsilon));
    v.normalize();
    REQUIRE(v.length() == Catch::Approx(1.0f).margin(vec3::epsilon));

    v = vec3(1, -2, 5);
    REQUIRE(v.length() == Catch::Approx(5.47723f).margin(vec3::epsilon));
    v.normalize();
    REQUIRE(v.length() == Catch::Approx(1.0f).margin(vec3::epsilon));

}

TEST_CASE("Projected vectors are correct", "[vectors]") {
    vec3 v(-2, 1, -2);
    vec3 w(-4, 3, -1);
    vec3 proj = v.project_onto(w);
    vec3 perp = v.projection_perp(w);
    REQUIRE(proj == vec3(-2,  1.5f, -0.5f));
    REQUIRE(perp == vec3( 0, -0.5f, -1.5f));

    v = vec3(-5, 1, 5);
    w = vec3(-3, 1, 1);
    proj = v.project_onto(w);
    perp = v.projection_perp(w);
    REQUIRE(proj == vec3(-5.7272725f, 1.9090909f, 1.9090909f));
    REQUIRE(perp == vec3(0.7272725f, -0.9090909f, 3.0909090f));

    v = vec3( 2, 3,  3);
    w = vec3(-1, 4, -3);
    proj = v.project_onto(w);
    perp = v.projection_perp(w);
    REQUIRE(proj == vec3(-0.0384615f, 0.1538462f, -0.1153846f));
    REQUIRE(perp == vec3(2.0384614f, 2.8461537f, 3.1153846f));
}

TEST_CASE("Cross products are accurate and perpendicular", "[vectors]") {
    vec3 u(  6,  2, 6);
    vec3 v(-10, -8, 8);
    vec3 w = u.cross(v);
    REQUIRE(w == vec3(64, -108, -28));
    REQUIRE(u.is_perpendicular(w));
    REQUIRE(v.is_perpendicular(w));

    u = vec3(0, -5, -5);
    v = vec3(8,  4,  1);
    w = u.cross(v);
    REQUIRE(w == vec3(15, -40, 40));
    REQUIRE(u.is_perpendicular(w));
    REQUIRE(v.is_perpendicular(w));

    u = vec3(-5,  8, 0);
    v = vec3( 7, -7, 7);
    w = u.cross(v);
    REQUIRE(w == vec3(56, 35, -21));
    REQUIRE(u.is_perpendicular(w));
    REQUIRE(v.is_perpendicular(w));
}

TEST_CASE("Scalar multiples are collinear", "[vectors]") {
    vec3 v(8, -6, 5);
    vec3 w = v * 4;
    REQUIRE(v.is_collinear(w));
    REQUIRE(w.is_collinear(v));

    v = vec3(-3, 0, 2);
    w = v * -2;
    REQUIRE(v.is_collinear(w));
    REQUIRE(w.is_collinear(v));

    v = vec3(0.25f, -6.83f, 3.0f);
    w = v * 5.12f;
    REQUIRE(v.is_collinear(w));
    REQUIRE(w.is_collinear(v));

}
