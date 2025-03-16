// Copyright 2025 Ponita Ty
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Universe.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 300), "The Solar System!");
    window.setFramerateLimit(60);

    NB::Universe universe;
    try {
        std::cin >> universe;
        std::cout << "Successfully loaded universe with " << universe.size()
        << " bodies and radius " << universe.radius() << std::endl;

        if (!universe.initBackground("starfield.jpg")) {
            std::cerr << "Warning: Could not load background image" << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error reading universe: " << ex.what() << std::endl;
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color(0, 0, 20));
        window.draw(universe);
        window.display();
    }

    return 0;
}
