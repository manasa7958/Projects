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
            std::cerr << "Invalid! Using default size.\n";
            size = 200.0f;
        }
        if (depth < 0) {
            std::cerr << "Invalid! Using default depth.\n";
            depth = 5;
        }
    }

    // Calculate appropriate window size dynamically
    float margin = 50.0f; // Extra padding to avoid touching edges
    float windowWidth = size * 2.5f + margin;
    float windowHeight = size * std::sqrt(3.0f) + margin;
    
    // Adjust size so that the fractal fits within the window
    float scaleFactor = std::min((windowWidth - margin) / (size * 2.5f), (windowHeight - margin) / (size * std::sqrt(3.0f)));
    float adjustedSize = size * scaleFactor;
    
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)), "Triangle Fractal");
    Triangle fractal(windowWidth / 2.0f, windowHeight - margin, adjustedSize, depth);
    
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
