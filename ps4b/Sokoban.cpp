// Copyright Manasa praveen 2025
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>

namespace SB {

sf::Texture Sokoban::wallTexture;
sf::Texture Sokoban::groundTexture;
sf::Texture Sokoban::playerTexture;
sf::Texture Sokoban::boxTexture;
sf::Texture Sokoban::storageTexture;
sf::Font Sokoban::font;
bool Sokoban::texturesLoaded = false;

Sokoban::Sokoban() : boardWidth(0), boardHeight(0) {}

Sokoban::Sokoban(const std::string& filename) : originalLevelFile(filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Unable to open file");

    file >> *this;

    originalBoard = board;
    loadTextures();
    reset();
}

void Sokoban::loadTextures() {
    if (texturesLoaded) return;

    if (!wallTexture.loadFromFile("block_06.png") ||
        !boxTexture.loadFromFile("crate_03.png") ||
        !groundTexture.loadFromFile("ground_01.png") ||
        !storageTexture.loadFromFile("ground_04.png") ||
        !playerTexture.loadFromFile("player_05.png") ||
        !font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        throw std::runtime_error("Failed to load one or more textures/fonts");
    }

    texturesLoaded = true;
}

unsigned int Sokoban::width() const {
    return boardWidth;
}

unsigned int Sokoban::height() const {
    return boardHeight;
}

sf::Vector2u Sokoban::playerLoc() const {
    return playerPosition;
}

int Sokoban::getMoveCount() const {
    return moveCount;
}

bool Sokoban::isWon() const {
    if (board.empty() || originalBoard.empty()) return false;
    int boxesOnTargets = 0;
    int totalBoxes = 0;
    int totalTargets = 0;

    std::cout << "=== Debug isWon() ===\n";

    for (unsigned int y = 0; y < boardHeight; ++y) {
        for (unsigned int x = 0; x < boardWidth; ++x) {
            char curr = board[y][x];
            char original = originalBoard[y][x];

            std::cout << x << ", " << y << ": board=" << curr << " og=" << original << "\n";

            if (curr == 'A') totalBoxes++;
            if (curr == 'B') {
                totalBoxes++;
                boxesOnTargets++;
            }

            if (original == 'a') totalTargets++;
        }
    }

    std::cout << "totalBoxes: " << totalBoxes
              << " boxesOnTargets: " << boxesOnTargets
              << " totalTargets: " << totalTargets << "\n";

    bool win = (boxesOnTargets == totalBoxes || boxesOnTargets == totalTargets);
    std::cout << "isWon() returns: " << (win ? "true" : "false") << "\n";

    return win;
}

void Sokoban::movePlayer(Direction dir) {
    if (gameWon) return;

    int dx = 0, dy = 0;
    switch (dir) {
        case Direction::Up: dy = -1; break;
        case Direction::Down: dy = 1; break;
        case Direction::Left: dx = -1; break;
        case Direction::Right: dx = 1; break;
    }

    int x = playerPosition.x;
    int y = playerPosition.y;
    int nx = x + dx;
    int ny = y + dy;

    if (nx < 0 || ny < 0 || nx >= static_cast<int>(boardWidth) ||
        ny >= static_cast<int>(boardHeight)) return;

    char dest = board[ny][nx];

    if (dest == '#') return;

    if (dest == 'A' || dest == 'B') {
        int nnx = nx + dx;
        int nny = ny + dy;
        if (nnx < 0 || nny < 0 || nnx >= static_cast<int>(boardWidth) ||
            nny >= static_cast<int>(boardHeight)) return;

        char next = board[nny][nnx];
        if (next == '#' || next == 'A' || next == 'B') return;

        // Move the box
        board[nny][nnx] = (originalBoard[nny][nnx] == 'a') ? 'B' : 'A';
        board[ny][nx] = '@';
        board[y][x] = (originalBoard[y][x] == 'a') ? 'a' : '.';
        playerPosition = {static_cast<unsigned int>(nx), static_cast<unsigned int>(ny)};
        moveCount++;
    } else {
        // Regular move
        board[ny][nx] = '@';
        board[y][x] = (originalBoard[y][x] == 'a') ? 'a' : '.';
        playerPosition = {static_cast<unsigned int>(nx), static_cast<unsigned int>(ny)};
        moveCount++;
    }

    gameWon = isWon();
}

void Sokoban::reset() {
    if (originalBoard.empty()) return;

    board = originalBoard;
    boardHeight = board.size();
    boardWidth = board[0].size();
    moveCount = 0;
    gameWon = false;

    for (unsigned int y = 0; y < board.size(); ++y) {
        for (unsigned int x = 0; x < board[y].size(); ++x) {
            if (board[y][x] == '@') {
                playerPosition = {x, y};
            } else if (originalBoard[y][x] == 'a' && board[y][x] == 'A') {
                board[y][x] = 'B';  // Box is on the target
            }
        }
    }
}


void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (unsigned int y = 0; y < boardHeight; ++y) {
        for (unsigned int x = 0; x < boardWidth; ++x) {
            char tile = board[y][x];

            if (tile != '#') {
                sf::Sprite groundSprite;
                groundSprite.setTexture(groundTexture);
                groundSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                target.draw(groundSprite, states);
            }
            sf::Sprite sprite;
            if (tile == '#') {
                sprite.setTexture(wallTexture);
            } else if (tile == 'A' || tile == 'B') {
                sprite.setTexture(boxTexture);
            } else if (tile == 'a') {
                sprite.setTexture(storageTexture);
            } else if (tile == '@') {
                sprite.setTexture(playerTexture);
            } else {
                continue;
            }
            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            target.draw(sprite, states);
        }
    }
    /*if (gameWon) {
        sf::Text winText;
        winText.setFont(font);
        winText.setString("You Win!");
        winText.setCharacterSize(48);
        winText.setFillColor(sf::Color::Yellow);
        winText.setPosition(boardWidth * TILE_SIZE /
            2 - 100, boardHeight * TILE_SIZE / 2 - 50);
        target.draw(winText, states);
    }*/
}

std::ostream& operator<<(std::ostream& out, const Sokoban& s) {
    out << s.boardHeight << " " << s.boardWidth << "\n";
    for (const auto& row : s.board) {
        out << row << "\n";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Sokoban& s) {
    in >> s.boardHeight >> s.boardWidth;
    in.ignore();
    s.board.clear();
    s.board.resize(s.boardHeight, std::string(s.boardWidth, '.'));

    bool playerFound = false;
    for (unsigned int i = 0; i < s.boardHeight; ++i) {
        std::getline(in, s.board[i]);
        if (s.board[i].length() != s.boardWidth) {
            throw std::runtime_error("Level file row length mismatch");
        }

        for (unsigned int j = 0; j < s.boardWidth; ++j) {
            char c = s.board[i][j];

            if (c == '@') {
                if (playerFound) {
                    throw std::runtime_error("Multiple players '@' found in level file");
                }
                s.playerPosition = {j, i};
                playerFound = true;
            }
        }
    }

    if (!playerFound) {
        throw std::runtime_error("No player '@' found in level file");
    }

    s.originalBoard = s.board;
    return in;
}


}  // namespace SB
