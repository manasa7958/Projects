// Copyright Manasa Praveen 2025
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>

namespace SB {

sf::Texture Sokoban::wallTexture, Sokoban::groundTexture,
Sokoban::playerTexture, Sokoban::boxTexture,
Sokoban::storageTexture;

sf::Font Sokoban::font;
bool Sokoban::texturesLoaded = false;

Sokoban::Sokoban() : gameWon(false), moveCount(0) {}

Sokoban::Sokoban(const std::string& filename) :
originalLevelFile(filename), gameWon(false), moveCount(0) {
    loadTextures();
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Failed to open level file");
    file >> *this;
}

unsigned int Sokoban::height() const { return grid.size(); }
unsigned int Sokoban::width() const { return grid.empty() ? 0 : grid[0].size(); }

sf::Vector2u Sokoban::playerLoc() const { return playerPos; }

bool Sokoban::isWon() const {
    for (const auto& row : grid) {
        for (char tile : row) {
            if (tile == 'a') {
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
        case Direction::Up:    dy = -1; break;
        case Direction::Down:  dy = 1; break;
        case Direction::Left:  dx = -1; break;
        case Direction::Right: dx = 1; break;
    }

    int newX = playerPos.x + dx;
    int newY = playerPos.y + dy;

    if (newX < 0 || newX >= static_cast<int>(width()) ||
        newY < 0 || newY >= static_cast<int>(height()) ||
        grid[newY][newX] == '#') {
        return;  // Player can't move into walls or out of bounds
    }

    char targetTile = grid[newY][newX];

    if (targetTile == 'A') {  // If the player is trying to push a box
        int boxNewX = newX + dx;
        int boxNewY = newY + dy;

        if (boxNewX < 0 || boxNewX >= static_cast<int>(width()) ||
            boxNewY < 0 || boxNewY >= static_cast<int>(height()) ||
            grid[boxNewY][boxNewX] == '#' || grid[boxNewY][boxNewX] == 'A') {
            return;  // Box can't be moved
        }

        // Move the box to the next position
        if (grid[boxNewY][boxNewX] == 'a') {
            grid[boxNewY][boxNewX] = 'A';  // Box is on a storage spot
        } else {
            grid[boxNewY][boxNewX] = 'A';  // Box is on a regular spot
        }

        // The player's new position will become either empty or a storage spot
        grid[newY][newX] = '@';  // Player occupies the box's old position
    } else if (targetTile == '.' || targetTile == 'a') {
        // Move the player to the new position (empty space or storage spot)
        grid[newY][newX] = '@';
    } else {
        return;  // Invalid move
    }

    // Set the player's current position to either a storage spot or empty space
    grid[playerPos.y][playerPos.x] = (grid[playerPos.y][playerPos.x] == 'a') ? 'a' : '.';

    // Update player position
    playerPos.x = newX;
    playerPos.y = newY;

    moveCount++;

    // Check if all storage spots are filled with boxes
    if (isWon()) {
        gameWon = true;
    }
}

void Sokoban::reset() {
    *this = Sokoban(originalLevelFile);
}

int Sokoban::getMoveCount() const { return moveCount; }

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite;

    // Draw the game grid
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);

            if (grid[y][x] == '#') {
                sprite.setTexture(wallTexture);
            } else {
                sprite.setTexture(groundTexture);
            }
            target.draw(sprite, states);
        }
    }

    // Draw the entities (player, boxes, storage spots)
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);

            switch (grid[y][x]) {
                case '@': sprite.setTexture(playerTexture); break;
                case 'A': sprite.setTexture(boxTexture); break;
                case 'a': sprite.setTexture(storageTexture); break;
                default: continue;
            }
            target.draw(sprite, states);
        }
    }

    // Draw move count
    if (fontLoaded) {
        sf::Text moveText("Moves: " + std::to_string(moveCount), font, 20);
        moveText.setPosition(10, 10);
        moveText.setFillColor(sf::Color::White);
        target.draw(moveText, states);
    }

    // Draw "You Win" message if the game is won
    if (gameWon && fontLoaded) {
        sf::Text winText("You Win!", font, 120);  // Increased font size to 72
        winText.setFillColor(sf::Color::Yellow);  // Victory message in yellow
        winText.setPosition(width() * TILE_SIZE / 2 - winText.getGlobalBounds().width / 2,
                            height() * TILE_SIZE / 2 - winText.getGlobalBounds().height / 2);
        target.draw(winText, states);
    }
}

void Sokoban::loadTextures() {
    if (!texturesLoaded) {
        if (!wallTexture.loadFromFile("block_06.png") ||
            !groundTexture.loadFromFile("ground_01.png") ||
            !playerTexture.loadFromFile("player_05.png") ||
            !boxTexture.loadFromFile("crate_03.png") ||
            !storageTexture.loadFromFile("ground_04.png")) {
            throw std::runtime_error("Failed to load textures");
        }
        texturesLoaded = true;
    }
}

std::ostream& operator<<(std::ostream& out, const Sokoban& s) {
    out << s.height() << " " << s.width() << "\n";
    for (const auto& row : s.grid) {
        out << row << "\n";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Sokoban& s) {
    size_t h, w;
    in >> h >> w;
    in.ignore();

    s.grid.resize(h);
    for (size_t y = 0; y < h; ++y) {
        std::getline(in, s.grid[y]);
        auto playerIdx = s.grid[y].find('@');
        if (playerIdx != std::string::npos) {
            s.playerPos = {static_cast<unsigned int>(playerIdx), static_cast<unsigned int>(y)};
        }
    }
    return in;
}

}  // namespace SB
