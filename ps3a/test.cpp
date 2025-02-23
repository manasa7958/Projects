#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath> 
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
