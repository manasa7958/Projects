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

BOOST_AUTO_TEST_CASE(TailMustBePresentTest) {
    {
        EDistance ed("AC", "A");
        ed.optDistance();
        std::string out = ed.alignment();
        std::cout << "[AC vs A] Alignment output:\n" << out << std::endl;

        BOOST_CHECK_MESSAGE(out.find("C -") != std::string::npos,
            "[AC vs A] Tail line 'C -' was missing. Broken implementation detected.");
    }

    {
        EDistance ed("A", "AC");
        ed.optDistance();
        std::string out = ed.alignment();
        std::cout << "[A vs AC] Alignment output:\n" << out << std::endl;

        BOOST_CHECK_MESSAGE(out.find("- C") != std::string::npos,
            "[A vs AC] Tail line '- C' was missing. Broken implementation detected.");
    }
}

BOOST_AUTO_TEST_CASE(TailMustBeTwoLinesTest) {
    EDistance ed("AC", "A");
    ed.optDistance();
    std::string out = ed.alignment();

    std::istringstream ss(out);
    int count = 0;
    std::string line;
    while (std::getline(ss, line)) {
        if (!line.empty()) ++count;
    }

    BOOST_CHECK_MESSAGE(count >= 2, "Alignment is missing lines — tail may be cut off.");
}
