// Copyright Manasa Praveen 2025
#include <iostream>
#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <level_file>\n";
        return 1;
    }

    SB::Sokoban game(argv[1]);
    sf::RenderWindow window(sf::VideoMode(game.width() * SB::Sokoban::TILE_SIZE, 
    game.height() * SB::Sokoban::TILE_SIZE), "Sokoban");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (!game.isWon()) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::W ||
                        event.key.code == sf::Keyboard::Up) {
                        game.movePlayer(SB::Direction::Up);
                    } else if (event.key.code == sf::Keyboard::S ||
                        event.key.code == sf::Keyboard::Down) {
                        game.movePlayer(SB::Direction::Down);
                    } else if (event.key.code == sf::Keyboard::A ||
                        event.key.code == sf::Keyboard::Left) {
                        game.movePlayer(SB::Direction::Left);
                    } else if (event.key.code == sf::Keyboard::D ||
                        event.key.code == sf::Keyboard::Right) {
                        game.movePlayer(SB::Direction::Right);
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                game.reset();
            }
        }

    window.clear();
    window.draw(game);
    window.display();
    }
    return 0;
}
