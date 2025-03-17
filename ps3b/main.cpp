// Copyright 2025 Manasa Praveen
#include <iostream>
#include "CelestialBody.hpp"
#include "Universe.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <T> <dt>" << std::endl;
        return 1;
    }

    double T = std::stod(argv[1]);
    double dt = std::stod(argv[2]);

    NB::Universe universe;
    std::cin >> universe;

    sf::RenderWindow window(sf::VideoMode(800, 800), "The Solar System!");
    
    sf::Font defaultFont;
    if (!defaultFont.loadFromFile("/System/Library/Fonts/Supplemental/Helvetica.ttc")) { 
        std::cerr << "Warning: Failed to load Helvetica. Continuing without font." << std::endl;
    }

    sf::Text elapsedTimeText;
    elapsedTimeText.setFont(defaultFont);
    elapsedTimeText.setCharacterSize(20);
    elapsedTimeText.setFillColor(sf::Color::White);
    elapsedTimeText.setPosition(10, 10);

    double elapsedTime = 0.0;

    while (window.isOpen() && elapsedTime < T) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        universe.step(dt);
        elapsedTime += dt;

        window.clear();
        window.draw(universe);

        elapsedTimeText.setString("Elapsed Time: " + std::to_string(static_cast<int>(elapsedTime)) + " s");
        window.draw(elapsedTimeText);

        window.display();
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    std::cout << universe;
    return 0;
}
