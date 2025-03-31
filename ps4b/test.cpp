// Copyright Manasa Praveen 2025
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Sokoban.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SokobanTests
#include <boost/algorithm/string.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(BasicMovementTest) {
    SB::Sokoban game("level3.lvl");
    sf::Vector2u expPos = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    expPos = game.playerLoc();
    BOOST_CHECK_EQUAL(expPos.x, 4);
    BOOST_CHECK_EQUAL(expPos.y, 8);
}

BOOST_AUTO_TEST_CASE(CannotMoveTest) {
    SB::Sokoban game("level3.lvl");
    game.movePlayer(SB::Direction::Left);
    game.movePlayer(SB::Direction::Left);
    auto midPos = game.playerLoc();
    game.movePlayer(SB::Direction::Left);
    auto finalPos = game.playerLoc();

    BOOST_CHECK_EQUAL(midPos.x, finalPos.x);
    BOOST_CHECK_EQUAL(midPos.y, finalPos.y);
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

BOOST_AUTO_TEST_CASE(PlayerOffScreenTest) {
    SB::Sokoban game("pushleft.lvl");
    sf::Vector2u end = game.playerLoc();

    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    end = game.playerLoc();

    BOOST_CHECK_EQUAL(end.x, 4);
    BOOST_CHECK_EQUAL(end.y, 2);
}

BOOST_AUTO_TEST_CASE(CannotMoveIntoWallTest) {
    SB::Sokoban game({
        "#####",
        "#@  #",
        "#####"
    });
    bool moved = game.movePlayer(Direction::Left); // Wall
    BOOST_CHECK(!moved);
}

BOOST_AUTO_TEST_CASE(IgnoreBoxesNotInDirectionTest) {
    SB::Sokoban game({
        "#####",
        "#@ $#",
        "#####"
    });
    bool moved = game.movePlayer(Direction::Up); // No box above, should move
    BOOST_CHECK(moved);
}

BOOST_AUTO_TEST_CASE(BoxBoxCollisionTest) {
    SB::Sokoban game({
        "######",
        "#@$$ #",
        "######"
    });
    bool moved = game.movePlayer(Direction::Right); // Box into box
    BOOST_CHECK(!moved);
}

BOOST_AUTO_TEST_CASE(BoxWallCollisionTest) {
    SB::Sokoban game({
        "######",
        "#@$# #",
        "######"
    });
    bool moved = game.movePlayer(Direction::Right); // Box into wall
    BOOST_CHECK(!moved);
}

BOOST_AUTO_TEST_CASE(InvalidSymbolsTest) {
    BOOST_CHECK_THROW(SB::Sokoban({
        "#@x #", // 'x' is invalid
        "#####"
    }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TooManyBoxesVictoryTest) {
    SB::Sokoban game({
        "#######",
        "#@ $$ #",
        "#  .  #",
        "#######"
    });
    // Push both boxes onto one target
    game.movePlayer(Direction::Right);
    game.movePlayer(Direction::Right);
    game.movePlayer(Direction::Left);
    game.movePlayer(Direction::Left);
    game.movePlayer(Direction::Down);
    game.movePlayer(Direction::Right);
    game.movePlayer(Direction::Right);
    BOOST_CHECK(!game.hasWon());
}

BOOST_AUTO_TEST_CASE(TooManyTargetsVictoryTest) {
    SB::Sokoban game({
        "#######",
        "#@ $  #",
        "# ..  #",
        "#######"
    });
    // Push box onto one of the targets
    game.movePlayer(Direction::Right);
    game.movePlayer(Direction::Right);
    game.movePlayer(Direction::Down);
    game.movePlayer(Direction::Left);
    BOOST_CHECK(!game.hasWon());
}

BOOST_AUTO_TEST_CASE(PlayerOffScreenMoveTest) {
    SB::Sokoban game({
        "#@   #",
        "#####"
    });
    bool moved = game.movePlayer(Direction::Left); // Would go out of bounds
    BOOST_CHECK(!moved);
}

BOOST_AUTO_TEST_CASE(BoxOffScreenPushTest) {
    SB::Sokoban game({
        "#@ $ #",
        "#####"
    });
    game.movePlayer(Direction::Right); // Now @ is next to $
    bool moved = game.movePlayer(Direction::Right); // Push box off screen
    BOOST_CHECK(!moved);
}
