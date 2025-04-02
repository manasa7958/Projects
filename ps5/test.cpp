// Copyright Manasa Praveen 2025
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "EDistance.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EDistanceTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(WrongMinTest) {
    BOOST_CHECK_EQUAL(EDistance::min3(5, 2, 8), 2);
    BOOST_CHECK_EQUAL(EDistance::min3(7, 7, 3), 3);
    BOOST_CHECK_EQUAL(EDistance::min3(1, 1, 1), 1);
}

BOOST_AUTO_TEST_CASE(test_alignment_from_file_lastygap8) {
    auto [s1, s2] = readSequencesFromFile("ps5/lastygap8.txt");
    EDistance ed(s1, s2);
    int dist = ed.optDistance();
    std::string alignment = ed.alignment();

    BOOST_CHECK(dist > 0); // crude sanity
    BOOST_CHECK(alignment.find("-") != std::string::npos); // has a gap
    BOOST_CHECK(alignment.find("a a") != std::string::npos || alignment.find("A A") != std::string::npos);
}
