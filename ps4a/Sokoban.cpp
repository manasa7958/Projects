//Copyright Manasa praveen 2025
#include "Sokoban.hpp"
#include <fstream>
#include <stdexcept>

namespace SB {

Sokoban::Sokoban() : boardWidth(0), boardHeight(0) {}

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
    // Check if all storage locations have boxes
    for (const auto& row : board) {
        if (row.find('a') != std::string::npos) {
            return false;
        }
    }
    return true;
}

void Sokoban::movePlayer(Direction dir) {
    // Placeholder for movement logic (to be implemented in Part B)
}

void Sokoban::reset() {
    // Reset game state logic (to be implemented)
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
