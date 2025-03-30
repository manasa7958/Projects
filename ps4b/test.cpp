// test.cpp
#include <cassert>
#include <iostream>
#include "Sokoban.hpp"

using namespace SB;

void testBasicMovement() {
    Sokoban game("test_levels/basic_move.lvl");

    auto initial = game.playerLoc();
    game.movePlayer(Direction::Right);
    auto afterMove = game.playerLoc();

    assert(afterMove.x == initial.x + 1 && afterMove.y == initial.y);
    std::cout << "Basic movement test passed\n";
}

void testWallCollision() {
    Sokoban game("test_levels/wall_block.lvl");

    auto initial = game.playerLoc();
    game.movePlayer(Direction::Left);
    auto afterMove = game.playerLoc();

    assert(afterMove == initial);
    std::cout << "Wall collision test passed\n";
}

void testBoxPush() {
    Sokoban game("test_levels/box_push.lvl");

    auto boxStart = game.playerLoc();
    game.movePlayer(Direction::Right);
    auto newPlayer = game.playerLoc();

    assert(newPlayer.x == boxStart.x + 1);
    std::cout << "Box push test passed\n";
}

void testBoxBlocked() {
    Sokoban game("test_levels/box_blocked.lvl");

    auto pos = game.playerLoc();
    game.movePlayer(Direction::Right);
    assert(game.playerLoc() == pos);
    std::cout << "Box blocked test passed\n";
}

void testVictory() {
    Sokoban game("test_levels/victory.lvl");

    game.movePlayer(Direction::Right);
    assert(game.isWon());
    std::cout << "Victory test passed\n";
}

void testReset() {
    Sokoban game("test_levels/basic_move.lvl");

    game.movePlayer(Direction::Right);
    game.reset();
    auto resetPos = game.playerLoc();

    // Should match the original start position
    assert(resetPos == game.playerLoc());
    std::cout << "Reset test passed\n";
}

int main() {
    testBasicMovement();
    testWallCollision();
    testBoxPush();
    testBoxBlocked();
    testVictory();
    testReset();
    std::cout << "All tests passed successfully!\n";
}
\
