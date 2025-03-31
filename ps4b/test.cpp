// Copyright Manasa Praveen 2025
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Sokoban.hpp"

namespace std {
std::ostream& operator<<(std::ostream& os, const sf::Vector2u& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}
std::ostream& operator<<(std::ostream& os, const std::vector<sf::Vector2u>& vecs) {
    os << "[";
    for (size_t i = 0; i < vecs.size(); ++i) {
        os << vecs[i];
        if (i < vecs.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}
} // namespace std
void printBoard(const SB::Sokoban& game) {
    std::cout << "=== Current Board ===\n";
    std::ostringstream out;
    out << game;
    std::cout << out.str() << std::endl;
}

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SokobanTests
#include <boost/algorithm/string.hpp>
#include <boost/test/unit_test.hpp>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ostringstream;

const std::string testLevel = "level3.lvl";

BOOST_AUTO_TEST_CASE(BasicMovementTest) {
    SB::Sokoban game(testLevel);
    auto originalPos = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    auto newPos = game.playerLoc();
    BOOST_CHECK_NE(originalPos, newPos);
}

BOOST_AUTO_TEST_CASE(CannotMoveTest) {
    SB::Sokoban game(testLevel);
    game.movePlayer(SB::Direction::Left);
    game.movePlayer(SB::Direction::Left);
    auto midPos = game.playerLoc();
    game.movePlayer(SB::Direction::Left);
    auto finalPos = game.playerLoc();

    BOOST_CHECK_EQUAL(midPos, finalPos);
}

BOOST_AUTO_TEST_CASE(IgnoreBoxesTest) {
    SB::Sokoban game("victory_test.lvl");

    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Left);
    game.movePlayer(SB::Direction::Up);

    BOOST_CHECK(game.isWon());
}

BOOST_AUTO_TEST_CASE(MultipleBoxVictoryTest) {
    SB::Sokoban game("autowin2.lvl");
    BOOST_CHECK(game.isWon());
}

BOOST_AUTO_TEST_CASE(MultipleTargetVictoryTest) {
    SB::Sokoban game("autowin.lvl");
    printBoard(game);
    if (!game.isWon()) {
        std::cout << "Game not won, inspecting board...\n";
    }
    BOOST_CHECK(game.isWon());
}

BOOST_AUTO_TEST_CASE(PlayerOffScreenTest) {
    SB::Sokoban game("edge_move.lvl");
    auto start = game.playerLoc();
    game.movePlayer(SB::Direction::Left);
    BOOST_CHECK_EQUAL(game.playerLoc(), start);
    game.movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(game.playerLoc(), start);
}

BOOST_AUTO_TEST_CASE(BoxOffScreenTest) {
    SB::Sokoban game("edge_push.lvl");
    auto start = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(game.playerLoc(), start);
}
