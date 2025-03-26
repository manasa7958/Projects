// Copyright Manasa praveen 2025
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>

namespace SB {

Sokoban::Sokoban() : boardWidth(0), boardHeight(0) {}

Sokoban::Sokoban(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open file");
    }
    file >> *this;
    originalBoard = board;

    if (!wallTexture.loadFromFile("block_06.png")) {
        throw std::runtime_error("Failed to load wall texture");
    }
    if (!boxTexture.loadFromFile("crate_03.png")) {
        throw std::runtime_error("Failed to load box texture");
    }
    if (!groundTexture.loadFromFile("ground_01.png")) {
        throw std::runtime_error("Failed to load ground texture");
    }
    if (!storageTexture.loadFromFile("ground_04.png")) {
        throw std::runtime_error("Failed to load storage texture");
    }
    if (!playerTexture.loadFromFile("player_05.png")) {
        throw std::runtime_error("Failed to load player texture");
    }
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
    throw std::runtime_error("Failed to load system font");
    }
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

bool Sokoban::isWon() const {
    return std::none_of(board.begin(), board.end(), [](const std::string& row) {
        return row.find('a') != std::string::npos;
    });
}

/*void Sokoban::movePlayer(Direction dir) {
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

    char& dest = board[ny][nx];
    char& curr = board[y][x];

    if (dest == '#') return;

    if (dest == 'A' || dest == 'a') {
        int nnx = nx + dx;
        int nny = ny + dy;
        if (nnx < 0 || nny < 0 || nnx >= static_cast<int>(boardWidth) ||
            nny >= static_cast<int>(boardHeight)) return;
        char& next = board[nny][nnx];

        if (next == '.' || next == 'a') {
            next = 'A';
            dest = '@';
            curr = (originalBoard[y][x] == 'a') ? 'a' : '.';
            playerPosition = { static_cast<unsigned int>(nx), static_cast<unsigned int>(ny) };
        }
    } else if (dest == '.' || dest == ' ') {
        dest = '@';
        curr = (originalBoard[y][x] == 'a') ? 'a' : '.';
        playerPosition = { static_cast<unsigned int>(nx), static_cast<unsigned int>(ny) };
    }
    gameWon = isWon();
}*/
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

    // Bounds check
    if (nx < 0 || ny < 0 || nx >= static_cast<int>(boardWidth) ||
        ny >= static_cast<int>(boardHeight)) return;

    char& dest = board[ny][nx];
    char& curr = board[y][x];

    // Wall blocks movement
    if (dest == '#') return;

    // --- Handle pushing box
    if (dest == 'A' || dest == 'a') {
        int nnx = nx + dx;
        int nny = ny + dy;
        if (nnx < 0 || nny < 0 || nnx >= static_cast<int>(boardWidth) ||
            nny >= static_cast<int>(boardHeight)) return;

        char& next = board[nny][nnx];

        // Cannot push into a wall or another box
        if (next == '#' || next == 'A' || next == 'a') return;

        // Move the box
        next = 'A';

        // Replace box's previous location with original tile
        dest = (originalBoard[ny][nx] == 'a') ? 'a' : '.';

        // Move player into the box's previous spot
        board[ny][nx] = '@';
        curr = (originalBoard[y][x] == 'a') ? 'a' : '.';
        playerPosition = { static_cast<unsigned int>(nx), static_cast<unsigned int>(ny) };
    }

    // --- Regular move
    else if (dest == '.' || dest == 'a' || dest == ' ') {
        board[ny][nx] = '@';
        curr = (originalBoard[y][x] == 'a') ? 'a' : '.';
        playerPosition = { static_cast<unsigned int>(nx), static_cast<unsigned int>(ny) };
    }

    gameWon = isWon();
}

void Sokoban::reset() {
    board = originalBoard;
    gameWon = false;
    boardWidth = originalBoard[0].size();
    boardHeight = originalBoard.size();
    for (unsigned int y = 0; y < board.size(); ++y) {
        auto pos = board[y].find('@');
        if (pos != std::string::npos) {
            playerPosition = {static_cast<unsigned int>(pos), y};
            break;
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
            } else if (tile == 'A') {
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
        auto pos = s.board[i].find('@');
        if (pos != std::string::npos) {
            s.playerPosition = sf::Vector2u(pos, i);
        }
    }
    return in;
}

}  // namespace SB
