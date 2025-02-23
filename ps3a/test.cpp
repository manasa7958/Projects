#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath> 
#include "Universe.hpp"
#include "CelestialBody.hpp"

void testEmpty() {
    std::stringstream input("0 1.0e+11\n");
    NB::Universe universe;
    input >> universe;

    assert(universe.size() == 0);
    std::cout << "Empty Universe test passed!" << std::endl;
}
