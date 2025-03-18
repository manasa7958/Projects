// Copyright 2025 Ponita Ty
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NBodyTest
#include <sstream>
#include <cmath>
#include <boost/test/unit_test.hpp>
#include "Universe.hpp"
#include "CelestialBody.hpp"

BOOST_AUTO_TEST_SUITE(SpaceObjectTests)

BOOST_AUTO_TEST_CASE(TestCelestialConstructor) {
    NB::CelestialBody obj;
    BOOST_CHECK_EQUAL(obj.mass(), 0.0f);
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

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GalacticSimulationTests)

BOOST_AUTO_TEST_CASE(TestUniverseConstructor) {
    NB::Universe cosmos;
    BOOST_CHECK_EQUAL(cosmos.size(), 0);
    BOOST_CHECK_GE(cosmos.radius(), 0.0);
}

BOOST_AUTO_TEST_CASE(TestUniverseEvolution) {
    std::stringstream ss;
    ss << "2 3.00e+11\n";
    ss << "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";
    ss << "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 sun.gif\n";

    NB::Universe cosmos;
    ss >> cosmos;

    const double dt = 25000.0;
    cosmos.step(dt);

    BOOST_CHECK_LT(cosmos[0].position().x, 1.4960e+11);
}

BOOST_AUTO_TEST_SUITE_END()
