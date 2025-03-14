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

BOOST_AUTO_TEST_CASE(test_celestial_body_initialization) {
    CelestialBody body(1.0e24, 1.0e11, 2.0e11, 3.0e3, 4.0e3, "earth.gif");
    BOOST_CHECK_CLOSE(body.getMass(), 1.0e24, 1e-6);
    BOOST_CHECK_CLOSE(body.getPosition().x, 1.0e11, 1e-6);
    BOOST_CHECK_CLOSE(body.getPosition().y, 2.0e11, 1e-6);
    BOOST_CHECK_CLOSE(body.getVelocity().x, 3.0e3, 1e-6);
    BOOST_CHECK_CLOSE(body.getVelocity().y, 4.0e3, 1e-6);
    BOOST_CHECK_EQUAL(body.getImage(), "earth.gif");
}

BOOST_AUTO_TEST_CASE(test_universe_step) {
    Universe universe;
    universe.addBody(std::make_shared<CelestialBody>(1.0e24, 0.0, 0.0, 0.0, 0.0, "sun.gif"));
    universe.addBody(std::make_shared<CelestialBody>(5.0e23, 1.0e11, 0.0, 0.0, 3.0e4, "mars.gif"));
    
    double initial_x = universe.getBodies()[1]->getPosition().x;
    double initial_y = universe.getBodies()[1]->getPosition().y;
    
    universe.step(25000.0);
    
    BOOST_CHECK(universe.getBodies()[1]->getPosition().x != initial_x);
    BOOST_CHECK(universe.getBodies()[1]->getPosition().y != initial_y);
}

BOOST_AUTO_TEST_CASE(test_velocity_update) {
    Universe universe;
    auto planet = std::make_shared<CelestialBody>(5.0e23, 1.0e11, 0.0, 0.0, 3.0e4, "venus.gif");
    universe.addBody(planet);
    
    double initial_vx = planet->getVelocity().x;
    double initial_vy = planet->getVelocity().y;
    
    universe.step(25000.0);
    
    BOOST_CHECK(planet->getVelocity().x != initial_vx);
    BOOST_CHECK(planet->getVelocity().y != initial_vy);
}
