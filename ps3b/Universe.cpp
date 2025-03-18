// Copyright 2025 Manasa Praveen
#include <iostream>
#include <cmath>
#include "Universe.hpp"

namespace NB {

Universe::Universe() : radius_(0), 
    backgroundTexture_(std::make_shared<sf::Texture>()),
    backgroundSprite_(std::make_shared<sf::Sprite>()) {}

bool Universe::initBackground(const std::string& filename) {
    if (!backgroundTexture_->loadFromFile(filename)) {
        std::cerr << "Failed to load background image: " << filename << std::endl;
        return false;
    }
    backgroundSprite_->setTexture(*backgroundTexture_);
    sf::Vector2u textureSize = backgroundTexture_->getSize();
    sf::Vector2u windowSize(800, 800);
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite_->setScale(scaleX, scaleY);
    return true;
}

std::istream& operator>>(std::istream& in, Universe& universe) {
    size_t n;
    double radius;
    in >> n >> radius;
    universe.radius_ = radius;
    universe.bodies.clear();

    for (size_t i = 0; i < n; ++i) {
        auto body = std::make_shared<CelestialBody>();
        in >> *body;
        if (!body->loadTexture(radius)) {
            std::cerr << "Failed to load texture" << std::endl;
        }
        universe.bodies.push_back(body);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Universe& universe) {
    out << universe.bodies.size() << " " << universe.radius_ << "\n";
    for (const auto& body : universe.bodies) {
        out << *body << "\n";
    }
    return out;
}

const CelestialBody& Universe::operator[](size_t i) const {
    if (i >= bodies.size()) {
        throw std::out_of_range("Index out of range");
    }
    return *bodies[i];
}

void Universe::step(double seconds) {
    const double G = 6.67e-11;
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

        double new_vx = vx + ax * seconds;
        double new_vy = vy + ay * seconds;

        double px = bodies[i]->position().x;
        double py = bodies[i]->position().y;

        double new_px = px + new_vx * seconds;
        double new_py = py + new_vy * seconds;

        bodies[i]->setPosition(new_px, new_py);
        bodies[i]->setVelocity(new_vx, new_vy);
    }
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(*backgroundSprite_);  

    for (const auto& body : bodies) {
        sf::Vector2f pos = body->position();
        float screenX = (pos.x / radius_) * 400 + 400;
        float screenY = (pos.y / radius_) * 400 + 400;

        if (body->sprite) {  
            body->sprite->setPosition(screenX, screenY);
            window.draw(*body->sprite, states);
        }
    }
}

}  // namespace NB
