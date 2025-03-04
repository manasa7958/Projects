// Copyright 2025 Manasa Praveen
#include <iostream>
#include <memory>
#include <cmath>
#include "Universe.hpp"

namespace NB {

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

void NB::Universe::step(double dt) {
    std::vector<sf::Vector2f> newVelocities(bodies.size());
    std::vector<sf::Vector2f> newPositions(bodies.size());

    float dtSign = (dt >= 0) ? 1.0f : -1.0f;
    
    for (size_t i = 0; i < bodies.size(); i++) {
        if (bodies[i]->mass() == 0) {
            newPositions[i] = bodies[i]->position();
            newVelocities[i] = bodies[i]->velocity();
            continue;
        }
        
        sf::Vector2f netForce(0.f, 0.f);
        for (size_t j = 0; j < bodies.size(); j++) {
            if (i == j || bodies[j]->mass() == 0) continue;
            
            sf::Vector2f diff = bodies[j]->position() - bodies[i]->position();
            float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
            
            if (distance < 1e-6) continue;

            float forceMagnitude = (6.67430e-11 * bodies[i]->mass() * bodies[j]->mass()) / (distance * distance);
            sf::Vector2f force = (diff / distance) * forceMagnitude * dtSign;
            netForce += force;
        }

        sf::Vector2f acceleration = netForce / bodies[i]->mass();
        sf::Vector2f halfStepVelocity = bodies[i]->velocity() + (acceleration * static_cast<float>(dt * 0.5));
        newPositions[i] = bodies[i]->position() + (halfStepVelocity * static_cast<float>(dt));
        newVelocities[i] = halfStepVelocity + (acceleration * static_cast<float>(dt * 0.5));
    }

    for (size_t i = 0; i < bodies.size(); i++) {
        bodies[i]->setVelocity(newVelocities[i]);
        bodies[i]->setPosition(newPositions[i]);
    }
}


void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(backgroundSprite);
    if (bodies.empty()) {
        std::cerr << "No celestial bodies found!";
    }
    for (const auto& body : bodies) {
        window.draw(*body, states);
    }
}

}  // namespace NB
