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

BOOST_AUTO_TEST_CASE(testNoAcceleration) {
    std::stringstream input("1 1.0e+11\n"
        "0.0 0.0 0.0 0.0 1.0e+30 earth.gif\n");

    NB::Universe universe;
    input >> universe;

    sf::Vector2f initial_position = universe[0].position();
    sf::Vector2f initial_velocity = universe[0].velocity();

    std::cerr << "TEST: Initial Position: (" << initial_position.x << ", " << initial_position.y << ")\n";
    std::cerr << "TEST: Initial Velocity: (" << initial_velocity.x << ", " << initial_velocity.y << ")\n";
    
    for (int i = 0; i < 10; i++) {
        universe.step(1.0e+6);
    }

    sf::Vector2f final_position = universe[0].position();
    sf::Vector2f final_velocity = universe[0].velocity();

    std::cerr << "TEST: Final Position: (" << final_position.x << ", " << final_position.y << ")\n";
    std::cerr << "TEST: Final Velocity: (" << final_velocity.x << ", " << final_velocity.y << ")\n";

    BOOST_CHECK_SMALL(final_velocity.x, 1e-10f);
    BOOST_CHECK_SMALL(final_velocity.y, 1e-10f);
    BOOST_CHECK_SMALL(final_position.x - initial_position.x, 1e-10f);
    BOOST_CHECK_SMALL(final_position.y - initial_position.y, 1e-10f);
}

/*BOOST_AUTO_TEST_CASE(testAntigrav) {
    std::stringstream input("2 1.0e+11\n"
        "0.0 0.0 0.0 0.0 1.0e+30 sun.gif\n"
        "1.0e+11 0.0 0.0 0.0 1.0e+30 mercury.gif\n");

    NB::Universe universe;
    input >> universe;

    sf::Vector2f initial_pos1 = universe[0].position();
    sf::Vector2f initial_pos2 = universe[1].position();

    for (int i = 0; i < 10; i++) {
        universe.step(1.0e+6);
    }

    sf::Vector2f after_normal_pos1 = universe[0].position();
    sf::Vector2f after_normal_pos2 = universe[1].position();

    BOOST_REQUIRE(after_normal_pos1.x > initial_pos1.x);
    BOOST_REQUIRE(after_normal_pos2.x < initial_pos2.x);
}*/

BOOST_AUTO_TEST_CASE(testInvertedGravity) {
    std::stringstream input("2 1.0e+11\n"
        "0.0 0.0 0.0 0.0 1.0e+30 sun.gif\n"
        "1.0e+11 0.0 0.0 0.0 1.0e+30 mercury.gif\n");

    NB::Universe universe;
    input >> universe;

    sf::Vector2f initial_pos1 = universe[0].position();
    sf::Vector2f initial_pos2 = universe[1].position();

    // Negative time step should reverse gravity
    for (int i = 0; i < 10; i++) {
        universe.step(-1.0e+6);
    }

    sf::Vector2f final_pos1 = universe[0].position();
    sf::Vector2f final_pos2 = universe[1].position();

    // With negative time step, first body should move left, second body should move right
    BOOST_REQUIRE(final_pos1.x < initial_pos1.x);
    BOOST_REQUIRE(final_pos2.x > initial_pos2.x);
}
/*
BOOST_AUTO_TEST_CASE(testNoAcceleration) {
    std::stringstream input("1 1.0e+11\n"
        "0.0 0.0 0.0 0.0 1.0e+30 earth.gif\n");

    NB::Universe universe;
    input >> universe;

    sf::Vector2f initial_position = universe[0].position();
    sf::Vector2f initial_velocity = universe[0].velocity();

    std::cerr << "TEST: Initial Position: (" << initial_position.x << ", " << initial_position.y << ")\n";
    std::cerr << "TEST: Initial Velocity: (" << initial_velocity.x << ", " << initial_velocity.y << ")\n";

    for (int i = 0; i < 10; i++) {
        universe.step(1.0e+6);
    }

    sf::Vector2f final_position = universe[0].position();
    sf::Vector2f final_velocity = universe[0].velocity();

    std::cerr << "TEST: Final Position: (" << final_position.x << ", " << final_position.y << ")\n";
    std::cerr << "TEST: Final Velocity: (" << final_velocity.x << ", " << final_velocity.y << ")\n";

    // If no force acts, position & velocity should remain unchanged
    BOOST_CHECK_SMALL(static_cast<double>(final_velocity.x), 1e-10);
    BOOST_CHECK_SMALL(static_cast<double>(final_velocity.y), 1e-10);
    BOOST_CHECK_CLOSE(static_cast<double>(final_position.x),
        static_cast<double>(initial_position.x), 0.0001);
    BOOST_CHECK_CLOSE(static_cast<double>(final_position.y),
        static_cast<double>(initial_position.y), 0.0001);
}

BOOST_AUTO_TEST_CASE(testInvertedGravity) {
    std::stringstream input("2 1.0e+11\n"
        "0.0 0.0 0.0 0.0 1.0e+30 sun.gif\n"
        "1.0e+11 0.0 0.0 0.0 1.0e+30 mercury.gif\n");

    NB::Universe universe;
    input >> universe;

    sf::Vector2f initial_pos1 = universe[0].position();
    sf::Vector2f initial_pos2 = universe[1].position();

    for (int i = 0; i < 10; i++) {
        universe.step(-1.0e+6);
    }

    sf::Vector2f final_pos1 = universe[0].position();
    sf::Vector2f final_pos2 = universe[1].position();

    BOOST_REQUIRE(final_pos1.x < initial_pos1.x);
    BOOST_REQUIRE(final_pos2.x > initial_pos2.x);
}*/

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
