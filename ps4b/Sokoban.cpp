// Sokoban.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>

namespace SB {

Sokoban::Sokoban() : boardWidth(0), boardHeight(0), gameWon(false) {}

Sokoban::Sokoban(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Unable to open file");
    file >> *this;
    originalBoard = board;
    loadTextures();
    reset();
}

void Sokoban::loadTextures() {
    if (!wallTexture.loadFromFile("block_06.png")) throw std::runtime_error("Failed to load wall texture");
    if (!boxTexture.loadFromFile("crate_03.png")) throw std::runtime_error("Failed to load box texture");
    if (!groundTexture.loadFromFile("ground_01.png")) throw std::runtime_error("Failed to load ground texture");
    if (!storageTexture.loadFromFile("ground_04.png")) throw std::runtime_error("Failed to load storage texture");
    if (!playerTexture.loadFromFile("player_05.png")) throw std::runtime_error("Failed to load player texture");
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) throw std::runtime_error("Failed to load font");
}

unsigned int Sokoban::width() const { return boardWidth; }

unsigned int Sokoban::height() const { return boardHeight; }

sf::Vector2u Sokoban::playerLoc() const { return playerPosition; }

// >>, << operators for board reading and writing
std::ostream& operator<<(std::ostream& out, const Sokoban& s) {
    out << s.boardHeight << " " << s.boardWidth << "\n";
    for (const auto& row : s.board) {
        out << row << "\n";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Sokoban& s) {
    in >> s.boardHeight >> s.boardWidth;
    s.board.clear();
    s.board.resize(s.boardHeight);
    in.ignore();
    for (unsigned int i = 0; i < s.boardHeight; ++i) {
        std::getline(in, s.board[i]);
        if (s.board[i].length() != s.boardWidth) throw std::runtime_error("Invalid row width");

        for (char c : s.board[i]) {
            if (c != '#' && c != '.' && c != ' ' && c != 'a' && c != 'A' && c != '@') {
                throw std::invalid_argument(std::string("Invalid symbol: ") + c);
            }
        }
        // Find the player '@' in the initial board setup
        auto pos = s.board[i].find('@');
        if (pos != std::string::npos) {
            s.playerPosition = { static_cast<unsigned int>(pos), i };
        }
    }
    return in;
}

// Movement Logic
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

    if (nx < 0 || ny < 0 || nx >= static_cast<int>(boardWidth) || ny >= static_cast<int>(boardHeight)) return;

    char dest = board[ny][nx];
    if (dest == '#') return;  // Wall blocking movement

    // Handling box movement
    if (dest == 'A' || dest == 'B') {
        int nnx = nx + dx;
        int nny = ny + dy;
        if (nnx < 0 || nny < 0 || nnx >= static_cast<int>(boardWidth) || nny >= static_cast<int>(boardHeight)) return;
        char next = board[nny][nnx];
        if (next == '#' || next == 'A' || next == 'B') return;  // Blocked by a wall or another box

        // Move box to the next position
        board[nny][nnx] = (originalBoard[nny][nnx] == 'a') ? 'B' : 'A';  // Box turns into 'B' on target
        board[ny][nx] = '@';  // Move player to where the box was
        board[y][x] = (originalBoard[y][x] == 'a') ? 'a' : '.';  // Restore previous player's tile

        playerPosition = { static_cast<unsigned int>(nx), static_cast<unsigned int>(ny) };
    } else {
        // Move player to the new location
        board[ny][nx] = '@';
        board[y][x] = (originalBoard[y][x] == 'a') ? 'a' : '.';
        playerPosition = { static_cast<unsigned int>(nx), static_cast<unsigned int>(ny) };
    }

    // Check if the game is won
    gameWon = isWon();
}

// Updated Victory Condition
bool Sokoban::isWon() const {
    int boxesOnTargets = 0;
    int totalTargets = 0;
    int totalBoxes = 0;

    for (unsigned int y = 0; y < boardHeight; ++y) {
        for (unsigned int x = 0; x < boardWidth; ++x) {
            char curr = board[y][x];
            char orig = originalBoard[y][x];

            if (curr == 'A' || curr == 'B') totalBoxes++;  // Count total boxes
            if (orig == 'a') totalTargets++;  // Count total targets
            if (curr == 'B') boxesOnTargets++;  // Count boxes on targets
        }
    }

    // Win if either all boxes are on targets or all targets are filled with boxes
    return (boxesOnTargets == totalBoxes || boxesOnTargets == totalTargets);
}

// Reset Game to Initial State
void Sokoban::reset() {
    board = originalBoard;
    gameWon = false;
    for (unsigned int y = 0; y < board.size(); ++y) {
        for (unsigned int x = 0; x < board[y].size(); ++x) {
            if (board[y][x] == '@') {
                playerPosition = {x, y};
                return;
            }
        }
    }
    throw std::runtime_error("Player position '@' not found in level");
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

    if (gameWon) {
        sf::Text winText;
        winText.setFont(font);
        winText.setString("You Win!");
        winText.setCharacterSize(48);
        winText.setFillColor(sf::Color::Yellow);
        winText.setPosition(boardWidth * TILE_SIZE / 2 - 100, boardHeight * TILE_SIZE / 2 - 50);
        target.draw(winText, states);
    }
}

}  // namespace SB
