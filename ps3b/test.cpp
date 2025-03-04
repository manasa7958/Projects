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
        BOOST_CHECK_SMALL(static_cast<double>(universe[0].velocity().x), 1e-12);
        BOOST_CHECK_SMALL(static_cast<double>(universe[0].velocity().y), 1e-12);
    }

    sf::Vector2f final_position = universe[0].position();
    sf::Vector2f final_velocity = universe[0].velocity();

    std::cerr << "TEST: Final Position: (" << final_position.x << ", " << final_position.y << ")\n";
    std::cerr << "TEST: Final Velocity: (" << final_velocity.x << ", " << final_velocity.y << ")\n";

    BOOST_CHECK_MESSAGE(
        std::abs(final_velocity.x) < 1.0e-12f && std::abs(final_velocity.y) < 1.0e-12f,
        "Velocity changed when it shouldn't have. Final velocity: (" 
        << final_velocity.x << ", " << final_velocity.y << ")"
    );
    
    BOOST_CHECK_MESSAGE(
        std::abs(final_position.x - initial_position.x) < 1.0e-6f && 
        std::abs(final_position.y - initial_position.y) < 1.0e-6f,
        "Position changed when it shouldn't have. Displacement: (" 
        << (final_position.x - initial_position.x) << ", " 
        << (final_position.y - initial_position.y) << ")"
    );
}
BOOST_AUTO_TEST_CASE(testAntigrav) {
    std::stringstream input("2 1.0e+11\n"
        "0.0 0.0 0.0 0.0 1.0e+30 sun.gif\n"
        "0.0 1.0e+11 0.0 0.0 1.0e+30 mercury.gif\n");

    NB::Universe universe;
    input >> universe;

    sf::Vector2f initial_pos1 = universe[0].position();
    sf::Vector2f initial_pos2 = universe[1].position();

    std::cerr << "TEST: Initial Position 1: (" << initial_pos1.x << ", " << initial_pos1.y << ")\n";
    std::cerr << "TEST: Initial Position 2: (" << initial_pos2.x << ", " << initial_pos2.y << ")\n";

    for (int i = 0; i < 10; i++) {
        universe.step(1.0e+6);
    }

    sf::Vector2f final_pos1 = universe[0].position();
    sf::Vector2f final_pos2 = universe[1].position();
    sf::Vector2f final_vel1 = universe[0].velocity();
    sf::Vector2f final_vel2 = universe[1].velocity();

    std::cerr << "TEST: Final Position 1: (" << final_pos1.x << ", " << final_pos1.y << ")\n";
    std::cerr << "TEST: Final Position 2: (" << final_pos2.x << ", " << final_pos2.y << ")\n";

    BOOST_REQUIRE_MESSAGE(
        final_pos1.y < initial_pos1.y,
        "First body did not move down with normal gravity. Initial y: " 
        << initial_pos1.y << ", Final y: " << final_pos1.y
    );
    
    BOOST_REQUIRE_MESSAGE(
        final_pos2.y > initial_pos2.y,
        "Second body did not move up with normal gravity. Initial y: " 
        << initial_pos2.y << ", Final y: " << final_pos2.y
    );
    
    BOOST_REQUIRE_MESSAGE(
        final_vel1.y < 0,
        "First body should have negative y-velocity with normal gravity"
    );
    
    BOOST_REQUIRE_MESSAGE(
        final_vel2.y > 0,
        "Second body should have positive y-velocity with normal gravity"
    );
}
BOOST_AUTO_TEST_CASE(testInvertedGravity) {
    std::stringstream input("2 1.0e+11\n"
        "0.0 0.0 0.0 0.0 1.0e+30 sun.gif\n"
        "1.0e+11 0.0 0.0 0.0 1.0e+30 mercury.gif\n");

    NB::Universe universe;
    input >> universe;

    sf::Vector2f initial_pos1 = universe[0].position();
    sf::Vector2f initial_pos2 = universe[1].position();

    std::cerr << "TEST: Initial Position 1: (" << initial_pos1.x << ", " << initial_pos1.y << ")\n";
    std::cerr << "TEST: Initial Position 2: (" << initial_pos2.x << ", " << initial_pos2.y << ")\n";

    for (int i = 0; i < 10; i++) {
        universe.step(-1.0e+6);
    }

    sf::Vector2f final_pos1 = universe[0].position();
    sf::Vector2f final_pos2 = universe[1].position();
    sf::Vector2f final_vel1 = universe[0].velocity();
    sf::Vector2f final_vel2 = universe[1].velocity();

    BOOST_REQUIRE_MESSAGE(
        final_pos1.x < initial_pos1.x,
        "First body did not move left with inverted gravity."
    );
    
    BOOST_REQUIRE_MESSAGE(
        final_pos2.x > initial_pos2.x,
        "Second body did not move right with inverted gravity."
    );
    
    BOOST_REQUIRE_MESSAGE(
        final_vel1.x > 0,
        "First body's velocity should be positive with inverted gravity"
    );
    
    BOOST_REQUIRE_MESSAGE(
        final_vel2.x < 0,
        "Second body's velocity should be negative with inverted gravity"
    );
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
