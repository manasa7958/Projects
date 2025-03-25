// Copyright Manasa Praveen 2025
#include <iostream>
#include <fstream>
#include <string>
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

void Sokoban::movePlayer(Direction dir) {
}

void Sokoban::reset() {
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
