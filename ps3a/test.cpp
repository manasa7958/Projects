#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath> 

#include "Universe.hpp"
#include "CelestialBody.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NBodyTests
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testEmptyUniverse) {
    std::stringstream input("0 1.0e+11\n");
    NB::Universe universe;
    input >> universe;

    BOOST_TEST(universe.size() == 0);
}

BOOST_AUTO_TEST_CASE(testFlippedValues) {
    std::stringstream input("1.1111e+11 2.2222e+11 3.3333e+04 4.4444e+04 5.5555e+24 flipped.gif");
    NB::CelestialBody body;
    input >> body;
    
    double expected_x_pos = 1.1111e+11;
    double expected_y_pos = 2.2222e+11;
    double expected_x_vel = 3.3333e+04;
    double expected_y_vel = 4.4444e+04;
    double expected_mass = 5.5555e+24;
    std::string expected_image = "flipped.gif";
    
    BOOST_REQUIRE_CLOSE(body.position().x, expected_x_pos, 0.001f);
    BOOST_REQUIRE_CLOSE(body.position().y, expected_y_pos, 0.001f);
    BOOST_REQUIRE_CLOSE(body.velocity().x, expected_x_vel, 0.001f);
    BOOST_REQUIRE_CLOSE(body.velocity().y, expected_y_vel, 0.001f);
    BOOST_REQUIRE_CLOSE(body.mass(), expected_mass, 0.001f);
}

BOOST_AUTO_TEST_CASE(testFormatting) {
    std::stringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    NB::CelestialBody body;
    input >> body;  // Read from input

    std::stringstream output;
    output << std::scientific << std::setprecision(4);  // Ensure formatting
    output << body;

    std::string expected = "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";
    std::string actual = output.str();

    // Debugging output: print expected vs. actual output
    std::cout << "Expected Output: \"" << expected << "\" (size: " << expected.size() << ")\n";
    std::cout << "Actual Output:   \"" << actual << "\" (size: " << actual.size() << ")\n";

    // Compare character by character if mismatch
    if (actual != expected) {
        std::cout << "Formatting Mismatch! Debugging...\n";
        for (size_t i = 0; i < std::min(expected.size(), actual.size()); i++) {
            if (expected[i] != actual[i]) {
                std::cout << "Mismatch at position " << i 
                          << ": expected '" << expected[i] 
                          << "', got '" << actual[i] << "'\n";
            }
        }
    }

    BOOST_TEST(actual == expected);
}
