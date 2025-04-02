// Copyright Manasa Praveen 2025
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "EDistance.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EDistanceTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Min3Test) {
    BOOST_CHECK_EQUAL(EDistance::min3(9, 5, 7), 5);
    BOOST_CHECK_EQUAL(EDistance::min3(10, 20, 3), 3);
    BOOST_CHECK_EQUAL(EDistance::min3(5, 5, 5), 5);
}

BOOST_AUTO_TEST_CASE(TestPenaltyFunction) {
    BOOST_CHECK_EQUAL(EDistance::penalty('A', 'A'), 0); // match
    BOOST_CHECK_EQUAL(EDistance::penalty('C', 'G'), 1); // mismatch
    BOOST_CHECK_EQUAL(EDistance::penalty('T', 'T'), 0); // match again
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
