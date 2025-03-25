// Copyright Manasa Praveen 2025
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Sokoban.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SokobanTests
#include <boost/algorithm/string.hpp>
#include <boost/test/unit_test.hpp>

using namespace SB;

const std::string testLevel = "level3.lvl";

BOOST_AUTO_TEST_CASE(BasicMovementTest) {
    Sokoban game(testLevel);
    auto originalPos = game.playerLoc();

    game.movePlayer(Direction::Right);
    auto newPos = game.playerLoc();

    BOOST_CHECK_NE(originalPos, newPos);
}

BOOST_AUTO_TEST_CASE(WallCollisionTest) {
    Sokoban game(testLevel);
    auto originalPos = game.playerLoc();

    game.movePlayer(Direction::Up);
    auto newPos = game.playerLoc();

    BOOST_CHECK_EQUAL(originalPos, newPos);
}

BOOST_AUTO_TEST_CASE(BoxPushTest) {
    Sokoban game(testLevel);

    game.movePlayer(Direction::Right);
    game.movePlayer(Direction::Right);

    auto playerPos = game.playerLoc();
    BOOST_CHECK_NE(playerPos, sf::Vector2u(2, 1));
}

BOOST_AUTO_TEST_CASE(VictoryConditionTest) {
    Sokoban game(testLevel);

    game.movePlayer(Direction::Right);
    game.movePlayer(Direction::Right);
    game.movePlayer(Direction::Down);
    game.movePlayer(Direction::Left);
    game.movePlayer(Direction::Up);

    BOOST_CHECK(game.isWon());
}

BOOST_AUTO_TEST_CASE(ResetFunctionalityTest) {
    Sokoban game(testLevel);
    auto initialPos = game.playerLoc();

    game.movePlayer(Direction::Right);
    game.movePlayer(Direction::Down);
    BOOST_CHECK_NE(game.playerLoc(), initialPos);

    game.reset();
    BOOST_CHECK_EQUAL(game.playerLoc(), initialPos);
}
