#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>  // Needed for fabs()
#include "Universe.hpp"
#include "CelestialBody.hpp"

const double EPSILON = 1e-6;  // Small tolerance for floating-point comparisons

void testEmptyUniverse() {
    std::stringstream input("0 1.0e+11\n");
    NB::Universe universe;
    input >> universe;

    assert(universe.size() == 0);
    std::cout << "Empty Universe test passed!" << std::endl;
}

void testIOOperators() {
    std::stringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    NB::CelestialBody body;
    input >> body;
    
    std::stringstream output;
    output << body;

    assert(output.str() == "1.4960e+11 0 0 29800 5.974e+24 earth.gif\n");

    std::cout << "IO Operators for CelestialBody passed!" << std::endl;
}

void testCelestialBody() {
    std::stringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    NB::CelestialBody body;
    
    input >> body;

    assert(std::fabs(body.position().x - 1.4960e+11) < EPSILON);
    assert(std::fabs(body.position().y - 0.0) < EPSILON);
    assert(std::fabs(body.velocity().x - 0.0) < EPSILON);
    assert(std::fabs(body.velocity().y - 2.9800e+04) < EPSILON);
    assert(std::fabs(body.mass() - 5.9740e+24) < EPSILON);

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
    assert(std::fabs(universe[0].mass() - 5.9740e+24) < EPSILON);
    assert(std::fabs(universe[1].mass() - 6.4190e+23) < EPSILON);
    
    std::cout << "Universe tests passed!" << std::endl;
}

void testUniverseIndexing() {
    std::stringstream input("3 1.0e+11\n"
                            "1.0e+10 2.0e+10 0.0 0.0 5.0e+24 earth.gif\n"
                            "2.0e+10 3.0e+10 0.0 0.0 6.0e+24 mars.gif\n"
                            "3.0e+10 4.0e+10 0.0 0.0 7.0e+24 jupiter.gif\n");
    NB::Universe universe;
    input >> universe;

    assert(universe.size() == 3);
    assert(std::fabs(universe[0].mass() - 5.0e+24) < EPSILON);
    assert(std::fabs(universe[1].mass() - 6.0e+24) < EPSILON);
    assert(std::fabs(universe[2].mass() - 7.0e+24) < EPSILON);

    // Out-of-bounds test
    try {
        universe[3];  // Should throw an exception
        assert(false);  // If it doesn't throw, the test fails
    } catch (const std::out_of_range&) {
        std::cout << "Universe indexing test passed!" << std::endl;
    }
}

