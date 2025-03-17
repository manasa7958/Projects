// Copyright 2025 Manasa Praveen
#include <iomanip>
#include <iostream>
#include <memory>
#include <cmath>
#include "CelestialBody.hpp"

namespace NB {

CelestialBody::CelestialBody() 
    : pos(0, 0), vel(0, 0), m(0), imageFile("body.gif"), 
      texture(std::make_shared<sf::Texture>()), sprite(std::make_shared<sf::Sprite>()) {}

bool CelestialBody::loadTexture(double universeRadius) {
    if (!texture->loadFromFile(imageFile)) {
        std::cerr << "Failed to load texture: " << imageFile << std::endl;
        return false;
    }
    sprite->setTexture(*texture);
    sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
    return true;
}

std::istream& operator>>(std::istream& in, CelestialBody& body) {
    in >> body.pos.x >> body.pos.y >> body.vel.x >> body.vel.y >> body.m >> body.imageFile;

    if (!body.loadTexture(1.0)) {  // Call texture loader
        std::cerr << "Failed to load texture for " << body.imageFile << std::endl;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
    out << std::scientific << std::setprecision(4) << std::uppercase
        << body.pos.x << " " << body.pos.y << " "
        << body.vel.x << " " << body.vel.y << " "
        << body.m << " " << body.imageFile;
    return out;
}

void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    if (sprite) {
        window.draw(*sprite, states);
    } else {
        std::cerr << "Warning: Sprite is null, cannot draw." << std::endl;
    }
}

}  // namespace NB
