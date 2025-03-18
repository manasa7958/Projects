// CelestialBody.cpp - Customized Version
#include "CelestialBody.hpp"
#include <iomanip>

namespace NB {

CelestialBody::CelestialBody() {
    coordX_ = 0.0;
    coordY_ = 0.0;
    speedX_ = 0.0;
    speedY_ = 0.0;
    weight_ = 0.0;
    textureFile_ = "default.gif";
    texture_ = std::make_shared<sf::Texture>();
    sprite_ = std::make_shared<sf::Sprite>();
}

sf::Vector2f CelestialBody::position() const {
    return sf::Vector2f(static_cast<float>(coordX_), static_cast<float>(coordY_));
}

sf::Vector2f CelestialBody::velocity() const {
    return sf::Vector2f(static_cast<float>(speedX_), static_cast<float>(speedY_));
}

float CelestialBody::mass() const {
    return static_cast<float>(weight_);
}

void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    if (sprite_ && texture_) {
        window.draw(*sprite_, states);
    }
}

std::istream& operator>>(std::istream& is, CelestialBody& body) {
    double x, y, vx, vy, m;
    std::string filename;
    if (is >> x >> y >> vx >> vy >> m >> filename) {
        body.coordX_ = x;
        body.coordY_ = y;
        body.speedX_ = vx;
        body.speedY_ = vy;
        body.weight_ = m;
        body.textureFile_ = filename;
        body.texture_->loadFromFile(filename);
        body.sprite_->setTexture(*body.texture_);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
    os << std::scientific << std::setprecision(4)
       << body.coordX_ << " " << body.coordY_ << " "
       << body.speedX_ << " " << body.speedY_ << " "
       << body.weight_ << " " << body.textureFile_;
    return os;
}
