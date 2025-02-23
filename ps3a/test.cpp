#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <cmath> 
#include "Universe.hpp"
#include "CelestialBody.hpp"

const double EPSILON = 1e-6;

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
    output << std::scientific << std::setprecision(4);
    output << body;

    std::string expected = "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";
    std::string actual = output.str();

    std::cout << "Expected: \"" << expected << "\"\n";
    std::cout << "Actual:   \"" << actual << "\"\n";

    assert(actual == expected);

    std::cout << "Formatting test passed!" << std::endl;
}

void testFlipped() {
    std::stringstream input("1.4960e+11 2.0000e+11 3.0000e+04 4.0000e+04 5.9740e+24 flipped.gif");
    NB::CelestialBody body;
    input >> body;

    // Ensure values are assigned correctly
    assert(std::fabs(body.position().x - 1.4960e+11) < EPSILON);
    assert(std::fabs(body.position().y - 2.0000e+11) < EPSILON);
    assert(std::fabs(body.velocity().x - 3.0000e+04) < EPSILON);
    assert(std::fabs(body.velocity().y - 4.0000e+04) < EPSILON);
    assert(std::fabs(body.mass() - 5.9740e+24) < EPSILON);
    assert(body.imageFile == "flipped.gif");

    std::stringstream output;
    output << body;

    std::cout << "Expected Output: \"1.4960e+11 2.0000e+11 3.0000e+04 4.0000e+04 5.9740e+24 flipped.gif\\n\"" << std::endl;
    std::cout << "Actual Output:   \"" << output.str() << "\"" << std::endl;

    assert(output.str() == "1.4960e+11 2.0000e+11 3.0000e+04 4.0000e+04 5.9740e+24 flipped.gif\n");

    std::cout << "Test passed!" << std::endl;
}

int main() {
    testEmpty();
    testFlipped();
    std::cout << "Tests passed!" << std::endl;
    return 0;
}
