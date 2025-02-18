// Copyright 2025 Manasa Praveen and Ponita Ty
#include <iostream>
#include <SFML/Graphics.hpp>
#include "triangle.hpp"
#include <cstdlib>
int main(int argc, char* argv[]){
  float size = 200.0f;
  int depth = 5;
  if (argc == 3) {
    size = std::atof(argv[1]);
    depth = std::atoi(argv[2]);
    if (size <= 0) {
      std::cerr << "Invalid size! Using default size of 200.\n";
      size = 200.0f;
    }
    if (depth < 0) {
      std::cerr << "Invalid depth! Using default depth of 5.\n";
      depth = 5;
    }
  }
  unsigned int windowWidth = 500;
  unsigned int windowHeight = 500;
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Triangle Fractal");
  float triangleHeight = size * std::sqrt(3.0f) / 2.0f;
  float scaleForWidth = windowWidth / (size * 2.0f);
  float scaleForHeight = windowHeight / (triangleHeight * 2.0f);
  float scale = std::min(scaleForWidth, scaleForHeight);
  float adjustedSize = size * scale * 0.4f;
  float xPos = windowWidth / 2.0f;
  float yPos = windowHeight / 2.0f;
  
  Triangle fractal(xPos, yPos, adjustedSize, depth);
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

