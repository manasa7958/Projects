// Copyright 2025 Ponita Ty
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NBodyTest
#include <sstream>
#include <cmath>
#include <boost/test/unit_test.hpp>
#include "Universe.hpp"
#include "CelestialBody.hpp"

struct CelestialBodyFixture {
    const double x_pos = 1.4960e+11;
    const double y_pos = 0.0;
    const double x_vel = 0.0;
    const double y_vel = 2.9800e+04;
    const double mass = 5.9740e+24;
    const std::string image = "earth.gif";

    std::stringstream ss;

    CelestialBodyFixture() {
        ss << x_pos << " " << y_pos << " "
           << x_vel << " " << y_vel << " "
           << mass << " " << image;
    }
};

BOOST_FIXTURE_TEST_SUITE(CelestialBodyTests, CelestialBodyFixture)

BOOST_AUTO_TEST_CASE(TestDefaultConstructor) {
    NB::CelestialBody body;

    const float maxValue = 1e35f;
    float mass = body.mass();

    BOOST_CHECK_GE(mass, -maxValue);
    BOOST_CHECK_LE(mass, maxValue);

    BOOST_CHECK_GE(body.position().x, -maxValue);
    BOOST_CHECK_LE(body.position().x, maxValue);
    BOOST_CHECK_GE(body.position().y, -maxValue);
    BOOST_CHECK_LE(body.position().y, maxValue);

    BOOST_CHECK_GE(body.velocity().x, -maxValue);
    BOOST_CHECK_LE(body.velocity().x, maxValue);
    BOOST_CHECK_GE(body.velocity().y, -maxValue);
    BOOST_CHECK_LE(body.velocity().y, maxValue);
}

BOOST_AUTO_TEST_CASE(TestInputOperator) {
    NB::CelestialBody body;
    ss >> body;

    BOOST_CHECK_CLOSE(body.position().x, static_cast<float>(x_pos), 0.001f);
    BOOST_CHECK_SMALL(body.position().y, 1e-5f);
    BOOST_CHECK_SMALL(body.velocity().x, 1e-5f);
    BOOST_CHECK_CLOSE(body.velocity().y, static_cast<float>(y_vel), 0.001f);
    BOOST_CHECK_CLOSE(body.mass(), static_cast<float>(mass), 0.001f);
}

BOOST_AUTO_TEST_CASE(TestOutputOperator) {
    NB::CelestialBody body;
    ss >> body;

    std::stringstream out;
    out << body;

    NB::CelestialBody body2;
    out >> body2;

    BOOST_CHECK_CLOSE(body2.position().x, body.position().x, 0.001f);
    BOOST_CHECK_CLOSE(body2.position().y, body.position().y, 0.001f);
    BOOST_CHECK_CLOSE(body2.velocity().x, body.velocity().x, 0.001f);
    BOOST_CHECK_CLOSE(body2.velocity().y, body.velocity().y, 0.001f);
    BOOST_CHECK_CLOSE(body2.mass(), body.mass(), 0.001f);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(UniverseTests)

BOOST_AUTO_TEST_CASE(TestDefaultConstructor) {
    NB::Universe uni;
    BOOST_CHECK_EQUAL(uni.size(), 0);
    BOOST_CHECK_GE(uni.radius(), 0.0);
}

BOOST_AUTO_TEST_CASE(TestInputOperator) {
    std::stringstream ss;
    ss << "2 2.50e+11\n";
    ss << "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";
    ss << "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 sun.gif\n";

    NB::Universe uni;
    ss >> uni;

    BOOST_CHECK_EQUAL(uni.size(), 2);
    BOOST_CHECK_CLOSE(static_cast<float>(uni.radius()), 2.50e+11f, 0.001f);
    BOOST_CHECK_CLOSE(uni[0].position().x, 1.4960e+11f, 0.001f);
    BOOST_CHECK_CLOSE(uni[0].velocity().y, 2.9800e+04f, 0.001f);
    BOOST_CHECK_CLOSE(uni[0].mass(), 5.9740e+24f, 0.001f);
}

BOOST_AUTO_TEST_CASE(TestOutputOperator) {
    std::stringstream ss;
    ss << "1 2.50e+11\n";
    ss << "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";

    NB::Universe uni;
    ss >> uni;

    std::stringstream out;
    out << uni;

    NB::Universe uni2;
    out >> uni2;

    BOOST_CHECK_EQUAL(uni2.size(), uni.size());
    BOOST_CHECK_CLOSE(static_cast<float>(uni2.radius()), static_cast<float>(uni.radius()), 0.001f);
    BOOST_CHECK_CLOSE(uni2[0].position().x, uni[0].position().x, 0.001f);
    BOOST_CHECK_CLOSE(uni2[0].velocity().y, uni[0].velocity().y, 0.001f);
    BOOST_CHECK_CLOSE(uni2[0].mass(), uni[0].mass(), 0.001f);
}

BOOST_AUTO_TEST_CASE(TestInvalidInput) {
    NB::Universe uni;
    std::stringstream ss;
    ss << "-1 2.50e+11";

    BOOST_CHECK_THROW(ss >> uni, std::exception);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(StepMethodTests)

const double G = 6.67e-11;

BOOST_AUTO_TEST_CASE(TestBasicStepSingleBody) {
    std::stringstream ss;
    ss << "1 2.50e+11\n";
    ss << "1.0000e+11 0.0000e+00 1.0000e+04 0.0000e+00 5.9740e+24 earth.gif\n";

    NB::Universe uni;
    ss >> uni;

    const double dt = 25000.0;
    uni.step(dt);

    BOOST_CHECK_CLOSE(uni[0].position().x, 1.0000e+11f + 1.0000e+04f * dt, 0.001f);
    BOOST_CHECK_SMALL(uni[0].position().y, 1e-5f);
    BOOST_CHECK_CLOSE(uni[0].velocity().x, 1.0000e+04f, 0.001f);
    BOOST_CHECK_SMALL(uni[0].velocity().y, 1e-5f);
}

BOOST_AUTO_TEST_CASE(TestTwoBodiesAttraction) {
    std::stringstream ss;
    ss << "2 2.50e+11\n";
    ss << "1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 5.9740e+24 earth.gif\n";
    ss << "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 sun.gif\n";

    NB::Universe uni;
    ss >> uni;

    const double dt = 25000.0;
    uni.step(dt);

    BOOST_CHECK_LT(uni[0].velocity().x, 0);
    BOOST_CHECK_SMALL(uni[0].velocity().y, 1e-5f);

    BOOST_CHECK_GT(uni[1].velocity().x, 0);
    BOOST_CHECK_SMALL(uni[1].velocity().y, 1e-5f);

    BOOST_CHECK_LT(uni[0].position().x, 1.0000e+11f);
}

BOOST_AUTO_TEST_CASE(TestLeapfrog) {
    std::stringstream ss;
    ss << "2 2.50e+11\n";
    ss << "0.0000e+00 1.0000e+11 0.0000e+00 0.0000e+00 5.9740e+24 small.gif\n";
    ss << "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 large.gif\n";

    NB::Universe uni;
    ss >> uni;

    double r = 1.0000e+11;
    double m2 = 1.9890e+30;
    double expectedAccel = G * m2 / (r * r);

    const double dt = 25000.0;
    uni.step(dt);

    BOOST_CHECK_SMALL(uni[0].velocity().x, 1e-5f);
    BOOST_CHECK_CLOSE(std::abs(uni[0].velocity().y), expectedAccel * dt, 5.0f);
    BOOST_CHECK_LT(uni[0].velocity().y, 0);

    BOOST_CHECK_SMALL(uni[0].position().x, 1e-5f);
    BOOST_CHECK_LT(uni[0].position().y, 1.0000e+11f);
}

BOOST_AUTO_TEST_CASE(TestOrderOfOperations) {
    std::stringstream ss;
    ss << "3 2.50e+11\n";
    ss << "1.0000e+11 0.0000e+00 0.0000e+00 1.0000e+04 5.9740e+24 body1.gif\n";
    ss << "0.0000e+00 1.0000e+11 1.0000e+04 0.0000e+00 5.9740e+24 body2.gif\n";
    ss << "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 sun.gif\n";

    NB::Universe uni;
    ss >> uni;

    sf::Vector2f pos1 = uni[0].position();
    sf::Vector2f vel1 = uni[0].velocity();
    sf::Vector2f pos2 = uni[1].position();
    sf::Vector2f vel2 = uni[1].velocity();

    const double dt = 25000.0;
    uni.step(dt);

    BOOST_CHECK_LT(uni[0].velocity().x, vel1.x);
    BOOST_CHECK_LT(uni[1].velocity().y, vel2.y);
    BOOST_CHECK_GT(uni[0].position().y, pos1.y);
    BOOST_CHECK_GT(uni[1].position().x, pos2.x);
}

BOOST_AUTO_TEST_CASE(TestForceCloseBodyBug) {
    std::stringstream ss;
    ss << "2 2.50e+11\n";
    ss << "1.0000e+10 0.0000e+00 0.0000e+00 0.0000e+00 5.9740e+24 body1.gif\n";
    ss << "-1.0000e+10 0.0000e+00 0.0000e+00 0.0000e+00 5.9740e+24 body2.gif\n";

    NB::Universe uni;
    ss >> uni;

    const double dt = 25000.0;

    sf::Vector2f pos1_init = uni[0].position();
    sf::Vector2f pos2_init = uni[1].position();

    for (int i = 0; i < 5; i++) {
        uni.step(dt);
    }

    sf::Vector2f pos1_final = uni[0].position();
    sf::Vector2f pos2_final = uni[1].position();

    float initial_distance1 = std::abs(pos1_init.x);
    float final_distance1 = std::abs(pos1_final.x);

    float initial_distance2 = std::abs(pos2_init.x);
    float final_distance2 = std::abs(pos2_final.x);

    BOOST_CHECK_LT(final_distance1, initial_distance1);
    BOOST_CHECK_LT(final_distance2, initial_distance2);

    BOOST_CHECK(-1e30f < pos1_final.x && pos1_final.x < 1e30f);
    BOOST_CHECK(-1e30f < pos1_final.y && pos1_final.y < 1e30f);
    BOOST_CHECK(-1e30f < pos2_final.x && pos2_final.x < 1e30f);
    BOOST_CHECK(-1e30f < pos2_final.y && pos2_final.y < 1e30f);
}

BOOST_AUTO_TEST_CASE(TestPrecisionLossBug) {
    std::stringstream ss;
    ss << "2 2.50e+11\n";
    ss << "1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 1.0000e+10 tiny.gif\n";
    ss << "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.0000e+40 massive.gif\n";

    NB::Universe uni;
    ss >> uni;

    sf::Vector2f initialPos = uni[0].position();

    const double dt = 25000.0;
    for (int i = 0; i < 10; i++) {
        uni.step(dt);
    }

    sf::Vector2f finalPos = uni[0].position();

    BOOST_CHECK_LT(finalPos.x, initialPos.x);
    BOOST_CHECK_SMALL(uni[1].position().x, 1e-5f);
    BOOST_CHECK_SMALL(uni[1].position().y, 1e-5f);
    BOOST_CHECK_LT(uni[0].velocity().x, 0);
}

BOOST_AUTO_TEST_CASE(TestExtremeMassDifference) {
    std::stringstream ss;
    ss << "2 2.50e+11\n";
    ss << "1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 5.9740e+24 normal.gif\n";
    ss << "2.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 1.0000e-20 tiny.gif\n";

    NB::Universe uni;
    ss >> uni;

    const double dt = 25000.0;
    uni.step(dt);

    float accel1 = std::abs(uni[0].velocity().x) / dt;
    float accel2 = std::abs(uni[1].velocity().x) / dt;

    BOOST_CHECK(accel1 >= 0.0f);
    BOOST_CHECK(accel2 >= 0.0f);
    BOOST_CHECK(accel1 < 1e30f);
    BOOST_CHECK(accel2 < 1e30f);

    BOOST_CHECK_SMALL(std::abs(uni[0].velocity().x), 1e-5f);
    BOOST_CHECK_LT(uni[1].velocity().x, 0);
}

BOOST_AUTO_TEST_CASE(TestFixedTimeSteps) {
    std::string input = "1 2.50e+11\n"
    "1.0000e+11 0.0000e+00 1.0000e+04 0.0000e+00 5.9740e+24 earth.gif\n";

    std::stringstream ss1(input);
    std::stringstream ss2(input);

    NB::Universe uni1;
    ss1 >> uni1;

    NB::Universe uni2;
    ss2 >> uni2;

    const double bigDt = 100000.0;
    uni1.step(bigDt);

    const double smallDt = bigDt / 10.0;
    for (int i = 0; i < 10; i++) {
        uni2.step(smallDt);
    }

    BOOST_CHECK_CLOSE(uni1[0].position().x, uni2[0].position().x, 0.001f);
    BOOST_CHECK_CLOSE(uni1[0].position().y, uni2[0].position().y, 0.001f);

    BOOST_CHECK_CLOSE(uni1[0].velocity().x, uni2[0].velocity().x, 0.001f);
    BOOST_CHECK_CLOSE(uni1[0].velocity().y, uni2[0].velocity().y, 0.001f);
}

BOOST_AUTO_TEST_CASE(TestOneByOneMovement) {
    std::string input = "3 2.50e+11\n"
    "0.0000e+00 1.0000e+11 0.0000e+00 0.0000e+00 5.9740e+24 body1.gif\n"
    "8.6603e+10 -5.0000e+10 0.0000e+00 0.0000e+00 5.9740e+24 body2.gif\n"
    "-8.6603e+10 -5.0000e+10 0.0000e+00 0.0000e+00 5.9740e+24 body3.gif\n";

    std::stringstream ss(input);
    NB::Universe uni;
    ss >> uni;

    const double dt = 25000.0;
    uni.step(dt);

    BOOST_CHECK_SMALL(uni[0].velocity().x, 1e-12f);
    BOOST_CHECK_CLOSE(std::abs(uni[1].velocity().x), std::abs(uni[2].velocity().x), 0.0001f);
    BOOST_CHECK_CLOSE(uni[1].velocity().y, uni[2].velocity().y, 0.0001f);
}

BOOST_AUTO_TEST_CASE(TestLeapFrogSimple) {
    std::string input = "3 2.50e+11\n"
    "-1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 1.0000e+30 left.gif\n"
    "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.0000e+20 middle.gif\n"
    "1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 1.0000e+30 right.gif\n";

    std::stringstream ss(input);
    NB::Universe uni;
    ss >> uni;

    const double dt = 25000.0;
    uni.step(dt);

    BOOST_CHECK_SMALL(uni[1].position().x, 1e-10f);
    BOOST_CHECK_SMALL(uni[1].position().y, 1e-10f);

    BOOST_CHECK_SMALL(uni[1].velocity().x, 1e-10f);
    BOOST_CHECK_SMALL(uni[1].velocity().y, 1e-10f);
}

BOOST_AUTO_TEST_CASE(TestFixedDeltasBug) {
    std::string input = "2 2.50e+11\n"
    "1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 5.9740e+24 body1.gif\n"
    "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 sun.gif\n";

    std::stringstream ss1(input);
    NB::Universe uni1;
    ss1 >> uni1;

    std::stringstream ss2(input);
    NB::Universe uni2;
    ss2 >> uni2;

    const double dt1 = 50000.0;
    uni1.step(dt1);

    const double dt2 = dt1 / 2.0;
    uni2.step(dt2);
    uni2.step(dt2);

    BOOST_CHECK_NE(uni1[0].position().x, uni2[0].position().x);
    BOOST_CHECK_NE(uni1[0].velocity().x, uni2[0].velocity().x);
}

BOOST_AUTO_TEST_SUITE_END()
