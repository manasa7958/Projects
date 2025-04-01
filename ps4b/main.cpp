// Copyright Manasa Praveen 2025
#include <iostream>
#include <string>
#include "sfml_fix.hpp" // IRRELEVANT, using because of problems in terminal
#include "Sokoban.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <level_file>\n";
        return 1;
    }

    SB::Sokoban game(argv[1]);

    sf::RenderWindow window(sf::VideoMode(game.width() * SB::Sokoban::TILE_SIZE,
        game.height() * SB::Sokoban::TILE_SIZE), "Sokoban");

    // Extra Credit: Victory Fanfare!!
    sf::SoundBuffer victoryBuffer;
    if (!victoryBuffer.loadFromFile("victory.wav")) {
        std::cerr << "Failed to load victory sound\n";
        return 1;
    }
    sf::Sound victorySound;
    victorySound.setBuffer(victoryBuffer);

    bool playedVictorySound = false;
    
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
            } else if (!playedVictorySound) {
                victorySound.play();
                playedVictorySound = true;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                game.reset();
                playedVictorySound = false;
            }
        }

        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}
