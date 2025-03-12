// Copyright 2025 Manasa Praveen
#include <iostream>
#include <memory>
#include <cmath>
#include "Universe.hpp"

namespace NB {

const double G = 6.67430e-11;  // Gravitational constant

Universe::Universe() : universeRadius(0) {
    if (!backgroundTexture.loadFromFile("background.jpg")) {
        std::cerr << "Failed to load background image" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
        sf::Vector2u textureSize = backgroundTexture.getSize();
        sf::Vector2u windowSize(800, 800);
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
    }
}

void Universe::step(double dt) {
  size_t n = bodies.size();
  std::vector<Vector2D> forces(n, Vector2D(0, 0));

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (i != j) {
        Vector2D delta = bodies[j]->position() - bodies[i]->position();
        double distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        double forceMagnitude = (G * bodies[i]->mass() * bodies[j]->mass()) / (distance * distance);
        Vector2D force(forceMagnitude * delta.x / distance, forceMagnitude * delta.y / distance);
        forces[i] = forces[i] + force;
      }
    }
  }

  for (size_t i = 0; i < n; ++i) {
    bodies[i]->updateVelocity(forces[i], dt);
  }

  for (size_t i = 0; i < n; ++i) {
    bodies[i]->updatePosition(dt);
  }
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(backgroundSprite);
    for (const auto& body : bodies) {
        window.draw(*body, states);
    }
}

}  // namespace NB
