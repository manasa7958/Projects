// Copyright Manasa Praveen 2025
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "EDistance.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EDistanceTest
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(Min3Test) {
    std::vector<int> vals = {1, 2, 3};

    for (int a : vals) {
        for (int b : vals) {
            for (int c : vals) {
                int expected = std::min({a, b, c});
                int actual = EDistance::min3(a, b, c);
                BOOST_CHECK_MESSAGE(
                    actual == expected,
                    "min3(" << a << ", " << b << ", " << c << ") = "
                    << actual << ", expected " << expected);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(WringCostTest) {
    {
        EDistance ed("A", "A");
        int dist = ed.optDistance();
        BOOST_CHECK_MESSAGE(dist == 0, "Match: Expected 0, got " << dist);
    }

    {
        EDistance ed("A", "T");
        int dist = ed.optDistance();
        BOOST_CHECK_MESSAGE(dist == 1, "Mismatch: Expected 1, got " << dist);
    }

    {
        EDistance ed("A", "");
        int dist = ed.optDistance();
        BOOST_CHECK_MESSAGE(dist == 2, "Gap: Expected 2, got " << dist);
    }
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

BOOST_AUTO_TEST_CASE(TestAlignmentTailDebug) {
    EDistance ed("AC", "A");
    ed.optDistance();
    std::string out = ed.alignment();

    std::cout << "Alignment output:\n" << out << std::endl;

    bool tail_found = out.find("C -") != std::string::npos;
    BOOST_CHECK_MESSAGE(tail_found, "Expected to find 'C -' at the end, but did not.");
}
