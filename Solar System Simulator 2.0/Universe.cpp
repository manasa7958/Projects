// Copyright 2025 Manasa Praveen
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "Universe.hpp"

namespace NB {
Universe::Universe() : universeBoundary_(0.0),
bgTexture_(std::make_shared<sf::Texture>()),
bgSprite_(std::make_shared<sf::Sprite>()),
antiGravityMode_(false) {}

size_t Universe::size() const {
    return spaceObjects_.size();
}

double Universe::radius() const {
    return universeBoundary_;
}

const CelestialBody& Universe::operator[](size_t i) const {
    return spaceObjects_[i];
}

void Universe::enableAntiGravity(bool mode) {
    std::cout << "enableAntiGravity called! Mode: " << mode << std::endl;
    antiGravityMode_ = mode;
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    sf::Vector2u windowSize = window.getSize();

    if (bgTexture_->getSize().x > 0) {
        float scaleX = static_cast<float>(windowSize.x)
        / bgTexture_->getSize().x;
        float scaleY = static_cast<float>(windowSize.y)
        / bgTexture_->getSize().y;
        bgSprite_->setScale(scaleX, scaleY);
        window.draw(*bgSprite_, states);
    }

    if (universeBoundary_ <= 0.0) return;

    float scale = std::min(windowSize.x, windowSize.y)
    / (2.0f * static_cast<float>(universeBoundary_));
    scale *= 0.8f;

    for (const auto& body : spaceObjects_) {
        float screenX = (body.position().x * scale) + (windowSize.x / 2.0f);
        float screenY = (windowSize.y / 2.0f) - (body.position().y * scale);

        sf::Sprite sprite;
        if (body.getSprite(sprite)) {
            sprite.setPosition(screenX, screenY);
            sprite.setScale(1.5f, 1.5f);
            window.draw(sprite, states);
        }
    }
}

void Universe::step(double timeStep) {
    const double GRAV_CONST = 6.67e-11;
    size_t bodyCount = spaceObjects_.size();
    if (bodyCount == 0) return;
    std::vector<sf::Vector2f> forces(bodyCount, sf::Vector2f(0.0f, 0.0f));
    for (size_t i = 0; i < bodyCount; i++) {
        for (size_t j = i + 1; j < bodyCount; j++) {
            sf::Vector2f delta = spaceObjects_[j].position() - spaceObjects_[i].position();
            float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            if (distance < 1e-10) distance = 1e-10;

            float forceMagnitude = GRAV_CONST * spaceObjects_[i].mass()
            * spaceObjects_[j].mass() / (distance * distance);
            sf::Vector2f force = forceMagnitude * (delta / distance);

            if (antiGravityMode_) {
                force = -force;
            }
            forces[i] += force;
            forces[j] -= force;
        }
    }
    for (size_t i = 0; i < bodyCount; i++) {
        if (spaceObjects_[i].mass() == 0) continue;

        sf::Vector2f acceleration = forces[i] / spaceObjects_[i].mass();
        sf::Vector2f halfVelocity = spaceObjects_[i].velocity()
        + (0.5f * acceleration * static_cast<float>(timeStep));
        sf::Vector2f newPosition = spaceObjects_[i].position()
        + halfVelocity * static_cast<float>(timeStep);

        spaceObjects_[i].setPosition(newPosition);
    }
    std::vector<sf::Vector2f> newForces(bodyCount, sf::Vector2f(0.0f, 0.0f));
    for (size_t i = 0; i < bodyCount; i++) {
        for (size_t j = i + 1; j < bodyCount; j++) {
            sf::Vector2f delta = spaceObjects_[j].position() - spaceObjects_[i].position();
            float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            if (distance < 1e-10) distance = 1e-10;

            float forceMagnitude = GRAV_CONST * spaceObjects_[i].mass()
            * spaceObjects_[j].mass() / (distance * distance);
            sf::Vector2f force = forceMagnitude * (delta / distance);

            if (antiGravityMode_) {
                force = -force;
            }
            newForces[i] += force;
            newForces[j] -= force;
        }
    }
    for (size_t i = 0; i < bodyCount; i++) {
        if (spaceObjects_[i].mass() == 0) continue;

        sf::Vector2f newAcceleration = newForces[i] / spaceObjects_[i].mass();
        sf::Vector2f newVelocity = spaceObjects_[i].velocity()
        + (newAcceleration * static_cast<float>(timeStep));
        spaceObjects_[i].setVelocity(newVelocity);
    }
}

std::istream& operator>>(std::istream& is, Universe& universe) {
    int totalBodies;
    double size;
    is >> totalBodies >> size;
    universe.universeBoundary_ = size;
    universe.spaceObjects_.clear();

    for (int i = 0; i < totalBodies; ++i) {
        CelestialBody body;
        is >> body;
        universe.spaceObjects_.push_back(body);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& universe) {
    os << universe.size() << " " << universe.radius() << "\n";
    for (const auto& body : universe.spaceObjects_) {
        os << body << "\n";
    }
    return os;
}
}  // namespace NB
