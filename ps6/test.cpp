// Copyright Manasa Praveen 2025
#include <iostream>
#include <string>
#include <set>
#include "RandWriter.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RandWriterTest
#include <boost/test/unit_test.hpp>

const std::string sample_text = "gagggagaggcgagaaa";

BOOST_AUTO_TEST_CASE(KZeroTest) {
    RandWriter rw(sample_text, 2);
    BOOST_REQUIRE_EQUAL(rw.orderK(), 2);
}

BOOST_AUTO_TEST_CASE(ErrorCheckingTest) {
    RandWriter rw(sample_text, 2);
    BOOST_REQUIRE_THROW(rw.freq("a"), std::exception);
    BOOST_REQUIRE_THROW(rw.freq("aaa", 'g'), std::exception);
    BOOST_REQUIRE_THROW(rw.kRand("a"), std::exception);
    BOOST_REQUIRE_THROW(rw.generate("a", 10), std::exception);
}

BOOST_AUTO_TEST_CASE(GenerateLengthTest) {
    RandWriter rw(sample_text, 2);
    std::string result = rw.generate("ga", 10);
    BOOST_REQUIRE_EQUAL(result.size(), 10);
}

BOOST_AUTO_TEST_CASE(GenerateStartTest) {
    RandWriter rw(sample_text, 2);
    std::string result = rw.generate("ga", 10);
    BOOST_REQUIRE_EQUAL(result.substr(0, 2), "ga");
}
