// Copyright 2025 Manasa Praveen
#include <iostream>
#include <SFML/Graphics.hpp>
#include "triangle.hpp"
#include <cstdlib> // For std::atoi
#include <algorithm> // For std::min and std::max

int main(int argc, char* argv[]) {
    // Default values
    float requestedSize = 200.0f;
    int depth = 5;

    // Check if the user provided arguments
    if (argc == 3) {
        requestedSize = std::atof(argv[1]); // Convert first argument to float (size)
        depth = std::atoi(argv[2]); // Convert second argument to int (depth)

        // Validate inputs
        if (requestedSize <= 0) {
            std::cerr << "Invalid size! Using default size of 200.\n";
            requestedSize = 200.0f;
        }
        if (depth < 0) {
            std::cerr << "Invalid depth! Using default depth of 5.\n";
            depth = 5;
        }
    } else {
        std::cout << "Usage: ./Triangle <size> <depth>\n";
        std::cout << "Example: ./Triangle 400 5\n";
        std::cout << "Using default values: size = " << requestedSize << ", depth = " << depth << "\n";
    }

    // Define base window size
    const int BASE_WINDOW_WIDTH = 800;
    const int BASE_WINDOW_HEIGHT = 600;
    const int MAX_WINDOW_SIZE = 1200;

    // Calculate the height of the triangle based on requested size
    float requestedHeight = requestedSize * std::sqrt(3.0f) / 2.0f;

    // Determine window size dynamically
    int windowWidth = std::max(static_cast<int>(requestedSize * 1.2f), BASE_WINDOW_WIDTH);
    int windowHeight = std::max(static_cast<int>(requestedHeight * 1.2f), BASE_WINDOW_HEIGHT);

    // Cap window size to avoid extreme values
    windowWidth = std::min(windowWidth, MAX_WINDOW_SIZE);
    windowHeight = std::min(windowHeight, MAX_WINDOW_SIZE);

    // Determine the maximum size that fits within the window
    float maxTriangleWidth = windowWidth * 0.8f;  // 80% of window width
    float maxTriangleHeight = windowHeight * 0.8f; // 80% of window height

    // Determine the scaling factor
    float scaleFactor = std::min(maxTriangleWidth / requestedSize, maxTriangleHeight / requestedHeight);

    // Apply the scaling factor to ensure it fits
    float adjustedSize = requestedSize * scaleFactor;

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Triangle Fractal");

    // Center the fractal properly in the new window
    float centerX = windowWidth / 2.0f;
    float baseY = windowHeight * 0.75f;  // Position the base near the bottom

    // Create the fractal with the adjusted size
    Triangle fractal(centerX, baseY, adjustedSize, depth);

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
