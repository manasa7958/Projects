// Copyright 2025 Manasa Praveen
#include <iostream>

#include "CelestialBody.hpp"
#include "Universe.hpp"
#include <SFML/Graphics.hpp>

int main() {
  NB::Universe universe;
  std::cin >> universe;
  sf::RenderWindow window(sf::VideoMode(800, 800), "Simulation");
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    window.draw(universe);
    window.display();
  }
  return 0;
}
