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

/*BOOST_AUTO_TEST_CASE(testFormatting) {
    std::stringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    NB::CelestialBody body;
    input >> body;

    std::stringstream output;
    output << std::scientific << std::setprecision(4);
    output << body;

    std::string expected = "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";
    std::string actual = output.str();

    BOOST_TEST(actual == expected);
}*/

BOOST_AUTO_TEST_CASE(testFlippedValues) {
    std::stringstream input("1.1111e+11 2.2222e+11 3.3333e+04 4.4444e+04 5.5555e+24 flipped.gif");
    NB::CelestialBody body;
    input >> body;

    BOOST_TEST(std::fabs(body.position().x - 1.1111e+11) < EPSILON);
    BOOST_TEST(std::fabs(body.position().y - 2.2222e+11) < EPSILON);
    BOOST_TEST(std::fabs(body.velocity().x - 3.3333e+04) < EPSILON);
    BOOST_TEST(std::fabs(body.velocity().y - 4.4444e+04) < EPSILON);
    BOOST_TEST(std::fabs(body.mass() - 5.5555e+24) < EPSILON);
    BOOST_TEST(body.imageFile == "flipped.gif");
}



