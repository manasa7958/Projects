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
      "1.1111e+11 2.2222e+11 3.3333e+04 4.4444e+04 5.5555e+24 flipped.gif");
  NB::CelestialBody body;
  input >> body;

  BOOST_REQUIRE_CLOSE(body.position().x, 1.1111e+11, 0.001f);
  BOOST_REQUIRE_CLOSE(body.position().y, 2.2222e+11, 0.001f);
  BOOST_REQUIRE_CLOSE(body.velocity().x, 3.3333e+04, 0.001f);
  BOOST_REQUIRE_CLOSE(body.velocity().y, 4.4444e+04, 0.001f);
  BOOST_REQUIRE_CLOSE(body.mass(), 5.5555e+24, 0.001f);
}

BOOST_AUTO_TEST_CASE(testNoAcceleration) {
  std::stringstream input("1 1.0e+11\n0.0 0.0 0.0 0.0 1.0e+30 stationary.gif\n");
  NB::Universe universe;
  input >> universe;
  universe.step(1.0e+6);
  BOOST_TEST(universe[0].position().x == 0.0);
  BOOST_TEST(universe[0].position().y == 0.0);
}
