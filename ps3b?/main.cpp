// main.cpp - Customized Version
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Universe.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " T dt < universe_file" << std::endl;
        return 1;
    }

    double totalTime;
    std::istringstream ss(argv[1]);
    ss >> totalTime;
    double timeStep;
    std::istringstream ss1(argv[2]);
    ss1 >> timeStep;

    sf::RenderWindow window(sf::VideoMode(500, 500), "Galactic Simulation");
    window.setFramerateLimit(60);

    NB::Universe galaxy;
    try {
        std::cin >> galaxy;
        std::cout << "Loaded galaxy with " << galaxy.size()
                  << " celestial objects and size " << galaxy.radius() << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error loading galaxy: " << ex.what() << std::endl;
        return 1;
    }

    double elapsedTime = 0.0;
    sf::Clock clock;

    while (window.isOpen() && elapsedTime < totalTime) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        galaxy.step(timeStep);
        elapsedTime += timeStep;

        window.clear(sf::Color(10, 10, 40));
        window.draw(galaxy);
        window.display();
    }
    std::cout << galaxy;
    return 0;
}
