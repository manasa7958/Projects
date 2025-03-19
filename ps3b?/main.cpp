// Copyright 2025 Manasa Praveen
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Universe.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Invalid input format." << std::endl;
        return -1;
    }

    double totalDuration, timeIncrement;
    if (!(std::istringstream(argv[1]) >> totalDuration) ||
        !(std::istringstream(argv[2]) >> timeIncrement) ||
        totalDuration <= 0 || timeIncrement <= 0) {
        std::cerr << "Error: Time values must be positive." << std::endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(800, 800), "The Solar System!");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.jpg")) {
        std::cerr << "Error: Could not load background image." << std::endl;
    }
    sf::Sprite background(backgroundTexture);
    background.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y );
    
    NB::Universe universe;
    if (!(std::cin >> universe)) {
        std::cerr << "Error: Failed to load universe data." << std::endl;
        return -1;
    }
    if (universe.size() == 0) {
        std::cerr << "Error: No celestial bodies found." << std::endl;
        return -1;
    }

    double elapsedTime = 0.0;
    while (window.isOpen() && elapsedTime + timeIncrement <= totalDuration) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        universe.step(timeIncrement);
        elapsedTime += timeIncrement;

        window.clear(sf::Color(15, 15, 60));
        window.draw(background);
        window.draw(universe);
        window.display();
    }

    std::cout << universe;
    return 1;
}
