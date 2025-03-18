// Copyright 2025 Manasa Praveen
#include <iostream>
#include <cmath>
#include "Universe.hpp"

namespace NB {

Universe::Universe() : universeRadius(0), 
    backgroundTexture(std::make_shared<sf::Texture>()),
    backgroundSprite(std::make_shared<sf::Sprite>()) {

    if (!backgroundTexture->loadFromFile("background.jpg")) {
        std::cerr << "Failed to load background image" << std::endl;
    } else {
        backgroundSprite->setTexture(*backgroundTexture);
        sf::Vector2u textureSize = backgroundTexture->getSize();
        sf::Vector2u windowSize(800, 800);
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
        backgroundSprite->setScale(scaleX, scaleY);
    }
}

std::istream& operator>>(std::istream& in, Universe& universe) {
    size_t n;
    double radius;
    in >> n >> radius;
    universe.setRadius(radius);
    universe.clearBodies();

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
        out << universe[i] << "\n";  // Uses overloaded operator<< for CelestialBody
    }
    return out;
}

const CelestialBody& Universe::operator[](size_t i) const {
    if (i >= bodies.size()) {
        throw std::out_of_range("Index out of range");
    }
    return *bodies[i];  // Dereferencing shared_ptr
}

void Universe::step(double dt) {
    const double G = 6.67430e-11;

    size_t numBodies = bodies.size();
    std::vector<double> forceX(numBodies, 0.0);
    std::vector<double> forceY(numBodies, 0.0);

    // Compute forces
    for (size_t i = 0; i < numBodies; i++) {
        for (size_t j = 0; j < numBodies; j++) {
            if (i != j) {
                double dx = bodies[j]->position().x - bodies[i]->position().x;
                double dy = bodies[j]->position().y - bodies[i]->position().y;
                double dist = sqrt(dx * dx + dy * dy);

                if (dist < 1e-10) continue;

                double force = (G * bodies[i]->mass() * bodies[j]->mass()) / (dist * dist);
                forceX[i] += force * (dx / dist);
                forceY[i] += force * (dy / dist);
            }
        }
    }

    // Update positions and velocities
    for (size_t i = 0; i < numBodies; i++) {
        auto body = bodies[i];

        double ax = forceX[i] / body->mass();
        double ay = forceY[i] / body->mass();

        sf::Vector2f vel = body->velocity();
        sf::Vector2f pos = body->position();

        vel.x += dt * ax;
        vel.y += dt * ay;

        pos.x += dt * vel.x;
        pos.y += dt * vel.y;

        body->setVelocity(vel.x, vel.y);
        body->setPosition(pos.x, pos.y);
    }
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(*backgroundSprite); // ✅ Now using shared_ptr

    for (const auto& body : bodies) {
        sf::Vector2f pos = body->position();

        // ✅ Fixing screen coordinate transformation
        float screenX = (pos.x / universeRadius) * 400 + 400;
        float screenY = (pos.y / universeRadius) * 400 + 400;

        if (body->sprite) {  // ✅ No need for const_cast
            body->sprite->setPosition(screenX, screenY);
            window.draw(*body->sprite, states);
        }
    }
}

}  // namespace NB
