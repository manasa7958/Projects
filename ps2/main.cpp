// Copyright 2025 Manasa Praveen and Ponita Ty
#include <iostream>
#include <SFML/Graphics.hpp>
#include "triangle.hpp"
#include <cstdlib> // For std::atoi

int main(int argc, char* argv[]) {
    // Default values
    float size = 200.0f;
    int depth = 5;

    // Check if the user provided arguments
    if (argc == 3) {
        size = std::atof(argv[1]); // Convert first argument to float (size)
        depth = std::atoi(argv[2]); // Convert second argument to int (depth)

        // Validate inputs
        if (size <= 0) {
            std::cerr << "Invalid size! Using default size of 200.\n";
            size = 200.0f;
        }
        if (depth < 0) {
            std::cerr << "Invalid depth! Using default depth of 5.\n";
            depth = 5;
        }
    }

    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle Fractal");

    // Create fractal with user-specified size and depth
    Triangle fractal(400.0f, 400.0f, size, depth);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(fractal);
        window.display();
    }

    return 0;
}
