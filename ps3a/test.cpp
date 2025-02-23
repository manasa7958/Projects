#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>
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
    output << std::scientific << std::setprecision(4);
    output << body;

    std::string expected = "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";
    std::string actual = output.str();

    std::cout << "Expected: \"" << expected << "\"\n";
    std::cout << "Actual:   \"" << actual << "\"\n";

    assert(actual == expected);

    std::cout << "Formatting test passed!" << std::endl;
}

void testFormatting() {
    std::stringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    NB::CelestialBody body;
    input >> body;  // Read input

    std::stringstream output;
    output << std::scientific << std::setprecision(4);  // Ensure correct format
    output << body;  // Write to output

    std::string expected = "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";
    std::string actual = output.str();

    // Print actual vs expected for debugging
    std::cout << "Expected: \"" << expected << "\"\n";
    std::cout << "Actual:   \"" << actual << "\"\n";

    // Compare character by character
    if (actual != expected) {
        std::cout << "❌ Formatting Mismatch! Debugging...\n";
        for (size_t i = 0; i < std::min(expected.size(), actual.size()); i++) {
            if (expected[i] != actual[i]) {
                std::cout << "Mismatch at position " << i 
                          << ": expected '" << expected[i] 
                          << "', got '" << actual[i] << "'\n";
            }
        }
    }

    assert(actual == expected);  // Ensure exact match
    std::cout << "✅ Formatting test passed!" << std::endl;
}
int main() {
    testEmpty();
    testFormatting();
    //testFlipped();
    std::cout << "Tests passed!" << std::endl;
    return 0;
}
