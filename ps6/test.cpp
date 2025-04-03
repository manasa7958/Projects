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

/*BOOST_AUTO_TEST_CASE(FreqKGramTest) {
    RandWriter rw(sample_text, 1);
    BOOST_REQUIRE_EQUAL(rw.freq("a"), 7);
    BOOST_REQUIRE_EQUAL(rw.freq("g"), 9);
    BOOST_REQUIRE_EQUAL(rw.freq("c"), 1);
    BOOST_REQUIRE_EQUAL(rw.freq("z"), 0);
}*/
