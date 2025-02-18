// Copyright 2025 Manasa Praveen
#include <iostream>
#include <SFML/Graphics.hpp>
#include "triangle.hpp"

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Level 2 Triangle Fractal");
    
    // Create triangle at center of window
    Triangle fractal(400.0f, 400.0f, 200.0f);
    
    // Main loop
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
