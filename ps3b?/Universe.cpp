// Universe.cpp - Customized Version
#include "Universe.hpp"
#include <iostream>
#include <cmath>

namespace NB {

Universe::Universe() : cosmosSize_(0.0), backgroundTexture_(std::make_shared<sf::Texture>()),
backgroundSprite_(std::make_shared<sf::Sprite>()) {}

size_t Universe::size() const {
    return celestialBodies_.size();
}

double Universe::radius() const {
    return cosmosSize_;
}

const CelestialBody& Universe::operator[](size_t i) const {
    return celestialBodies_[i];
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    if (backgroundSprite_) {
        window.draw(*backgroundSprite_, states);
    }
    for (const auto& body : celestialBodies_) {
        window.draw(body, states);
    }
}

void Universe::step(double timeInterval) {
    const double GRAV_CONST = 6.67e-11;
    size_t bodyCount = celestialBodies_.size();
    if (bodyCount == 0) return;

    std::vector<double> forceX(bodyCount, 0.0);
    std::vector<double> forceY(bodyCount, 0.0);

    for (size_t i = 0; i < bodyCount; i++) {
        for (size_t j = i + 1; j < bodyCount; j++) {
            double deltaX = celestialBodies_[j].position().x - celestialBodies_[i].position().x;
            double deltaY = celestialBodies_[j].position().y - celestialBodies_[i].position().y;
            double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
            if (distance < 1e-10) distance = 1e-10;
            double force = GRAV_CONST * celestialBodies_[i].mass() * celestialBodies_[j].mass() / (distance * distance);
            double forceXComponent = force * deltaX / distance;
            double forceYComponent = force * deltaY / distance;
            forceX[i] += forceXComponent;
            forceY[i] += forceYComponent;
            forceX[j] -= forceXComponent;
            forceY[j] -= forceYComponent;
        }
    }

    for (size_t i = 0; i < bodyCount; i++) {
        double accelerationX = forceX[i] / celestialBodies_[i].mass();
        double accelerationY = forceY[i] / celestialBodies_[i].mass();
        double velocityX = celestialBodies_[i].velocity().x + accelerationX * timeInterval;
        double velocityY = celestialBodies_[i].velocity().y + accelerationY * timeInterval;
        double positionX = celestialBodies_[i].position().x + velocityX * timeInterval;
        double positionY = celestialBodies_[i].position().y + velocityY * timeInterval;
        
        celestialBodies_[i].setPosition(positionX, positionY);
        celestialBodies_[i].setVelocity(velocityX, velocityY);
    }
}
}  // namespace NB
