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

BOOST_AUTO_TEST_CASE(testEmptyUniverse) {
    std::stringstream input("0 1.0e+11\n");
    NB::Universe universe;
    input >> universe;
    BOOST_TEST(universe.size() == 0);
}

BOOST_AUTO_TEST_CASE(testFlippedValues) {
    std::stringstream input(
        "1.1111e+11 2.2222e+11 3.3333e+04 4.4444e+04 5.5555e+24 earth.gif");
    NB::CelestialBody body;
    input >> body;

    double expected_x_pos = 1.1111e+11;
    double expected_y_pos = 2.2222e+11;
    double expected_x_vel = 3.3333e+04;
    double expected_y_vel = 4.4444e+04;
    double expected_mass = 5.5555e+24;

    BOOST_REQUIRE_CLOSE(body.position().x, expected_x_pos, 0.001);
    BOOST_REQUIRE_CLOSE(body.position().y, expected_y_pos, 0.001);
    BOOST_REQUIRE_CLOSE(body.velocity().x, expected_x_vel, 0.001);
    BOOST_REQUIRE_CLOSE(body.velocity().y, expected_y_vel, 0.001);
    BOOST_REQUIRE_CLOSE(body.mass(), expected_mass, 0.001);
}

BOOST_AUTO_TEST_CASE(testSingleBodyNoMotion) {
    std::stringstream input("1 1.0e+11\n"
                            "1.0e+11 0.0 0.0 0.0 5.974e+24 earth.gif\n");

    NB::Universe universe;
    input >> universe;

    sf::Vector2f initial_pos = universe[0].position();
    sf::Vector2f initial_vel = universe[0].velocity();

    for (int i = 0; i < 10; i++) {
        universe.step(1.0e+6);
    }

    sf::Vector2f final_pos = universe[0].position();
    sf::Vector2f final_vel = universe[0].velocity();

    BOOST_CHECK_EQUAL(final_pos.x, initial_pos.x);
    BOOST_CHECK_EQUAL(final_pos.y, initial_pos.y);
    BOOST_CHECK_EQUAL(final_vel.x, initial_vel.x);
    BOOST_CHECK_EQUAL(final_vel.y, initial_vel.y);
}

BOOST_AUTO_TEST_CASE(testTwoBodyAttraction) {
    std::stringstream input("2 1.0e+11\n"
        "0.0 0.0 0.0 0.0 0.0 earth.gif\n"
        "1.0e+11 0.0 0.0 0.0 0.0 mars.gif\n");

    NB::Universe universe;
    input >> universe;

    sf::Vector2f initial_pos1 = universe[0].position();
    sf::Vector2f initial_pos2 = universe[1].position();

    for (int i = 0; i < 10; i++) {
        universe.step(1.0e+6);
    }

    sf::Vector2f final_pos1 = universe[0].position();
    sf::Vector2f final_pos2 = universe[1].position();

    BOOST_CHECK_LT(final_pos1.x, initial_pos1.x); // Body 1 moves left
    BOOST_CHECK_GT(final_pos2.x, initial_pos2.x); // Body 2 moves right
}

BOOST_AUTO_TEST_CASE(testMultiBodyBalance) {
    std::stringstream input("3 2.50e+11\n"
                            "0.0 0.0 0.0 0.0 1.0e+30 sun.gif\n"
                            "-8.6603e+10 -5.0000e+10 0.0 0.0 5.974e+24 earth.gif\n"
                            "8.6603e+10 -5.0000e+10 0.0 0.0 5.974e+24 mercury.gif\n");

    NB::Universe universe;
    input >> universe;

    for (int i = 0; i < 20; i++) {
        universe.step(1.0e+6);
    }

    BOOST_CHECK_CLOSE(std::abs(universe[0].velocity().x), std::abs(universe[1].velocity().x), 0.001);
    BOOST_CHECK_CLOSE(universe[1].velocity().y, universe[2].velocity().y, 0.001);
}

BOOST_AUTO_TEST_CASE(testExtremeMassDifference) {
    std::stringstream input("2 1.0e+11\n"
        "0.0 0.0 0.0 0.0 1.0e+30 sun.gif\n"
        "1.0e+11 0.0 0.0 0.0 1.0e+30 mercury.gif\n");

    NB::Universe universe;
    input >> universe;

    const double dt = 25000.0;
    universe.step(dt);

    float accel1 = std::abs(universe[0].velocity().x) / dt;
    float accel2 = std::abs(universe[1].velocity().x) / dt;

    BOOST_CHECK(accel1 >= 0.0f);
    BOOST_CHECK(accel2 >= 0.0f);
    BOOST_CHECK(accel1 < 1e30f);
    BOOST_CHECK(accel2 < 1e30f);
}

BOOST_AUTO_TEST_CASE(testExtraCredit) {
    std::stringstream input("2 1.0e+11\n"
        "0.0 0.0 0.0 0.0 0.0 earth.gif\n"
        "1.0e+11 0.0 0.0 0.0 0.0 mars.gif\n");

    NB::Universe universe;
    input >> universe;
    universe.step(1.0e+6);

    BOOST_REQUIRE_CLOSE(static_cast<double>(universe[0].position().x), 0.0, 0.0001);
    BOOST_REQUIRE_CLOSE(static_cast<double>(universe[0].position().y), 0.0, 0.0001);
    BOOST_REQUIRE_CLOSE(static_cast<double>(universe[1].position().x), 1.0e+11, 0.0001);
}

BOOST_AUTO_TEST_CASE(testFixedDeltaAndLeapfrog) {
    std::stringstream input("2 1.0e+11\n"
        "0.0 0.0 0.0 0.0 1.0e+30 sun.gif\n"
        "1.0e+11 0.0 0.0 0.0 1.0e+30 mercury.gif\n");

    NB::Universe universe;
    input >> universe;

    for (int i = 0; i < 10; ++i) {
        universe.step(-1.0e+6);
    }

    BOOST_REQUIRE(universe[0].position().x < 0.0);
    BOOST_REQUIRE(universe[1].position().x > 1.0e+11);
}
