// Copyright Manasa praveen 2025
#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

namespace SB {
enum class Direction {
    Up, Down, Left, Right
};

class Sokoban : public sf::Drawable {
 public:
    static const int TILE_SIZE = 64;

    Sokoban();
    explicit Sokoban(const std::string&);  // Optional

    unsigned int pixelHeight() const;  // Optional
    unsigned int pixelWidth() const;  // Optional

    unsigned int height() const;
    unsigned int width() const;

    sf::Vector2u playerLoc() const;

    bool isWon() const;

    void movePlayer(Direction dir);
    void reset();

    void undo();  // Optional XC
    void redo();  // Optional XC

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    bool gameWon = false;
    unsigned int boardWidth;
    unsigned int boardHeight;
    sf::Vector2u playerPosition;
    std::vector<std::string> board;
    std::vector<std::string> originalBoard;
    std::string originalLevelFile;
    sf::Texture wallTexture;
    sf::Texture boxTexture;
    sf::Texture groundTexture;
    sf::Texture storageTexture;
    sf::Texture playerTexture;
    friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
    friend std::istream& operator>>(std::istream& in, Sokoban& s);
};
}  // namespace SB
