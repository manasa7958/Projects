// Copyright 2025 Manasa Praveen 
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Universe.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Incorrect usage. Format: " << argv[0] << " <duration> <time_step> < input_file" << std::endl;
        return EXIT_FAILURE;
    }

    double simulationTime, stepSize;
    if (!(std::istringstream(argv[1]) >> simulationTime) || !(std::istringstream(argv[2]) >> stepSize) || simulationTime <= 0 || stepSize <= 0) {
        std::cerr << "Error: Duration and step size must be positive numbers." << std::endl;
        return EXIT_FAILURE;
    }

    sf::RenderWindow simulationWindow(sf::VideoMode(600, 600), "N-Body Simulation");
    simulationWindow.setFramerateLimit(60);

    NB::Universe cosmicSystem;
    try {
        std::cin >> cosmicSystem;
        if (cosmicSystem.size() == 0) {
            std::cerr << "Error: No celestial bodies detected in input." << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << "Loaded Universe: " << cosmicSystem.size() << " objects within radius " << cosmicSystem.radius() << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Failed to load universe data: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    double elapsedTime = 0.0;
    while (simulationWindow.isOpen() && elapsedTime + stepSize <= simulationTime) {
        sf::Event event;
        while (simulationWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                simulationWindow.close();
            }
        }

        cosmicSystem.step(stepSize);
        elapsedTime += stepSize;

        simulationWindow.clear(sf::Color(10, 10, 40));
        simulationWindow.draw(cosmicSystem);
        simulationWindow.display();
    }

    std::cout << cosmicSystem;
    return EXIT_SUCCESS;
}
