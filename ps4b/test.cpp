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

BOOST_AUTO_TEST_CASE(BoxBoxCollisionTest) {
    SB::Sokoban game("level2.lvl");
    sf::Vector2u pos = game.playerLoc();
    game.movePlayer(SB::Direction::Up);
    pos = game.playerLoc();
    BOOST_CHECK_EQUAL(pos.x, 8);
    BOOST_CHECK_EQUAL(pos.y, 5);
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

BOOST_AUTO_TEST_CASE(LotsOfBoxesTest) {
    SB::Sokoban game("level5.lvl");
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Left);
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK(game.isWon());
}

BOOST_AUTO_TEST_CASE(LotsOfTargetsTest) {
    SB::Sokoban game("level6.lvl");
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Left);

    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Left);
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK(game.isWon());
}

/*BOOST_AUTO_TEST_CASE(MissingSymbolTest) {
    SB::Sokoban game("autowin2.lvl");
    sf::Vector2u initialPos = game.playerLoc();
    BOOST_CHECK_EQUAL(initialPos.x, 2);
    BOOST_CHECK_EQUAL(initialPos.y, 2);
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Left);
    game.movePlayer(SB::Direction::Up);
    sf::Vector2u finalPos = game.playerLoc();
    BOOST_CHECK(finalPos.x >= 0 && finalPos.x < 5);
    BOOST_CHECK(finalPos.y >= 0 && finalPos.y < 5);
}*/
