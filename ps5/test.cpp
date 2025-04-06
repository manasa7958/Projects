// Copyright Manasa Praveen and Ponita Ty 2025
#define BOOST_TEST_MODULE EDistanceTest
#include <boost/test/included/unit_test.hpp>
#include "EDistance.hpp"

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

BOOST_AUTO_TEST_CASE(AlignmentExactLinesTest) {
    {
        EDistance ed("AC", "A");
        ed.optDistance();
        std::string out = ed.alignment();
        std::cout << "[AC vs A] Alignment output:\n" << out << std::endl;

        std::string expected =
            "A A 0\n"
            "C - 2";

        BOOST_CHECK_MESSAGE(out.find(expected) != std::string::npos,
            "[AC vs A] Expected exact alignment:\n" << expected << "\nBut got:\n" << out);
    }

    {
        EDistance ed("A", "AC");
        ed.optDistance();
        std::string out = ed.alignment();
        std::cout << "[A vs AC] Alignment output:\n" << out << std::endl;

        std::string expected =
            "A A 0\n"
            "- C 2";

        BOOST_CHECK_MESSAGE(out.find(expected) != std::string::npos,
            "[A vs AC] Expected exact alignment:\n" << expected << "\nBut got:\n" << out);
    }
}

BOOST_AUTO_TEST_CASE(NoThrowTest) {
    BOOST_REQUIRE_NO_THROW({
        EDistance ed("AC", "A");
        ed.optDistance();
        ed.alignment();
    });
}

BOOST_AUTO_TEST_CASE(AlignmentCompletenessTest) {
    EDistance ed("AACAGTTACC", "TAAGGTCA");
    ed.optDistance();
    std::string out = ed.alignment();
    std::istringstream ss(out);
    std::string line;
    std::string s1_reconstructed, s2_reconstructed;
    int line_count = 0;

    while (std::getline(ss, line)) {
        line_count++;
        if (line.size() >= 3) {
            char c1 = line[0];
            char c2 = line[2];
            if (c1 != '-') s1_reconstructed += c1;
            if (c2 != '-') s2_reconstructed += c2;
        }
    }

    BOOST_CHECK_MESSAGE(s1_reconstructed == "AACAGTTACC",
    "Reconstructed s1 should match original, got: " << s1_reconstructed);
    BOOST_CHECK_MESSAGE(s2_reconstructed == "TAAGGTCA",
    "Reconstructed s2 should match original, got: " << s2_reconstructed);
    BOOST_CHECK_MESSAGE(line_count == std::max(10, 8), "Alignment should have " << std::max(10, 8)
    << " lines, got: " << line_count);
}

BOOST_AUTO_TEST_CASE(CutEndsTest) {
    {
        EDistance ed("ACTG", "TG");
        ed.optDistance();
        std::string out = ed.alignment();
        std::istringstream ss(out);
        int line_count = 0;
        std::string line;
        while (std::getline(ss, line)) {
            line_count++;
        }
        BOOST_CHECK_MESSAGE(line_count == 4,
                            "Expected 4 lines in alignment output, but got " << line_count);

        BOOST_CHECK_MESSAGE(out.find("A -") != std::string::npos ||
                            out.find("A T") != std::string::npos,
                            "Alignment missing head end characters of the first string");
    }
    {
        EDistance ed("AGT", "T");
        ed.optDistance();
        std::string out = ed.alignment();
        BOOST_CHECK_MESSAGE(
                            out.find("A -") != std::string::npos,
                            "The first 'A' character should be present in the alignment");

        BOOST_CHECK_MESSAGE(
                            out.find("G -") != std::string::npos,
                            "The middle 'G' character should be present in the alignment");

        BOOST_CHECK_MESSAGE(
                            out.find("T T") != std::string::npos,
                            "The last 'T' character should be present in the alignment");
    }
}
