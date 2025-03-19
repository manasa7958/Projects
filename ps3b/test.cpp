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


/*BOOST_AUTO_TEST_CASE(TestAntiGravity) {
    std::stringstream ss;
    ss << "2 3.00e+11\n";
    ss << "1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 5.0000e+24 sun.gif\n";
    ss << "-1.0000e+11 0.0000e+00 0.0000e+00 0.0000e+00 5.0000e+24 earth.gif\n";

    NB::Universe universe;
    ss >> universe;
    
    universe.enableAntiGravity(true);

    for (int i = 0; i < 5000; i++) {
        universe.step(50000);
    }

    BOOST_CHECK_GT(universe[0].position().x, 1.0000e+11);
    BOOST_CHECK_LT(universe[1].position().x, -1.0000e+11);
}*/

BOOST_AUTO_TEST_CASE(Test1Year) {
    std::stringstream input;
    input << "2 1.496e+11\n";
    input << "1.4960e+11 0.0 0.0 2.978e+04 5.9740e+24 earth.gif\n";
    input << "0.0 0.0 0.0 0.0 1.9890e+30 sun.gif\n";

    NB::Universe universe;
    input >> universe;

    double one_year = 365.25 * 24 * 60 * 60;
    int steps = 365;
    double dt = one_year / steps;

    for (int i = 0; i < steps; i++) {
        universe.step(dt);
    }

    sf::Vector2f final_position = universe[0].position();
    sf::Vector2f final_velocity = universe[0].velocity();

    double distance_from_sun = std::sqrt(
        final_position.x * final_position.x + final_position.y * final_position.y
    );

    BOOST_REQUIRE_CLOSE(distance_from_sun, 1.496e+11, 0.1);
    BOOST_REQUIRE_CLOSE(final_velocity.x, 0.0, 0.1);
}

BOOST_AUTO_TEST_CASE(TestPrecision) {
    std::stringstream input;
    input << "2 1.0e+11\n";
    input << "0.0 0.0 0.0 0.0 1.0e+30 sun.gif\n";
    input << "1.0e+10 0.0 0.0001 0.0 5.9740e+24 earth.gif\n";

    NB::Universe universe;
    input >> universe;

    double total_time = 1.0e+6;
    int steps = 1000;
    double dt = total_time / steps;

    sf::Vector2f initial_position = universe[1].position();
    sf::Vector2f initial_velocity = universe[1].velocity();

    for (int i = 0; i < steps; i++) {
        universe.step(dt);
    }

    sf::Vector2f final_position = universe[1].position();
    sf::Vector2f final_velocity = universe[1].velocity();

    double displacement_x = std::abs(final_position.x - initial_position.x);
    double displacement_y = std::abs(final_position.y - initial_position.y);
    double velocity_change_x = std::abs(final_velocity.x - initial_velocity.x);
    double velocity_change_y = std::abs(final_velocity.y - initial_velocity.y);

    BOOST_CHECK_SMALL(displacement_x, 1.0);
    BOOST_CHECK_SMALL(displacement_y, 1.0);
    BOOST_CHECK_SMALL(velocity_change_x, 1e-5);
    BOOST_CHECK_SMALL(velocity_change_y, 1e-5);
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
