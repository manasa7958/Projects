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

/*BOOST_AUTO_TEST_CASE(BoxPushTest) {
    SB::Sokoban game(testLevel);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    auto playerPos = game.playerLoc();
    BOOST_CHECK_NE(playerPos, sf::Vector2u(2, 1));
}*/

BOOST_AUTO_TEST_CASE(VictoryConditionTest) {
    SB::Sokoban game("victory_test.lvl");

    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Left);
    game.movePlayer(SB::Direction::Up);

    BOOST_CHECK(game.isWon());
}

/*BOOST_AUTO_TEST_CASE(ResetFunctionalityTest) {
    SB::Sokoban game(testLevel);
    auto initialPos = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Down);
    BOOST_CHECK_NE(game.playerLoc(), initialPos);
    game.reset();
    BOOST_CHECK_EQUAL(game.playerLoc(), initialPos);
}*/
