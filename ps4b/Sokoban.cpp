// Copyright Manasa praveen 2025
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>

namespace SB {

Sokoban::Sokoban() : boardWidth(0), boardHeight(0) {}

Sokoban::Sokoban(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Unable to open file");
    file >> *this;
    originalBoard = board;
    if (!wallTexture.loadFromFile("block_06.png")) {
        throw std::runtime_error("Failed to load wall");
    }
    if (!boxTexture.loadFromFile("crate_03.png")) {
        throw std::runtime_error("Failed to load box");
    }
    if (!groundTexture.loadFromFile("ground_01.png")) {
        throw std::runtime_error("Failed to load ground");
    }
    if (!storageTexture.loadFromFile("ground_04.png")) {
        throw std::runtime_error("Failed to load storage");
    }
    if (!playerTexture.loadFromFile("player_05.png")) {
        throw std::runtime_error("Failed to load player");
    }
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    reset();
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

const std::vector<sf::Vector2u>& SB::Sokoban::boxLocs() const {
    return boxes;
}

bool Sokoban::isWon() const {
    for (unsigned int y = 0; y < boardHeight; ++y) {
        for (unsigned int x = 0; x < boardWidth; ++x) {
            if (originalBoard[y][x] == 'a' && board[y][x] != 'B' && board[y][x] != 'A') {
                return false;
            }
        }
    }
    return true;
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
        board[nny][nnx] = (originalBoard[nny][nnx] == 'a') ? 'B' : 'A';
        board[ny][nx] = (originalBoard[ny][nx] == 'a') ? 'a' : '.';
        board[y][x] = (originalBoard[y][x] == 'a') ? 'a' : '.';
        board[ny][nx] = '@';
        playerPosition = { static_cast<unsigned int>(nx),
            static_cast<unsigned int>(ny) };
    } else if (dest == '.' || dest == ' ' || dest == 'a') {
        board[y][x] = (originalBoard[y][x] == 'a') ? 'a' : '.';
        board[ny][nx] = '@';
        playerPosition = { static_cast<unsigned int>(nx),
            static_cast<unsigned int>(ny) };
    }

    gameWon = isWon();
}

void Sokoban::reset() {
    board = originalBoard;
    gameWon = false;
    boardWidth = originalBoard[0].size();
    boardHeight = originalBoard.size();
    for (unsigned int y = 0; y < board.size(); ++y) {
        for (unsigned int x = 0; x < board[y].size(); ++x) {
            if (board[y][x] == '@') {
                playerPosition = {static_cast<unsigned int>(x), y};
            }
            if (originalBoard[y][x] == 'a' && board[y][x] == 'A') {
                board[y][x] = 'B';
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
    if (gameWon) {
        sf::Text winText;
        winText.setFont(font);
        winText.setString("You Win!");
        winText.setCharacterSize(48);
        winText.setFillColor(sf::Color::Yellow);
        winText.setPosition(boardWidth * TILE_SIZE /
            2 - 100, boardHeight * TILE_SIZE / 2 - 50);
        target.draw(winText, states);
    }
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
    s.board.clear();
    s.board.resize(s.boardHeight);
    in.ignore();
    for (unsigned int i = 0; i < s.boardHeight; ++i) {
        std::getline(in, s.board[i]);
        if (s.board[i].length() != s.boardWidth)
            throw std::runtime_error("Invalid row width");
        for (char c : s.board[i]) {
            if (c != '#' && c != '.' && c != ' ' && c != 'a' &&
                c != 'A' && c != '@') {
                std::cout << "INVALID CHARACTER: '" << c << "'\n";
                throw std::runtime_error(std::string("Invalid symbol: ") + c);
            }
        }
        auto pos = s.board[i].find('@');
        if (pos != std::string::npos) {
            s.playerPosition = sf::Vector2u(pos, i);
        }
    }
    return in;
}

}  // namespace SB
