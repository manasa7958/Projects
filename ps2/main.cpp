// Copyright 2025 Manasa Praveen
#include <iostream>
#include <SFML/Graphics.hpp>
#include "triangle.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <L> <N>\n";
        return 1;
    }
    
    double length = std::stod(argv[1]);
    int depth = std::stoi(argv[2]);
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle Fractal");
    Triangle fractalTriangle(length, depth);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        window.draw(fractalTriangle);
        window.display();
    }
    
    return 0;
}

