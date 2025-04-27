// Copyright Manasa Praveen 2025
#pragma once

#include <vector>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace SB {

enum class Direction { Up, Down, Left, Right };

class Sokoban : public sf::Drawable {
    public:
        static const unsigned int TILE_SIZE = 64;

        Sokoban();
        Sokoban(const std::string& filename);

        void movePlayer(Direction dir);
        void reset();
        bool isWon() const;
        int getMoveCount() const;
        sf::Vector2u playerLoc() const;
        unsigned int width() const;
        unsigned int height() const;
        void undoMove();  // Undo feature!

        friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
        friend std::istream& operator>>(std::istream& in, Sokoban& s);

    private:
        struct GameState {
            std::vector<std::string> board;
            sf::Vector2u playerPosition;
            int moveCount;
        };

        std::vector<GameState> history;

        std::vector<std::string> board;
        std::vector<std::string> originalBoard;
        std::string originalLevelFile;
        unsigned int boardWidth;
        unsigned int boardHeight;
        sf::Vector2u playerPosition;
        int moveCount = 0;
        Direction lastDirection;
        bool gameWon = false;

        sf::Text moveCounterText;

        static sf::Texture wallTexture;
        static sf::Texture groundTexture;
        static sf::Texture boxTexture;
        static sf::Texture storageTexture;
        static sf::Texture playerTexture;
        static sf::Texture playerTextureUp;
        static sf::Texture playerTextureDown;
        static sf::Texture playerTextureLeft;
        static sf::Texture playerTextureRight;
        static sf::Font font;
        static bool texturesLoaded;

        void loadTextures();
        void saveState();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::SoundBuffer victoryBuffer;
        sf::Sound victorySound;
};

}  // namespace SB
