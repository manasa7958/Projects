// Copyright Manasa Praveen 2025
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// #include "sfml_fix.hpp" - IRRELEVANT for Gradescope using because of problems in terminal
#include "Sokoban.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SokobanTests
#include <boost/algorithm/string.hpp>
#include <boost/test/unit_test.hpp>

inline std::ostream& operator<<(std::ostream& os, const sf::Vector2u& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

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

BOOST_AUTO_TEST_CASE(MissingSymbolTest) {
    std::ifstream input("swapoff.lvl");
    SB::Sokoban game;
    input >> game;
    std::ostringstream output;
    output << game;
    std::ifstream expectedInput("swapoff.lvl");
    std::ostringstream expectedStream;
    expectedStream << expectedInput.rdbuf();

    BOOST_CHECK_EQUAL(output.str(), expectedStream.str());
}
