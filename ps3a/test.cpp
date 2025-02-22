#include <iostream>
#include <sstream>
#include <cassert>
#include "Universe.hpp"
#include "CelestialBody.hpp"

using namespace NB;
int main() {
    std::cout << "Running tests..." << std::endl;
    return 0;
}

void testCelestialBody() {
    std::stringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    CelestialBody body;
    
    input >> body;
    
    assert(body.getPosition().x == 1.4960e+11);
    assert(body.getPosition().y == 0.0);
    assert(body.getVelocity().x == 0.0);
    assert(body.getVelocity().y == 2.9800e+04);
    assert(body.getMass() == 5.9740e+24);

    std::stringstream output;
    output << body;
    std::string expected = "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";
    assert(output.str() == expected);

    std::cout << "CelestialBody tests passed!" << std::endl;
}

void testUniverse() {
    std::stringstream input("5 2.50e+11\n"
                            "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n"
                            "2.2790e+11 0.0000e+00 0.0000e+00 2.4100e+04 6.4190e+23 mars.gif\n"
                            "5.7900e+10 0.0000e+00 0.0000e+00 4.7900e+04 3.3020e+23 mercury.gif\n"
                            "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 sun.gif\n"
                            "1.0820e+11 0.0000e+00 0.0000e+00 3.5000e+04 4.8690e+24 venus.gif\n");

    Universe universe;
    input >> universe;

    assert(universe.size() == 5);
    assert(universe.radius() == 2.50e+11);
    assert(universe[0].getMass() == 5.9740e+24);
    assert(universe[1].getMass() == 6.4190e+23);
    
    std::stringstream output;
    output << universe;
    
    assert(output.str().find("1.4960e+11") != std::string::npos); // Check Earth data in output
    
    std::cout << "Universe tests passed!" << std::endl;
}

int main() {
    testCelestialBody();
    testUniverse();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

