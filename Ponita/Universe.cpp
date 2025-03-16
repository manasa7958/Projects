// Copyright 2025 Ponita Ty
#include "Universe.hpp"
#include <iostream>

namespace NB {

Universe::Universe() : radius_(0.0), backgroundTexture_(std::make_shared<sf::Texture>()),
backgroundSprite_(std::make_shared<sf::Sprite>()) {
}

bool Universe::initBackground(const std::string& filename) {
    if (backgroundTexture_->loadFromFile(filename)) {
        backgroundSprite_->setTexture(*backgroundTexture_);

        return true;
    }
    return false;
}

size_t Universe::size() const {
    return bodies_.size();
}

double Universe::radius() const {
    return radius_;
}

const CelestialBody& Universe::operator[](size_t i) const {
    return bodies_[i];
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2u windowSize = target.getSize();
    if (backgroundSprite_ && backgroundTexture_) {
        float scaleX = static_cast<float>(windowSize.x) / backgroundTexture_->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / backgroundTexture_->getSize().y;
        backgroundSprite_->setScale(scaleX, scaleY);
        target.draw(*backgroundSprite_, states);
    }

    float scale = std::min(windowSize.x, windowSize.y) / (2.0f * static_cast<float>(radius_));
    scale *= 0.5f;

    for (const auto& body : bodies_) {
        float screenX = (body.position().x * scale) + (windowSize.x / 2.0f);
        float screenY = (windowSize.y / 2.0f) - (body.position().y * scale);

        sf::Sprite* sprite = const_cast<sf::Sprite*>(body.sprite_.get());
        if (sprite) {
            sprite->setPosition(screenX, screenY);
            sprite->setScale(0.5f, 0.5f);
            target.draw(body, states);
        }
    }
}

std::istream& operator>>(std::istream& is, Universe& uni) {
    int n;
    double r;

    if (!(is >> n >> r)) {
        throw std::runtime_error("Invalid universe format");
    }

    if (n < 0) {
        throw std::runtime_error("Negative number of bodies");
    }

    uni.bodies_.clear();
    uni.radius_ = r;

    for (int i = 0; i < n; ++i) {
        CelestialBody body;
        if (is >> body) {
            uni.bodies_.push_back(body);
        } else {
            throw std::runtime_error("Failed to read body " + std::to_string(i));
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& uni) {
    os << uni.size() << " " << uni.radius() << "\n";
    for (size_t i = 0; i < uni.size(); ++i) {
        os << uni[i] << "\n";
    }
    return os;
}
}  // namespace NB
