// Universe.cpp - Final Fixed Version
#include "Universe.hpp"
#include <iostream>
#include <cmath>

namespace NB {

Universe::Universe() : universeBoundary_(0.0), bgTexture_(std::make_shared<sf::Texture>()),
bgSprite_(std::make_shared<sf::Sprite>()) {}

size_t Universe::size() const {
    return spaceObjects_.size();
}

double Universe::radius() const {
    return universeBoundary_;
}

const CelestialBody& Universe::operator[](size_t i) const {
    return spaceObjects_[i];
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    sf::Vector2u windowSize = window.getSize();

    if (bgTexture_->getSize().x > 0) {
        float scaleX = static_cast<float>(windowSize.x) / bgTexture_->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / bgTexture_->getSize().y;
        bgSprite_->setScale(scaleX, scaleY);
        window.draw(*bgSprite_, states);
    }

    if (universeBoundary_ <= 0.0) return;

    float scale = std::min(windowSize.x, windowSize.y) / (2.0f * static_cast<float>(universeBoundary_));
    scale *= 0.5f;

    for (const auto& body : spaceObjects_) {
        float screenX = (body.position().x * scale) + (windowSize.x / 2.0f);
        float screenY = (windowSize.y / 2.0f) - (body.position().y * scale);

        sf::Sprite* sprite = const_cast<sf::Sprite*>(body.sprite_.get());
        if (sprite && sprite->getTexture()) {
            sprite->setPosition(screenX, screenY);
            sprite->setScale(0.5f, 0.5f);
            window.draw(*sprite, states);
        }
    }
}

void Universe::step(double timeStep) {
    const double GRAV_CONST = 6.67e-11;
    size_t bodyCount = spaceObjects_.size();
    if (bodyCount == 0) return;

    std::vector<double> forceX(bodyCount, 0.0);
    std::vector<double> forceY(bodyCount, 0.0);

    for (size_t i = 0; i < bodyCount; i++) {
        for (size_t j = i + 1; j < bodyCount; j++) {
            double deltaX = spaceObjects_[j].position().x - spaceObjects_[i].position().x;
            double deltaY = spaceObjects_[j].position().y - spaceObjects_[i].position().y;
            double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
            if (distance < 1e-10) distance = 1e-10;
            double force = GRAV_CONST * spaceObjects_[i].mass() * spaceObjects_[j].mass() / (distance * distance);
            double forceXComponent = force * deltaX / distance;
            double forceYComponent = force * deltaY / distance;
            forceX[i] += forceXComponent;
            forceY[i] += forceYComponent;
            forceX[j] -= forceXComponent;
            forceY[j] -= forceYComponent;
        }
    }

    for (size_t i = 0; i < bodyCount; i++) {
        double accelerationX = forceX[i] / spaceObjects_[i].mass();
        double accelerationY = forceY[i] / spaceObjects_[i].mass();
        double velocityX = spaceObjects_[i].velocity().x + accelerationX * timeStep;
        double velocityY = spaceObjects_[i].velocity().y + accelerationY * timeStep;
        double positionX = spaceObjects_[i].position().x + velocityX * timeStep;
        double positionY = spaceObjects_[i].position().y + velocityY * timeStep;
        
        spaceObjects_[i].setPosition(positionX, positionY);
        spaceObjects_[i].setVelocity(velocityX, velocityY);
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
