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
    std::stringstream ss;
    ss << l;
    BOOST_CHECK_EQUAL(ss.str(), "1011011000110110");
}

BOOST_AUTO_TEST_CASE(testNoThrow) {
    BOOST_CHECK_NO_THROW(FibLFSR("1011011000110110"));//correct
    BOOST_CHECK_THROW(FibLFSR("1a1101100A110"), std::invalid_argument);//invalid characters
    BOOST_CHECK_THROW(FibLFSR("987"), std::invalid_argument);//too short
    BOOST_CHECK_THROW(FibLFSR("101101100011011001"), std::invalid_argument);//too long
}

BOOST_AUTO_TEST_CASE(testWrongInsert) {
    FibLFSR l("1011011000110110");  
    std::ostringstream ss1;
    ss1 << l;
    std::string initial = ss1.str();
    int newBit = l.step();
    
    std::ostringstream ss2;
    ss2 << l;
    std::string expected = initial.substr(1) + std::to_string(newBit);
    BOOST_REQUIRE_EQUAL(ss2.str(), expected);
}

