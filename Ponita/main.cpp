// Copyright 2025 Ponita Ty
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Universe.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " T dt < universe_file" << std::endl;
        return 1;
    }

    double T;
    std::istringstream ss(argv[1]);
    ss >> T;
    double dt;
    std::istringstream ss1(argv[2]);
    ss1 >> dt;

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

    double elapsed = 0.0;
    sf::Clock clock;

    while (window.isOpen() && elapsed < T) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        universe.step(dt);
        elapsed += dt;

        window.clear(sf::Color(0, 0, 20));
        window.draw(universe);
        window.display();
    }
    std::cout << universe;
    return 0;
}
