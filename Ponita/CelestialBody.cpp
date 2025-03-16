// Copyright 2025 Ponita Ty
#include "CelestialBody.hpp"

namespace NB {

CelestialBody::CelestialBody() {
    xPos_ = 0.0;
    yPos_ = 0.0;
    xVel_ = 0.0;
    yVel_ = 0.0;
    mass_ = 0.0;
    texture_ = std::make_shared<sf::Texture>();
    sprite_ = std::make_shared<sf::Sprite>();
}

sf::Vector2f CelestialBody::position() const {
    return sf::Vector2f(static_cast<float>(xPos_), static_cast<float>(yPos_));
}

sf::Vector2f CelestialBody::velocity() const {
    return sf::Vector2f(static_cast<float>(xVel_), static_cast<float>(yVel_));
}

float CelestialBody::mass() const {
    float result = static_cast<float>(mass_);
    const float maxValue = 1e35f;
    if (result < -maxValue) result = -maxValue;
    if (result > maxValue) result = maxValue;
    return result;
}

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (sprite_ && texture_) {
        target.draw(*sprite_, states);
    } else {
        std::cerr << "Warning: Sprite or texture is null" << std::endl;
    }
}

std::istream& operator>>(std::istream& is, CelestialBody& body) {
    double x, y, vx, vy, m;
    std::string filename;

    if (is >> x >> y >> vx >> vy >> m >> filename) {
        body.xPos_ = x;
        body.yPos_ = y;
        body.xVel_ = vx;
        body.yVel_ = vy;
        body.mass_ = m;

        std::cerr << "Loading texture from file: " << filename << std::endl;
        if (body.texture_->loadFromFile(filename)) {
            body.sprite_->setTexture(*body.texture_);

            sf::Vector2u size = body.texture_->getSize();
            body.sprite_->setOrigin(size.x / 2.0f, size.y / 2.0f);

            std::cerr << "Successfully loaded texture: " << filename << std::endl;
        } else {
            std::cerr << "Failed to load texture: " << filename << std::endl;
        }
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
    os << body.position().x << " " << body.position().y << " "
       << body.velocity().x << " " << body.velocity().y << " "
       << body.mass() << " body.gif";
    return os;
}
}  // namespace NB
