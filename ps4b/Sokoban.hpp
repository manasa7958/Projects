// Copyright Manasa Praveen 2025
#pragma once

#include <iostream>
#include <vector>
#include <string>
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

    unsigned int pixelHeight() const;  // Optional
    unsigned int pixelWidth() const;   // Optional

    unsigned int height() const;
    unsigned int width() const;

    sf::Vector2u playerLoc() const;

    bool isWon() const;

    void movePlayer(Direction dir);
    void loadTextures();
    void reset();

    void undo();  // Optional XC
    void redo();  // Optional XC

    int getMoveCount() const;

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    std::vector<std::string> grid;
    sf::Vector2u playerPos;
    std::string originalLevelFile;
    bool gameWon = false;
    int moveCount = 0;
    bool fontLoaded = true;

    static sf::Texture wallTexture;
    static sf::Texture groundTexture;
    static sf::Texture playerTexture;
    static sf::Texture boxTexture;
    static sf::Texture storageTexture;
    static sf::Font font;
    static bool texturesLoaded;

    friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
    friend std::istream& operator>>(std::istream& in, Sokoban& s);
};

}  // namespace SB
