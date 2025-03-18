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
    std::istringstream timeStream(argv[1]);
    timeStream >> totalTime;
    double timeInterval;
    std::istringstream intervalStream(argv[2]);
    intervalStream >> timeInterval;

    sf::RenderWindow window(sf::VideoMode(600, 600), "Cosmic Motion");
    window.setFramerateLimit(60);

    NB::Universe galaxySimulation;
    try {
        std::cin >> galaxySimulation;
        std::cout << "Initialized universe with " << galaxySimulation.size()
                  << " bodies within a boundary of " << galaxySimulation.radius() << std::endl;
    } catch (const std::exception& err) {
        std::cerr << "Error loading universe data: " << err.what() << std::endl;
        return 1;
    }

    double elapsed = 0.0;
    sf::Clock simulationClock;

    while (window.isOpen() && elapsed < totalTime) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        galaxySimulation.step(timeInterval);
        elapsed += timeInterval;

        window.clear(sf::Color(15, 15, 50));
        window.draw(galaxySimulation);
        window.display();
    }
    std::cout << galaxySimulation;
    return 0;
}
