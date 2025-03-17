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
        universe.addBody(body);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Universe& universe) {
    out << universe.size() << " " << universe.radius() << "\n";
    for (size_t i = 0; i < universe.size(); ++i) {
        out << *universe.bodies[i] << "\n";  // Dereferencing shared_ptr
    }
    return out;
}

void Universe::step(double dt) {
    const double G = 6.67430e-11;

    size_t numBodies = bodies.size();
    std::vector<double> forceX(numBodies, 0.0);
    std::vector<double> forceY(numBodies, 0.0);

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
    window.draw(backgroundSprite);
    for (const auto& body : bodies) {
        window.draw(*body, states);
    }
}

}  // namespace NB
