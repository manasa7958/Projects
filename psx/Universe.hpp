// Copyright 2025 Manasa Praveen
#include <iostream>
#include <memory>
#include <cmath>
#include "Universe.hpp"

namespace NB {

Universe::Universe() : universeRadius(0) {
    if (!backgroundTexture->loadFromFile("background.jpg")) {
        std::cerr << "Failed to load background image" << std::endl;
    } else {
        backgroundSprite->setTexture(backgroundTexture);
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
    if (!(in >> n >> radius)) {
        throw std::runtime_error("Invalid universe format");
    }

    universe.universeRadius = radius;
    universe.bodies.clear();

    for (size_t i = 0; i < n; ++i) {
        auto body = std::make_shared<CelestialBody>();
        if (in >> *body) {
            universe.bodies.push_back(body);
        } else {
            throw std::runtime_error("Failed to read celestial body " + std::to_string(i));
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Universe& universe) {
    out << universe.size() << " " << universe.universeRadius << "\n";
    for (const auto& body : universe.bodies) {
        out << *body << "\n";
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

void Universe::step(double dt) {
    const double G = 6.67430e-11;
    const double MAX_FORCE = 1.0e30;
    const double MAX_ACCEL = 1.0e20;

    size_t n = bodies.size();
    if (n == 0) return;

    std::vector<double> forceX(n, 0.0);
    std::vector<double> forceY(n, 0.0);

    // Compute gravitational forces
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {  
            double dx = bodies[j]->position().x - bodies[i]->position().x;
            double dy = bodies[j]->position().y - bodies[i]->position().y;
            double r = std::sqrt(dx * dx + dy * dy);

            if (r < 1e-10) r = 1e-10;

            double force = G * bodies[i]->mass() * bodies[j]->mass() / (r * r);
            if (force > MAX_FORCE) force = MAX_FORCE;

            double fx = force * dx / r;
            double fy = force * dy / r;

            forceX[i] += fx;
            forceY[i] += fy;
            forceX[j] -= fx;
            forceY[j] -= fy;
        }
    }

    // Apply forces and update positions
    for (size_t i = 0; i < n; i++) {
        double ax = forceX[i] / bodies[i]->mass();
        double ay = forceY[i] / bodies[i]->mass();

        if (std::abs(ax) > MAX_ACCEL) ax = ax > 0 ? MAX_ACCEL : -MAX_ACCEL;
        if (std::abs(ay) > MAX_ACCEL) ay = ay > 0 ? MAX_ACCEL : -MAX_ACCEL;

        double vx = bodies[i]->velocity().x;
        double vy = bodies[i]->velocity().y;

        double new_vx = vx + ax * dt;
        double new_vy = vy + ay * dt;

        double px = bodies[i]->position().x;
        double py = bodies[i]->position().y;

        double new_px = px + new_vx * dt;
        double new_py = py + new_vy * dt;

        bodies[i]->setPosition(new_px, new_py);
        bodies[i]->setVelocity(new_vx, new_vy);
    }
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    sf::Vector2u windowSize = window.getSize();

    // ✅ Ensure background is drawn properly (NO CHANGES TO HOW YOU LOAD IT)
    if (backgroundTexture.getSize().x > 0) {
        window.draw(backgroundSprite);
    } else {
        std::cerr << "❌ ERROR: Background texture is not set properly. Check file path." << std::endl;
    }

    if (bodies.empty()) {
        std::cerr << "⚠️ WARNING: No celestial bodies found!\n";
    }

    float scale = std::min(windowSize.x, windowSize.y) / (2.0f * static_cast<float>(universeRadius));
    scale *= 0.5f;

    for (const auto& body : bodies) {
        float screenX = (body->position().x * scale) + (windowSize.x / 2.0f);
        float screenY = (windowSize.y / 2.0f) - (body->position().y * scale);

        if (body->sprite) {
            body->sprite->setPosition(screenX, screenY);
            body->sprite->setScale(0.5f, 0.5f);
            window.draw(*body, states);
        }
    }
}

}  // namespace NB
