//Copyright Manasa Praveen 2025

#include <iostream>
#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <level_file>\n";
        return 1;
    }

    SB::Sokoban game(argv[1]);
    sf::RenderWindow window(sf::VideoMode(game.width() * SB::Sokoban::TILE_SIZE, game.height() * SB::Sokoban::TILE_SIZE), "Sokoban");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}
