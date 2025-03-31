// Copyright Manasa Praveen 2025
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
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
}  // namespace std
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

BOOST_AUTO_TEST_CASE(BasicMovementTest) {
    SB::Sokoban game("level3.lvl");
    auto originalPos = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    auto newPos = game.playerLoc();
    BOOST_CHECK_NE(originalPos, newPos);
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

BOOST_AUTO_TEST_CASE(ResetTest) {
    SB::Sokoban game("pushright.lvl");
    sf::Vector2u start = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    sf::Vector2u afterPush = game.playerLoc();
    BOOST_CHECK_EQUAL(afterPush.x, start.x + 1);
    BOOST_CHECK_EQUAL(afterPush.y, start.y);
    game.reset();
    sf::Vector2u resetPos = game.playerLoc();
    BOOST_CHECK_EQUAL(resetPos.x, start.x);
    BOOST_CHECK_EQUAL(resetPos.y, start.y);
}

BOOST_AUTO_TEST_CASE(FileParsingTest) {
    SB::Sokoban game("level3.lvl");
    BOOST_CHECK_EQUAL(game.height(), 12);
    BOOST_CHECK_EQUAL(game.width(), 10);
    BOOST_CHECK_EQUAL(game.playerLoc().x, 3);
    BOOST_CHECK_EQUAL(game.playerLoc().y, 8);
}

BOOST_AUTO_TEST_CASE(PlayerMovesAlongBordersTest) {
    SB::Sokoban game("level3.lvl");
    
    auto startPos = game.playerLoc();
    BOOST_CHECK_EQUAL(startPos.x, 3);
    BOOST_CHECK_EQUAL(startPos.y, 8);
    
    game.movePlayer(SB::Direction::Up);
    auto afterUp = game.playerLoc();
    BOOST_CHECK_EQUAL(afterUp.x, startPos.x);
    BOOST_CHECK_EQUAL(afterUp.y, startPos.y - 1);
    
    game.movePlayer(SB::Direction::Left);
    auto afterLeft = game.playerLoc();
    BOOST_CHECK_EQUAL(afterLeft.x, startPos.x - 1);
    BOOST_CHECK_EQUAL(afterLeft.y, startPos.y - 1);
}

BOOST_AUTO_TEST_CASE(BoxWallCollisionTest) {
    SB::Sokoban game("box_wall.lvl");
    auto initialPos = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(game.playerLoc().x, initialPos.x);
}

BOOST_AUTO_TEST_CASE(BoxBoxCollisionTest) {
    SB::Sokoban game("box_box.lvl");
    auto initialPos = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(game.playerLoc().x, initialPos.x);
}

BOOST_AUTO_TEST_CASE(PlayerOffScreenTest) {
    std::ofstream out("offscreen.lvl");
    out << "3 3\n@..\n...\n...";
    out.close();
    SB::Sokoban game("offscreen.lvl");
    auto initialPos = game.playerLoc();
    game.movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(game.playerLoc().x, initialPos.x);
    BOOST_CHECK_EQUAL(game.playerLoc().y, initialPos.y);
}

BOOST_AUTO_TEST_CASE(PushOffScreenTest) {
    SB::Sokoban game("push_offscreen.lvl");
    auto initialPos = game.playerLoc();
    game.movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(game.playerLoc().x, initialPos.x);
    BOOST_CHECK_EQUAL(game.playerLoc().y, initialPos.y);
}
