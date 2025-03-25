// Copyright Manasa Praveen 2025
#define BOOST_TEST_MODULE SokobanTests
#include <boost/test/included/unit_test.hpp>
#include "Sokoban.hpp"

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

    game.movePlayer(Direction::Up); // Assuming wall is above
    auto newPos = game.playerLoc();

    BOOST_CHECK_EQUAL(originalPos, newPos); // Should not move into wall
}

BOOST_AUTO_TEST_CASE(BoxPushTest) {
    Sokoban game(testLevel);

    // Move player to position to push box
    game.movePlayer(Direction::Right);  // adjust if needed
    game.movePlayer(Direction::Right);

    auto playerPos = game.playerLoc();
    BOOST_CHECK_NE(playerPos, sf::Vector2u(2, 1)); // Replace with correct expected box-push position
}

BOOST_AUTO_TEST_CASE(VictoryConditionTest) {
    Sokoban game(testLevel);

    // Move boxes into storage locations
    // This needs to match your level setup
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
