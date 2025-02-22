#include <iostream>
#include <cassert>
#include <cmath>  // Needed for fabs()
#include "Universe.hpp"
#include "CelestialBody.hpp"

const double EPSILON = 1e-6;  // Small tolerance for floating-point comparisons

void testCelestialBody() {
    std::stringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    NB::CelestialBody body;
    
    input >> body;

    assert(std::fabs(body.getPosition().x - 1.4960e+11) < EPSILON);  // ✅ FIXED
    assert(std::fabs(body.getPosition().y - 0.0) < EPSILON);
    assert(std::fabs(body.getVelocity().x - 0.0) < EPSILON);
    assert(std::fabs(body.getVelocity().y - 2.9800e+04) < EPSILON);
    assert(std::fabs(body.getMass() - 5.9740e+24) < EPSILON);  // ✅ FIXED

    std::cout << "CelestialBody tests passed!" << std::endl;
}

void testUniverse() {
    std::stringstream input("5 2.50e+11\n"
                            "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n"
                            "2.2790e+11 0.0000e+00 0.0000e+00 2.4100e+04 6.4190e+23 mars.gif\n"
                            "5.7900e+10 0.0000e+00 0.0000e+00 4.7900e+04 3.3020e+23 mercury.gif\n"
                            "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 sun.gif\n"
                            "1.0820e+11 0.0000e+00 0.0000e+00 3.5000e+04 4.8690e+24 venus.gif\n");

    NB::Universe universe;
    input >> universe;

    assert(universe.size() == 5);
    assert(std::fabs(universe[0].getMass() - 5.9740e+24) < EPSILON);  // ✅ FIXED
    assert(std::fabs(universe[1].getMass() - 6.4190e+23) < EPSILON);  // ✅ FIXED
    
    std::cout << "Universe tests passed!" << std::endl;
}
