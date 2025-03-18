/*#include "CelestialBody.hpp"
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

void CelestialBody::setPosition(double x, double y) {
    coordX_ = x;
    coordY_ = y;
}

void CelestialBody::setVelocity(double vx, double vy) {
    speedX_ = vx;
    speedY_ = vy;
}

bool CelestialBody::getSprite(sf::Sprite& outSprite) const {
    if (sprite_ && texture_) {
        outSprite = *sprite_;
        return true;
    }
    return false;
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
        if (body.texture_->loadFromFile(filename)) {
            body.sprite_->setTexture(*body.texture_);
        }
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
}  // namespace NB*/

// CelestialBody.cpp - Updated to use sf::Vector2f for position and velocity
#include "CelestialBody.hpp"
#include <iomanip>

namespace NB {

CelestialBody::CelestialBody() : pos_(0.0f, 0.0f), vel_(0.0f, 0.0f), weight_(0.0f) {
    textureFile_ = "default.gif";
    texture_ = std::make_shared<sf::Texture>();
    sprite_ = std::make_shared<sf::Sprite>();
}

sf::Vector2f CelestialBody::position() const {
    return pos_;
}

sf::Vector2f CelestialBody::velocity() const {
    return vel_;
}

float CelestialBody::mass() const {
    return weight_;
}

void CelestialBody::setPosition(const sf::Vector2f& pos) {
    pos_ = pos;
}

void CelestialBody::setVelocity(const sf::Vector2f& vel) {
    vel_ = vel;
}

bool CelestialBody::getSprite(sf::Sprite& outSprite) const {
    if (sprite_ && texture_) {
        outSprite = *sprite_;
        return true;
    }
    return false;
}

void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    if (sprite_ && texture_) {
        window.draw(*sprite_, states);
    }
}

std::istream& operator>>(std::istream& is, CelestialBody& body) {
    float x, y, vx, vy, m;
    std::string filename;
    if (is >> x >> y >> vx >> vy >> m >> filename) {
        body.pos_ = sf::Vector2f(x, y);
        body.vel_ = sf::Vector2f(vx, vy);
        body.weight_ = m;
        body.textureFile_ = filename;
        if (body.texture_->loadFromFile(filename)) {
            body.sprite_->setTexture(*body.texture_);
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
    os << std::scientific << std::setprecision(4)
       << body.pos_.x << " " << body.pos_.y << " "
       << body.vel_.x << " " << body.vel_.y << " "
       << body.weight_ << " " << body.textureFile_;
    return os;
}
}  // namespace NB


