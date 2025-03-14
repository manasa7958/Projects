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

using namespace NB;

BOOST_AUTO_TEST_CASE(test_celestial_body_initialization) {
    CelestialBody body(1.0e11, 2.0e11, 3.0e3, 4.0e3, 1.0e24, "earth.gif");
    BOOST_CHECK_CLOSE(body.mass(), 1.0e24, 1e-6);
    BOOST_CHECK_CLOSE(body.position().x, 1.0e11, 1e-6);
    BOOST_CHECK_CLOSE(body.position().y, 2.0e11, 1e-6);
    BOOST_CHECK_CLOSE(body.velocity().x, 3.0e3, 1e-6);
    BOOST_CHECK_CLOSE(body.velocity().y, 4.0e3, 1e-6);
}

BOOST_AUTO_TEST_CASE(test_universe_step) {
    Universe universe;
    universe.addBody(std::make_shared<CelestialBody>(0.0, 0.0, 0.0, 0.0, 1.0e24, "sun.gif"));
    universe.addBody(std::make_shared<CelestialBody>(1.0e11, 0.0, 0.0, 3.0e4, 5.0e23, "mars.gif"));
    
    double initial_x = universe[1].position().x;
    double initial_y = universe[1].position().y;
    
    universe.step(25000.0);
    
    BOOST_CHECK(universe[1].position().x != initial_x);
    BOOST_CHECK(universe[1].position().y != initial_y);
}

BOOST_AUTO_TEST_CASE(test_velocity_update) {
    Universe universe;
    auto planet = std::make_shared<CelestialBody>(1.0e11, 0.0, 0.0, 3.0e4, 5.0e23, "venus.gif");
    universe.addBody(planet);
    
    double initial_vx = planet->velocity().x;
    double initial_vy = planet->velocity().y;
    
    universe.step(25000.0);
    
    BOOST_CHECK(planet->velocity().x != initial_vx);
    BOOST_CHECK(planet->velocity().y != initial_vy);
}
