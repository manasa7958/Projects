// Copyright Manasa Praveen 2025
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "sfml_fix.hpp" // IRRELEVANT, using because of problems in terminal
#include <SFML/Graphics.hpp>

namespace SB {

enum class Direction {
    Up, Down, Left, Right
};

class Sokoban : public sf::Drawable {
 public:
    static const int TILE_SIZE = 64;

    Sokoban();
    explicit Sokoban(const std::string& filename);

    unsigned int width() const;
    unsigned int height() const;
    sf::Vector2u playerLoc() const;
    bool isWon() const;

    void movePlayer(Direction dir);
    void reset();
    int getMoveCount() const;

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    void loadTextures();

    std::vector<std::string> board;
    std::vector<std::string> originalBoard;
    sf::Vector2u playerPosition;
    unsigned int boardWidth;
    unsigned int boardHeight;
    std::string originalLevelFile;
    bool gameWon = false;
    int moveCount = 0;

    static sf::Texture wallTexture, groundTexture, playerTexture, boxTexture, storageTexture;
    static sf::Font font;
    static bool texturesLoaded;

    Direction lastDirection = Direction::Down;

    friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
    friend std::istream& operator>>(std::istream& in, Sokoban& s);
};

}  // namespace SB
