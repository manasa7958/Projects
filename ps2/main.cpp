// Copyright 2025 Manasa Praveen
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
    } else {
        std::cout << "Usage: ./Triangle <size> <depth>\n";
        std::cout << "Example: ./Triangle 400 5\n";
        std::cout << "Using default values: size = " << size << ", depth = " << depth << "\n";
    }

    // Calculate window dimensions dynamically based on size
    float height = size * std::sqrt(3.0f) / 2.0f; // Triangle height
    int windowWidth = std::max(static_cast<int>(size * 1.2f), 800);  // Ensure a minimum width
    int windowHeight = std::max(static_cast<int>(height * 1.2f), 600); // Ensure a minimum height

    // Cap window size to prevent excessive scaling
    int maxWindowSize = 1200;
    if (windowWidth > maxWindowSize || windowHeight > maxWindowSize) {
        float scaleFactor = static_cast<float>(maxWindowSize) / std::max(windowWidth, windowHeight);
        windowWidth *= scaleFactor;
        windowHeight *= scaleFactor;
        size *= scaleFactor;
    }

    // Create a rescaled window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Triangle Fractal");

    // Center the triangle within the new window dimensions
    Triangle fractal(windowWidth / 2.0f, windowHeight * 0.75f, size, depth);

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
