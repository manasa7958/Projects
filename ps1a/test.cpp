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
  BOOST_REQUIRE_THROW(l.generate(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testLFSROutput) {
    FibLFSR l("1011011000110110");
    stringstream ss;
    ss << l;
    BOOST_REQUIRE_EQUAL(ss.str(), "1011011000110110");
}

BOOST_AUTO_TEST_CASE(testInvalidInputs) {
  BOOST_REQUIRE_THROW(FibLFSR 1("101101"), std::invalid_argument);//too short
  BOOST_REQUIRE_THROW(FibLFSR 1("10110110001101100"), std::invalid_argument);//too long
  BOOST_REQUIRE_THROW(FibLFSR 1("A011011000110110"), std::invalid_argument);//other characters
  BOOST_REQUIRE_THROW(FibLFSR 1("A!@#$"), std::invalid_argument);//too short and invalid characters
  BOOST_REQUIRE_THROW(FibLFSR 1("1011021100001101"), std::invalid_argument);//other characters
  BOOST_REQUIRE_THROW(FibLFSR 1("11 00110011001100"), std::invalid_argument);//other characters
}
BOOST_AUTO_TEST_CASE(testGenerateEdgeCases) {
    FibLFSR l("1100110011001100");
    BOOST_REQUIRE_EQUAL(l.generate(1), l.step());
    BOOST_REQUIRE_THROW(l.generate(0), std::invalid_argument);
}
