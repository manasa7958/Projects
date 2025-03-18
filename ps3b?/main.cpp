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
    if (!(std::istringstream(argv[1]) >> totalDuration) || !(std::istringstream(argv[2]) >> timeIncrement) || totalDuration <= 0 || timeIncrement <= 0) {
        std::cerr << "Error: Time values must be positive." << std::endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(800, 800), "The Solar System!");
    window.setFramerateLimit(60);

    NB::Universe universe;
    if (!(std::cin >> universe)) {
        std::cerr << "Error: Failed to load universe data." << std::endl;
        return -1;
    }
    if (universe.size() == 0) {
        std::cerr << "Error: No celestial bodies available in input." << std::endl;
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
        sf::RenderStates states;
        states.transform.scale(2.0f, 2.0f); // Adjust scaling factor as needed
        window.draw(universe, states);
        window.display();
    }

    std::cout << universe;
    return 1;
}
