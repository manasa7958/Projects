// Copyright Manasa Praveen 2025
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace SB {

sf::Texture Sokoban::wallTexture;
sf::Texture Sokoban::groundTexture;
sf::Texture Sokoban::playerTexture;
sf::Texture Sokoban::boxTexture;
sf::Texture Sokoban::storageTexture;
sf::Texture Sokoban::playerTextureUp;
sf::Texture Sokoban::playerTextureDown;
sf::Texture Sokoban::playerTextureLeft;
sf::Texture Sokoban::playerTextureRight;
sf::Font Sokoban::font;
bool Sokoban::texturesLoaded = false;
bool Sokoban::audioAvailable = true;

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
        !playerTextureDown.loadFromFile("player_05.png") ||
        !playerTextureUp.loadFromFile("player_08.png")   ||
        !playerTextureRight.loadFromFile("player_17.png")||
        !playerTextureLeft.loadFromFile("player_20.png") ||
        !font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        throw std::runtime_error("Failed to load one or more textures/fonts");
    }
    try {
        if (!victoryBuffer.loadFromFile("victory.wav")) {
            audioAvailable = false;
        } else {
            victorySound.setBuffer(victoryBuffer);
        }
    } catch (...) {
        audioAvailable = false;
    }
    texturesLoaded = true;
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

    if (dest != '.' && dest != 'a' && dest != 'A' && dest != 'B') return;

    bool moved = false;

    if (dest == 'A' || dest == 'B') {
        int nnx = nx + dx;
        int nny = ny + dy;
        if (nnx < 0 || nny < 0 || nnx >= static_cast<int>(boardWidth) ||
            nny >= static_cast<int>(boardHeight)) return;

        char next = board[nny][nnx];
        if (next != '.' && next != 'a') return;

        saveState();

        board[nny][nnx] = (originalBoard[nny][nnx] == 'a') ? 'B' : 'A';
        board[ny][nx] = '@';
        board[y][x] = (originalBoard[y][x] == 'a') ? 'a' : '.';
        playerPosition = {static_cast<unsigned int>(nx), static_cast<unsigned int>(ny)};
        moveCount++;
        moved = true;
    } else {
        saveState();

        board[ny][nx] = '@';
        board[y][x] = (originalBoard[y][x] == 'a') ? 'a' : '.';
        playerPosition = {static_cast<unsigned int>(nx), static_cast<unsigned int>(ny)};
        moveCount++;
        moved = true;
    }

    if (moved) {
        lastDirection = dir;
        moveCounterText.setString("Moves: " + std::to_string(moveCount));
    }

    gameWon = isWon();
    if (gameWon && audioAvailable) {
        victorySound.play();
    }
}

} // namespace SB
