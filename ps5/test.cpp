#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EDistanceTest
#include <boost/test/unit_test.hpp>
#include "EDistance.hpp"

BOOST_AUTO_TEST_CASE(test_penalty_function) {
    BOOST_CHECK_EQUAL(EDistance::penalty('A', 'A'), 0);
    BOOST_CHECK_EQUAL(EDistance::penalty('A', 'T'), 1);
    BOOST_CHECK_EQUAL(EDistance::penalty('G', 'C'), 1);
    BOOST_CHECK_EQUAL(EDistance::penalty('T', 'T'), 0);
}

BOOST_AUTO_TEST_CASE(test_min3_function) {
    BOOST_CHECK_EQUAL(EDistance::min3(1, 2, 3), 1);
    BOOST_CHECK_EQUAL(EDistance::min3(4, 2, 5), 2);
    BOOST_CHECK_EQUAL(EDistance::min3(9, 9, 2), 2);
    BOOST_CHECK_EQUAL(EDistance::min3(3, 3, 3), 3);
}

BOOST_AUTO_TEST_CASE(test_opt_distance_simple) {
    EDistance ed("A", "A");
    BOOST_CHECK_EQUAL(ed.optDistance(), 0);

    EDistance ed2("A", "T");
    BOOST_CHECK_EQUAL(ed2.optDistance(), 1);

    EDistance ed3("A", "");
    BOOST_CHECK_EQUAL(ed3.optDistance(), 2);

    EDistance ed4("", "A");
    BOOST_CHECK_EQUAL(ed4.optDistance(), 2);
}

BOOST_AUTO_TEST_CASE(test_opt_distance_example10) {
    // From the PDF: "AACAGTTACC" vs "TAAGGTCA", expected distance = 7
    EDistance ed("AACAGTTACC", "TAAGGTCA");
    BOOST_CHECK_EQUAL(ed.optDistance(), 7);
}

BOOST_AUTO_TEST_CASE(test_alignment_format_basic) {
    EDistance ed("A", "T");
    ed.optDistance(); // ensure computation has run
    std::string output = ed.alignment();
    BOOST_CHECK(output.find("A T 1") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(test_alignment_format_multiline) {
    EDistance ed("AACAGTTACC", "TAAGGTCA");
    ed.optDistance();
    std::string align = ed.alignment();
    int line_count = std::count(align.begin(), align.end(), '\n');
    BOOST_CHECK(line_count >= 5); // Should have at least a few lines
    BOOST_CHECK(align.find("Edit distance") == std::string::npos); // just the alignment
}

BOOST_AUTO_TEST_CASE(test_no_throw_on_valid_input) {
    BOOST_REQUIRE_NO_THROW(EDistance("AGCT", "AGCT").optDistance());
    BOOST_REQUIRE_NO_THROW(EDistance("", "").optDistance());
}

BOOST_AUTO_TEST_CASE(test_throw_handling) {
    // There is no exception described in the interface, but we'll future-proof this
    // This test ensures any constructor or method does not throw on valid usage
    BOOST_REQUIRE_NO_THROW(EDistance("A", "A"));
    BOOST_REQUIRE_NO_THROW(EDistance("ACTG", "TGCA"));
}
