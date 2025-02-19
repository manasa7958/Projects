// Copyright 2025 Manasa Praveen and Ponita Ty
#include "triangle.hpp"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
  float L = 300.0f;  // size
  int N = 3;         // depth
  if (argc == 3) {
    L = std::atof(argv[1]);
    N = std::atoi(argv[2]);
    if (L <= 0) {
      std::cerr << "Error, using default size.\n";
      L = 200.0f;
    }
    if (N < 0) {
      std::cerr << "Error, using default depth.\n";
      N = 5;
    }
  }
  unsigned int windowWidth = 900;
  unsigned int windowHeight = 900;

  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                          "Triangle Fractal");

  float triangleHeight = L * std::sqrt(3.0f) / 2.0f;
  float scaleForWidth = windowWidth / (L * 2.0f);
  float scaleForHeight = windowHeight / (triangleHeight * 2.0f);
  float scale = std::min(scaleForWidth, scaleForHeight);
  float adjustedSize = L * scale * 0.4f;
  float xPos = windowWidth / 2.0f;
  float yPos = windowHeight / 2.0f;

  Triangle fractal(xPos, yPos, adjustedSize, N);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    window.clear(sf::Color::White);
    window.draw(fractal);
    window.display();
  }
  return 0;
}
