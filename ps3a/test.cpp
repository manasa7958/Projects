#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath> 

#include "Universe.hpp"
#include "CelestialBody.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NBodyTests
#include <boost/test/unit_test.hpp>

const double EPSILON = 1e-6;

BOOST_AUTO_TEST_CASE(testEmptyUniverse) {
    std::stringstream input("0 1.0e+11\n");
    NB::Universe universe;
    input >> universe;

    BOOST_TEST(universe.size() == 0);
}

BOOST_AUTO_TEST_CASE(testFlippedValues) {
    std::stringstream input("1.1111e+11 2.2222e+11 3.3333e+04 4.4444e+04 5.5555e+24 flipped.gif");
    NB::CelestialBody body;
    input >> body;
    
    NB::CelestialBody expected;
    expected.pos = sf::Vector2f(1.1111e+11, 2.2222e+11);
    expected.vel = sf::Vector2f(3.3333e+04, 4.4444e+04);
    expected.m = 5.5555e+24;
    expected.imageFile = "flipped.gif";
    
    BOOST_REQUIRE_CLOSE(body.position().x, expected.position().x, 0.001f);
    BOOST_REQUIRE_CLOSE(body.position().y, expected.position().y, 0.001f);
    BOOST_REQUIRE_CLOSE(body.velocity().x, expected.velocity().x, 0.001f);
    BOOST_REQUIRE_CLOSE(body.velocity().y, expected.velocity().y, 0.001f);
    BOOST_REQUIRE_CLOSE(body.mass(), expected.mass(), 0.001f);
    BOOST_REQUIRE(body.imageFile == expected.imageFile);
}
