//Copyright Manasa praveen 2025
#include <iostream>
#include <fstream>
#include <vector>
#include "Sokoban.hpp"

namespace SB {

Sokoban::Sokoban() {}

Sokoban::Sokoban(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open file");
    }
    file >> *this;
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
    return false; // Placeholder, will be implemented in Part B
}

void Sokoban::movePlayer(Direction dir) {
    // Placeholder, will be implemented in Part B
}

void Sokoban::reset() {
    // Reset game state
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Rendering logic will be added here
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
    in.ignore(); // Ignore newline
    
    for (unsigned int i = 0; i < s.boardHeight; ++i) {
        std::getline(in, s.board[i]);
        auto pos = s.board[i].find('@');
        if (pos != std::string::npos) {
            s.playerPosition = sf::Vector2u(pos, i);
        }
    }
    return in;
}

} // namespace SB
