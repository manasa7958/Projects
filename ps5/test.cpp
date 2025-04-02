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
