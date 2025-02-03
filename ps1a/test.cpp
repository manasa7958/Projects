// Copyright 2025 Manasa Praveen

#include <iostream>
#include <string>
#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

using PhotoMagic::FibLFSR;

BOOST_AUTO_TEST_CASE(testStepInstr) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
}

BOOST_AUTO_TEST_CASE(testGenerateInstr) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.generate(9), 51);
  BOOST_REQUIRE_THROW(l.generate(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testLFSROutput) {
    FibLFSR l("1011011000110110");
    stringstream ss;
    ss << l;
    BOOST_REQUIRE_EQUAL(ss.str(), "1011011000110110");
}

BOOST_AUTO_TEST_CASE(testInvalidInputs) {
  BOOST_REQUIRE_THROW(FibLFSR("101101"), std::invalid_argument);//too short
  BOOST_REQUIRE_THROW(FibLFSR("10110110001101100"), std::invalid_argument);//too long
  BOOST_REQUIRE_THROW(FibLFSR("A01101102 110$10"), std::invalid_argument);//other characters
}

BOOST_AUTO_TEST_CASE(testEdgeCases) {
    FibLFSR l("1100110011001100");
    BOOST_REQUIRE_EQUAL(l.generate(1), l.step());
    BOOST_REQUIRE_THROW(l.generate(0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testStep) {
    FibLFSR l("1011011000110110");
    std::vector<int> expect = {0, 0, 0, 1, 1, 0, 0, 1, 1, 1};
    for (int bit : expect) {
        BOOST_REQUIRE_EQUAL(l.step(), bit);
    }
}
BOOST_AUTO_TEST_CASE(testGenerateConsecutive) {
    FibLFSR l("1011011000110110");
    int first = l.generate(4);
    int second = l.generate(4);
    BOOST_REQUIRE_NE(first, second);
}

BOOST_AUTO_TEST_CASE(testNoThrow) {
    FibLFSR l("1011011000110110");
    BOOST_REQUIRE_NO_THROW(l.generate(1));
    BOOST_REQUIRE_NO_THROW(l.generate(16));
}

