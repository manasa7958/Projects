// Copyright Manasa Praveen 2025
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "EDistance.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EDistanceTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Min3DebugTest) {
    int a = 5, b = 1, c = 9;
    int result1 = EDistance::min3(a, b, c);
    std::cout << "min3(" << a << ", " << b << ", " << c << ") = " << result1 << std::endl;
    BOOST_CHECK_EQUAL(result1, 1);

    a = 7; b = 8; c = 3;
    int result2 = EDistance::min3(a, b, c);
    std::cout << "min3(" << a << ", " << b << ", " << c << ") = " << result2 << std::endl;
    BOOST_CHECK_EQUAL(result2, 3);

    a = 3; b = 8; c = 3;
    int result2 = EDistance::min3(a, b, c);
    std::cout << "min3(" << a << ", " << b << ", " << c << ") = " << result2 << std::endl;
    BOOST_CHECK_EQUAL(result2, 3);

    a = 3; b = 3; c = 3;
    int result2 = EDistance::min3(a, b, c);
    std::cout << "min3(" << a << ", " << b << ", " << c << ") = " << result2 << std::endl;
    BOOST_CHECK_EQUAL(result2, 3);

    a = 3; b = 3; c = 5;
    int result2 = EDistance::min3(a, b, c);
    std::cout << "min3(" << a << ", " << b << ", " << c << ") = " << result2 << std::endl;
    BOOST_CHECK_EQUAL(result2, 3);
}

BOOST_AUTO_TEST_CASE(PenaltyDebugTest) {
    char x = 'A', y = 'A';
    int result1 = EDistance::penalty(x, y);
    std::cout << "penalty('" << x << "', '" << y << "') = " << result1 << std::endl;
    BOOST_CHECK_EQUAL(result1, 0);

    x = 'C'; y = 'G';
    int result2 = EDistance::penalty(x, y);
    std::cout << "penalty('" << x << "', '" << y << "') = " << result2 << std::endl;
    BOOST_CHECK_EQUAL(result2, 1);
}


BOOST_AUTO_TEST_CASE(WrongDirectionTest) {
    // Tackles Reversed Direction as well
    EDistance ed("AGT", "AG");
    ed.optDistance();
    std::string out = ed.alignment();
    std::istringstream ss(out);
    std::string firstLine;
    std::getline(ss, firstLine);
    BOOST_CHECK(firstLine.find("A A") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(SwappedColsTest) {
    EDistance ed("A", "T");
    ed.optDistance();
    std::string out = ed.alignment();
    BOOST_CHECK(out.find("A T") != std::string::npos);
}
/*
BOOST_AUTO_TEST_CASE(test_tail_present) {
    EDistance ed("AC", "A");
    ed.optDistance();
    std::string out = ed.alignment();
    BOOST_CHECK(out.find("C -") != std::string::npos);
}
*/
