// Copyright 2025 Manasa Praveen
#include <iostream>
#include <memory>
#include <cmath>
#include "Universe.hpp"

namespace NB {

const double G = 6.67430e-11; // Gravitational constant

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

std::istream& operator>>(std::istream& in, Universe& universe) {
    size_t n;
    double radius;
    in >> n >> radius;
    universe.setRadius(radius);
    universe.clearBodies();

    if (n == 0) return in;
    for (size_t i = 0; i < n; ++i) {
        auto body = std::make_shared<CelestialBody>();
        in >> *body;
        if (!body->loadTexture(radius)) {
          std::cerr << "Failed to load texture" << std::endl;
        }
        universe.addBody(body);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Universe& universe) {
  out << universe.size() << " " << universe.radius() << "\n";
  for (size_t i = 0; i < universe.size(); ++i) {
    out << universe[i];
  }
  return out;
}

void Universe::step(double dt) {
    size_t numBodies = bodies.size();
    
    // Vectors to store net forces acting on each body
    std::vector<double> forceX(numBodies, 0.0);
    std::vector<double> forceY(numBodies, 0.0);

    // Compute net forces for each body
    for (size_t i = 0; i < numBodies; i++) {
        for (size_t j = 0; j < numBodies; j++) {
            if (i != j) {
                double dx = bodies[j]->position().x - bodies[i]->position().x;
                double dy = bodies[j]->position().y - bodies[i]->position().y;
                double dist = sqrt(dx * dx + dy * dy);

                if (dist == 0) continue; // Prevent division by zero

                double force = (G * bodies[i]->mass() * bodies[j]->mass()) / (dist * dist);
                forceX[i] += force * (dx / dist);
                forceY[i] += force * (dy / dist);
            }
        }
    }

    // Update velocities and positions using Leapfrog Integration
    for (size_t i = 0; i < numBodies; i++) {
        double ax = forceX[i] / bodies[i]->mass();
        double ay = forceY[i] / bodies[i]->mass();

        // Leapfrog Step:
        bodies[i]->vel.x += 0.5 * dt * ax;  // Half-step velocity update
        bodies[i]->vel.y += 0.5 * dt * ay;

        bodies[i]->pos.x += dt * bodies[i]->vel.x;  // Update position
        bodies[i]->pos.y += dt * bodies[i]->vel.y;

        bodies[i]->vel.x += 0.5 * dt * ax;  // Second half-step velocity update
        bodies[i]->vel.y += 0.5 * dt * ay;
    }
}

size_t Universe::size() const {
  return bodies.size();
}

double Universe::radius() const {
  return universeRadius;
}

const CelestialBody& Universe::operator[](size_t index) const {
  if (index >= bodies.size()) {
    throw std::out_of_range("Index out of range");
  }
  return *bodies[index];
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(backgroundSprite);
    if (bodies.empty()) {
        std::cerr << "No celestial bodies found!" << std::endl;
    }
    for (const auto& body : bodies) {
        window.draw(*body, states);
    }
}

}  // namespace NB
