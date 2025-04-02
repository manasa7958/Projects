// Copyright Manasa Praveen 2025
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "EDistance.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EDistanceTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Min3BasicTest) {
    BOOST_CHECK_EQUAL(EDistance::min3(5, 8, 9), 5);
}

BOOST_AUTO_TEST_CASE(TestPenaltyAllPairs) {
    BOOST_CHECK_EQUAL(EDistance::penalty('A', 'A'), 0);
    BOOST_CHECK_EQUAL(EDistance::penalty('C', 'C'), 0);
    BOOST_CHECK_EQUAL(EDistance::penalty('G', 'G'), 0);
    BOOST_CHECK_EQUAL(EDistance::penalty('T', 'T'), 0);

    BOOST_CHECK_EQUAL(EDistance::penalty('A', 'T'), 1);
    BOOST_CHECK_EQUAL(EDistance::penalty('C', 'G'), 1);
    BOOST_CHECK_EQUAL(EDistance::penalty('G', 'A'), 1);
    BOOST_CHECK_EQUAL(EDistance::penalty('T', 'C'), 1);
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
