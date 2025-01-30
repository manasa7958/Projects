// Copyright 2022
// By Dr. Rykalova
// Editted by Dr. Daly
// test.cpp for PS1a
// updated 1/8/2024

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
}


BOOST_AUTO_TEST_CASE(testInvalidLength) {
  BOOST_CHECK_THROW(FibLFSR("101101"), std::invalid_argument);
  BOOST_CHECK_THROW(FibLFSR("10110110001101100"), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(testInvalidCharacters) {
  BOOST_CHECK_THROW(FibLFSR("A011011000110110"), std::invalid_argument);
  BOOST_CHECK_THROW(FibLFSR("A!@#$"), std::invalid_argument);
}
