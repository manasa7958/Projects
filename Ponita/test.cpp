// Copyright 2025 Ponita Ty
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NBodyTest
#include <sstream>
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
