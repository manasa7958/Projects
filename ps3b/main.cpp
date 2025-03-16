// Copyright 2025 Manasa Praveen
#include <iostream>
#include "CelestialBody.hpp"
#include "Universe.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <T> <dt>" << std::endl;
    return 1;
  }

  double T = std::stod(argv[1]);
  double dt = std::stod(argv[2]);

  NB::Universe universe;
  std::cin >> universe;
  
  sf::RenderWindow window(sf::VideoMode(800, 800), "The Solar System!");
  double elapsedTime = 0.0;

  while (window.isOpen() && elapsedTime < T) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    
    universe.step(dt);
    window.clear();
    window.draw(universe);
    window.display();
    elapsedTime += dt;
  }

  std::cout << universe;
  return 0;
}
