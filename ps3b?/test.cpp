// Copyright 2025 Ponita Ty
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NBodyTest
#include <sstream>
#include <cmath>
#include <boost/test/unit_test.hpp>
#include "Universe.hpp"
#include "CelestialBody.hpp"

BOOST_AUTO_TEST_SUITE(CelestialObjectTests)

BOOST_AUTO_TEST_CASE(TestDefaultConstructor) {
    NB::CelestialBody obj;
    BOOST_CHECK_EQUAL(obj.mass(), 0.0f);
    BOOST_CHECK_EQUAL(obj.position().x, 0.0f);
    BOOST_CHECK_EQUAL(obj.position().y, 0.0f);
}

BOOST_AUTO_TEST_CASE(TestInputOperator) {
    std::stringstream ss("1.0 2.0 3.0 4.0 5.0 planet.gif");
    NB::CelestialBody obj;
    ss >> obj;
    BOOST_CHECK_CLOSE(obj.position().x, 1.0f, 0.001f);
    BOOST_CHECK_CLOSE(obj.position().y, 2.0f, 0.001f);
    BOOST_CHECK_CLOSE(obj.velocity().x, 3.0f, 0.001f);
    BOOST_CHECK_CLOSE(obj.velocity().y, 4.0f, 0.001f);
    BOOST_CHECK_CLOSE(obj.mass(), 5.0f, 0.001f);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(UniverseTests)

BOOST_AUTO_TEST_CASE(TestDefaultUniverse) {
    NB::Universe gal;
    BOOST_CHECK_EQUAL(gal.size(), 0);
    BOOST_CHECK_GE(gal.radius(), 0.0);
}

BOOST_AUTO_TEST_CASE(TestGalaxyEvolution) {
    std::stringstream ss;
    ss << "2 2.50e+11\n";
    ss << "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";
    ss << "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 sun.gif\n";

    NB::Universe gal;
    ss >> gal;

    const double dt = 25000.0;
    gal.step(dt);

    BOOST_CHECK_LT(gal[0].position().x, 1.4960e+11);
}

BOOST_AUTO_TEST_SUITE_END()
