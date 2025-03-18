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
    const double MAX_FORCE = 1.0e30;  // Prevents unrealistic forces
    const double MAX_ACCEL = 1.0e20;  // Prevents unrealistic acceleration

    size_t numBodies = bodies.size();
    if (numBodies == 0) return;

    std::vector<double> forceX(numBodies, 0.0);
    std::vector<double> forceY(numBodies, 0.0);

    // Compute gravitational forces
    for (size_t i = 0; i < numBodies; i++) {
        for (size_t j = i + 1; j < numBodies; j++) {  // ✅ Avoids duplicate calculations
            double dx = bodies[j]->position().x - bodies[i]->position().x;
            double dy = bodies[j]->position().y - bodies[i]->position().y;
            double r = std::sqrt(dx * dx + dy * dy);

            if (r < 1e-10) r = 1e-10;  // ✅ Prevents division by zero

            double force = (G * bodies[i]->mass() * bodies[j]->mass()) / (r * r);
            if (force > MAX_FORCE) force = MAX_FORCE;  // ✅ Limits extreme forces

            double fx = force * dx / r;
            double fy = force * dy / r;

            forceX[i] += fx;
            forceY[i] += fy;
            forceX[j] -= fx;  // ✅ Newton's Third Law
            forceY[j] -= fy;
        }
    }

    // Apply acceleration, update velocity and position
    for (size_t i = 0; i < numBodies; i++) {
        double ax = forceX[i] / bodies[i]->mass();
        double ay = forceY[i] / bodies[i]->mass();

        if (std::abs(ax) > MAX_ACCEL) ax = ax > 0 ? MAX_ACCEL : -MAX_ACCEL;
        if (std::abs(ay) > MAX_ACCEL) ay = ay > 0 ? MAX_ACCEL : -MAX_ACCEL;

        double vx = bodies[i]->velocity().x;
        double vy = bodies[i]->velocity().y;

        double new_vx = vx + ax * dt;  // ✅ v = v0 + a * t
        double new_vy = vy + ay * dt;

        double px = bodies[i]->position().x;
        double py = bodies[i]->position().y;

        double new_px = px + new_vx * dt;  // ✅ p = p0 + v * t
        double new_py = py + new_vy * dt;

        bodies[i]->setPosition(new_px, new_py);
        bodies[i]->setVelocity(new_vx, new_vy);
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
