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

BOOST_AUTO_TEST_CASE(testStationaryBody) {
  std::stringstream input(
      "1 1.0e+11\n"
      "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 5.9740e+24 earth.gif\n");
  
  NB::Universe universe;
  input >> universe;
  
  double initial_x = universe[0].position().x;
  double initial_y = universe[0].position().y;
  universe.step(50000.0);
  
  BOOST_TEST(universe[0].position().x == initial_x);
  BOOST_TEST(universe[0].position().y == initial_y);
}

BOOST_AUTO_TEST_CASE(testSinglePlanetFixed) {
  std::stringstream input("1 1.0e+11\n"
                          "0.0 0.0 0.0 0.0 5.974e+24 earth.gif\n");
  NB::Universe universe;
  input >> universe;
  universe.step(1.0e6);
  BOOST_TEST(universe[0].position().x == 0.0);
  BOOST_TEST(universe[0].position().y == 0.0);
}

BOOST_AUTO_TEST_CASE(testTwoBodyGravity) {
  std::stringstream input("2 1.0e+11\n"
                          "-1.0e+11 0.0 0.0 0.0 5.974e+24 earth.gif\n"
                          "1.0e+11 0.0 0.0 0.0 5.974e+24 mars.gif\n");
  NB::Universe universe;
  input >> universe;
  universe.step(1.0e6);
  BOOST_TEST(universe[0].position().x > -1.0e+11);
  BOOST_TEST(universe[1].position().x < 1.0e+11);
}

BOOST_AUTO_TEST_CASE(testFormatConsistency) {
  std::stringstream input(
      "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
  NB::CelestialBody body;
  input >> body;
  std::stringstream output;
  output << body;
  NB::CelestialBody body2;
  output >> body2;

  BOOST_CHECK_CLOSE(body2.position().x, body.position().x, 0.001f);
  BOOST_CHECK_CLOSE(body2.position().y, body.position().y, 0.001f);
  BOOST_CHECK_CLOSE(body2.velocity().x, body.velocity().x, 0.001f);
  BOOST_CHECK_CLOSE(body2.velocity().y, body.velocity().y, 0.001f);
  BOOST_CHECK_CLOSE(body2.mass(), body.mass(), 0.001f);
}

BOOST_AUTO_TEST_CASE(testMultiStepSimulation) {
  std::stringstream input("5 2.50e+11\n"
         "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n"
         "2.2790e+11 0.0000e+00 0.0000e+00 2.4100e+04 6.4190e+23 mars.gif\n"
         "5.7900e+10 0.0000e+00 0.0000e+00 4.7900e+04 3.3020e+23 mercury.gif\n"
         "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 sun.gif\n"
         "1.0820e+11 0.0000e+00 0.0000e+00 3.5000e+04 4.8690e+24 venus.gif\n");

  NB::Universe universe;
  input >> universe;

  for (int i = 0; i < 100; ++i) {
    universe.step(1.0e6);
  }

  BOOST_REQUIRE_NO_THROW(universe[0]);
  BOOST_TEST(universe.size() == 5);
}
