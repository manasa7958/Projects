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
    
    std::vector<double> forceX(numBodies, 0.0);
    std::vector<double> forceY(numBodies, 0.0);

    // Compute net forces
    for (size_t i = 0; i < numBodies; i++) {
        for (size_t j = 0; j < numBodies; j++) {
            if (i != j) {
                auto bodyA = bodies[i];
                auto bodyB = bodies[j];

                double dx = bodyB->position().x - bodyA->position().x;
                double dy = bodyB->position().y - bodyA->position().y;
                double dist = sqrt(dx * dx + dy * dy);

                if (dist == 0) continue;

                double force = (6.67430e-11 * bodyA->mass() * bodyB->mass()) / (dist * dist);
                forceX[i] += force * (dx / dist);
                forceY[i] += force * (dy / dist);
            }
        }
    }

    // Update velocities and positions using Leapfrog Integration
    for (size_t i = 0; i < numBodies; i++) {
        auto body = bodies[i];

        double ax = forceX[i] / body->mass();
        double ay = forceY[i] / body->mass();

        sf::Vector2f vel = body->velocity();
        sf::Vector2f pos = body->position();

        // 🔥 Leapfrog Integration: Half-step velocity update
        vel.x += 0.5 * dt * ax;
        vel.y += 0.5 * dt * ay;

        // 🔥 Update position
        pos.x += dt * vel.x;
        pos.y += dt * vel.y;

        // 🔥 Second half-step velocity update
        vel.x += 0.5 * dt * ax;
        vel.y += 0.5 * dt * ay;

        body->setVelocity(vel.x, vel.y);
        body->setPosition(pos.x, pos.y);

        std::cout << "Body " << i << " Position: (" << pos.x << ", " << pos.y << ")"
                  << " Velocity: (" << vel.x << ", " << vel.y << ")" << std::endl;
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

    for (const auto& body : bodies) {
        sf::Vector2f pos = body->position();
        
        // 🔥 Convert physics coordinates to screen coordinates
        float screenX = (pos.x / universeRadius) * 400 + 400;
        float screenY = (pos.y / universeRadius) * 400 + 400;

        // 🔥 Directly update sprite position
        const_cast<sf::Sprite&>(body->getSprite()).setPosition(screenX, screenY);
        
        window.draw(body->getSprite(), states);
    }
}



}  // namespace NB
