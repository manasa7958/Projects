// Copyright 2025 Manasa Praveen
/*#include <iostream>
#include <SFML/Graphics.hpp>
#include "triangle.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Need to enter " << argv[0] << " lenght depth\n";
        return -1;
    }
    double length = std::stod(argv[1]);
    int depth = std::stoi(argv[2]);
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle Fractal");
    float rotation = 0.0f;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        rotation = rotation + 0.5f;
        Triangle fractalTriangle(length, depth, rotation);
        
        window.clear();
        window.draw(fractalTriangle);
        window.display();
    }
    return 0;
}*/

// main.cpp
#include <SFML/Graphics.hpp>
#include "triangle.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./Triangle <size> <depth>\n";
        return 1;
    }
    float size = std::stof(argv[1]);
    int depth = std::stoi(argv[2]);

    sf::RenderWindow window(sf::VideoMode(800, 800), "Triangle Fractal");
    Triangle fractal(400, 600, size, depth);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(fractal);
        window.display();
    }
    return 0;
}

