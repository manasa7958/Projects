// Copyright 2025 Manasa Praveen
#include <iostream>
#include <SFML/Graphics.hpp>
#include "triangle.hpp"

int main() {
    int depth;
    std::cout << "Enter the fractal depth (recommended 1-7 for performance): ";
    std::cin >> depth;
    
    if (depth < 0) {
        std::cout << "Invalid depth! Using default depth of 5.\n";
        depth = 5;
    }

    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle Fractal");
    
    // Create fractal with user-specified depth
    Triangle fractal(400.0f, 400.0f, 200.0f, depth);
    
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
