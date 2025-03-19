// Copyright 2025 Manasa Praveen
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "CelestialBody.hpp"
#include "Universe.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NBodyTests
#include <boost/algorithm/string.hpp>
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(TestCelestialConstructor) {
    NB::CelestialBody obj;
    BOOST_CHECK_SMALL(static_cast<double>(obj.mass()), 1e-10);
    BOOST_CHECK_EQUAL(obj.position().x, 0.0f);
    BOOST_CHECK_EQUAL(obj.position().y, 0.0f);
}

BOOST_AUTO_TEST_CASE(TestCelestialInputOperator) {
    std::stringstream ss("2.0 3.0 4.0 5.0 6.0 mars.gif");
    NB::CelestialBody obj;
    ss >> obj;
    BOOST_CHECK_CLOSE(obj.position().x, 2.0f, 0.001f);
    BOOST_CHECK_CLOSE(obj.position().y, 3.0f, 0.001f);
    BOOST_CHECK_CLOSE(obj.velocity().x, 4.0f, 0.001f);
    BOOST_CHECK_CLOSE(obj.velocity().y, 5.0f, 0.001f);
    BOOST_CHECK_CLOSE(obj.mass(), 6.0f, 0.001f);
}

BOOST_AUTO_TEST_CASE(TestUniverseConstructor) {
    NB::Universe universe;
    BOOST_CHECK_EQUAL(universe.size(), 0);
    BOOST_CHECK_GE(universe.radius(), 0.0);
}

BOOST_AUTO_TEST_CASE(TestUniverseEvolution) {
    std::stringstream ss;
    ss << "2 3.00e+11\n";
    ss << "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";
    ss << "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 sun.gif\n";

    NB::Universe universe;
    ss >> universe;

    const double dt = 25000.0;
    universe.step(dt);

    BOOST_CHECK_LT(universe[0].position().x, 1.4960e+11);
}

BOOST_AUTO_TEST_CASE(TestNoAcceleration) {
    std::stringstream ss;
    ss << "1 1.00e+11\n";
    ss << "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 5.0000e+24 venus.gif\n";

    NB::Universe universe;
    ss >> universe;
    universe.step(10000);
    BOOST_CHECK_EQUAL(universe[0].position().x, 0.0f);
    BOOST_CHECK_EQUAL(universe[0].position().y, 0.0f);
}


BOOST_AUTO_TEST_CASE(TestAntiGravity) {
    std::stringstream ss;
    ss << "2 3.00e+11\n";
    ss << "1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 5.0000e+24 sun.gif\n";
    ss << "-1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 5.0000e+24 earth.gif\n";

    NB::Universe universe;
    ss >> universe;
    
    universe.enableAntiGravity(true);  // ✅ Ensure anti-gravity is turned on

    for (int i = 0; i < 5000; i++) {  // Run more steps to see noticeable separation
        universe.step(50000);
    }

    BOOST_CHECK_GT(universe[0].position().x, 1.0000e+11);
    BOOST_CHECK_LT(universe[1].position().x, -1.0000e+11);
}

BOOST_AUTO_TEST_CASE(TestInvertedGravity) {
    std::stringstream ss;
    ss << "2 3.00e+11\n";
    ss << "1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 5.0000e+24 sun.gif\n";
    ss << "-1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 5.0000e+24 earth.gif\n";

    NB::Universe universe;
    ss >> universe;
    universe.step(10000);
    BOOST_CHECK_LT(universe[0].position().x, 1.0000e+11);
    BOOST_CHECK_GT(universe[1].position().x, -1.0000e+11);
}

BOOST_AUTO_TEST_CASE(TestFixedTimeStep) {
    std::stringstream ss;
    ss << "1 1.00e+11\n";
    ss << "0.0000e+00 0.0000e+00 1.0000e+04 0.0000e+00 5.0000e+24 saturn.gif\n";

    NB::Universe universe;
    ss >> universe;
    universe.step(1);
    BOOST_CHECK_CLOSE(universe[0].position().x, 1.0000e+04, 0.001f);
}

BOOST_AUTO_TEST_CASE(TestLeapfrogIntegration) {
    std::stringstream ss;
    ss << "1 1.00e+11\n";
    ss << "0.0000e+00 0.0000e+00 1.0000e+04 0.0000e+00 5.0000e+24 mars.gif\n";

    NB::Universe universe;
    ss >> universe;
    double dt = 1;
    for (int i = 0; i < 10; ++i) {
        universe.step(dt / 2);
        universe.step(dt / 2);
    }
    BOOST_CHECK_CLOSE(universe[0].position().x, 1.0000e+05, 0.001f);
}

BOOST_AUTO_TEST_CASE(TestExtraCredit) {
    std::stringstream input("2 1.0e+11\n"
        "0.0 0.0 0.0 0.0 0.0 earth.gif\n"
        "1.0e+11 0.0 0.0 0.0 0.0 mars.gif\n");

    NB::Universe universe;
    input >> universe;
    universe.step(1.0e+6);

    BOOST_REQUIRE_CLOSE(static_cast<double>(universe[0].position().x),
    0.0, 0.0001);
    BOOST_REQUIRE_CLOSE(static_cast<double>(universe[0].position().y),
    0.0, 0.0001);
    BOOST_REQUIRE_CLOSE(static_cast<double>(universe[1].position().x),
    1.0e+11, 0.0001);
}
