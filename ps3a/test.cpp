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
void testFormatting() {
    std::stringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    NB::CelestialBody body;
    input >> body;
    std::stringstream output;
    output << body;
    
    assert(output.str() == "1.4960e+11 0 0 29800 5.974e+24 earth.gif\n"); // Check if output matches correct format
    std::cout << "Formatting for CelestialBody passed!" << std::endl;
}
int main() {
    testEmpty();
    testFormatting();
    std::cout << "Tests passed!" << std::endl;
    return 0;
}
