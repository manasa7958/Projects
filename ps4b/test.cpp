// Copyright Manasa Praveen 2025
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Sokoban.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SokobanTests
#include <boost/algorithm/string.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(LevelLoadSanityCheck) {
    SB::Sokoban game("basic_move.lvl");
    BOOST_CHECK_EQUAL(game.width(), 5);
    BOOST_CHECK_EQUAL(game.height(), 5);
}

BOOST_AUTO_TEST_CASE(BasicMovementTest) {
    SB::Sokoban game("basic_move.lvl");
    sf::Vector2u start = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    sf::Vector2u end = game.playerLoc();

    BOOST_CHECK_EQUAL(end.x, start.x + 1);
    BOOST_CHECK_EQUAL(end.y, start.y);
}

BOOST_AUTO_TEST_CASE(WallCollisionTest) {
    SB::Sokoban game("wall_block.lvl");
    sf::Vector2u start = game.playerLoc();
    game.movePlayer(SB::Direction::Left);
    sf::Vector2u end = game.playerLoc();

    BOOST_CHECK_EQUAL(end.x, start.x);
    BOOST_CHECK_EQUAL(end.y, start.y);
}

BOOST_AUTO_TEST_CASE(BoxPushTest) {
    SB::Sokoban game("box_push.lvl");
    game.movePlayer(SB::Direction::Right);
    sf::Vector2u pos = game.playerLoc();

    BOOST_CHECK_EQUAL(pos.x, 2);
    BOOST_CHECK_EQUAL(pos.y, 1);
}

BOOST_AUTO_TEST_CASE(BoxBlockedTest) {
    SB::Sokoban game("box_blocked.lvl");
    sf::Vector2u start = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    sf::Vector2u end = game.playerLoc();

    BOOST_CHECK_EQUAL(end.x, start.x);
    BOOST_CHECK_EQUAL(end.y, start.y);
}

BOOST_AUTO_TEST_CASE(ResetTest) {
    SB::Sokoban game("basic_move.lvl");
    sf::Vector2u start = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    game.reset();
    sf::Vector2u afterReset = game.playerLoc();

    BOOST_CHECK_EQUAL(afterReset.x, start.x);
    BOOST_CHECK_EQUAL(afterReset.y, start.y);
}

BOOST_AUTO_TEST_CASE(VictoryConditionTest) {
    SB::Sokoban game("victory.lvl");
    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK(game.isWon());
}

BOOST_AUTO_TEST_CASE(InvalidSymbolTest) {
    {
        std::ofstream bad("test_levels/bad_symbol.lvl");
        bad << "3 3\n";
        bad << "###\n";
        bad << "#@x\n";
        bad << "###\n";
    }  // File is now closed

    BOOST_CHECK_THROW(SB::Sokoban("test_levels/bad_symbol.lvl"), std::runtime_error);
}
