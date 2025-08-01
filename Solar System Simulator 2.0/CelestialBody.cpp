// Copyright 2025 Manasa Praveen
#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include "CelestialBody.hpp"

namespace NB {
CelestialBody::CelestialBody() : pos_(0.0f, 0.0f), vel_(0.0f, 0.0f), m_(0.0f) {
    textureFile_ = "default.gif";
    texture_ = std::make_shared<sf::Texture>();
    sprite_ = std::make_shared<sf::Sprite>();
}

bool CelestialBody::getSprite(sf::Sprite& outSprite) const {
    if (sprite_ && texture_) {
        outSprite = *sprite_;
        return true;
    }
    return false;
}

sf::Vector2f CelestialBody::position() const {
    return pos_;
}

sf::Vector2f CelestialBody::velocity() const {
    return vel_;
}

float CelestialBody::mass() const {
    return (m_ > 0) ? m_ : 0.0f;
}

void CelestialBody::setPosition(const sf::Vector2f& pos) {
    pos_ = pos;
}

void CelestialBody::setVelocity(const sf::Vector2f& vel) {
    vel_ = vel;
}

std::istream& operator>>(std::istream& is, CelestialBody& body) {
    float x, y, vx, vy, m;
    std::string filename;

    if (!(is >> x >> y >> vx >> vy >> m >> filename)) {
        std::cerr << "Error: Invalid CelestialBody input!" << std::endl;
        is.setstate(std::ios::failbit);
        return is;
    }
    body.pos_ = sf::Vector2f(x, y);
    body.vel_ = sf::Vector2f(vx, vy);
    body.m_ = m;

    body.textureFile_ = filename;
    if (!body.texture_->loadFromFile(filename)) {
        std::cerr << "Warning: Failed to load texture: " << filename << std::endl;
    } else {
        body.sprite_->setTexture(*body.texture_);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
    os << std::scientific << std::setprecision(4)
       << body.pos_.x << " " << body.pos_.y << " "
       << body.vel_.x << " " << body.vel_.y << " "
       << body.m_ << " " << body.textureFile_;
    return os;
}

void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states)
const {
    if (sprite_ && texture_) {
        window.draw(*sprite_, states);
    }
}
}  // namespace NB


