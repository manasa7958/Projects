/*// Copyright 2025 Manasa Praveen
#include <iostream>

#include "CelestialBody.hpp"
#include "Universe.hpp"
#include <SFML/Graphics.hpp>

int main() {
  NB::Universe universe;
  std::cin >> universe;
  std::cout << "Finished reading planets.txt" << std::endl;
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
}*/

// Copyright 2025 Manasa Praveen
#include <iostream>
#include "CelestialBody.hpp"
#include "Universe.hpp"
#include <SFML/Graphics.hpp>

int main() {
  NB::Universe universe;

  // DEBUG: Confirm input is being read
  std::cout << "Reading planets.txt..." << std::endl;
  std::cin >> universe;
  std::cout << "Finished reading planets.txt" << std::endl;

  // DEBUG: Check how many celestial bodies were loaded
  std::cout << "Number of celestial bodies: " << universe.getSize() << std::endl;

  sf::RenderWindow window(sf::VideoMode(800, 800), "Simulation");

  // DEBUG: Test SFML by drawing a green circle
  sf::CircleShape testShape(50);
  testShape.setFillColor(sf::Color::Green);
  testShape.setPosition(375, 375);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();

    // DEBUG: Draw test shape to see if SFML is working
    window.draw(testShape);

    // Draw the universe (assuming operator<< is correctly defined)
    window.draw(universe);

    window.display();
  }

  return 0;
}
