// Copyright 2025 Manasa Praveen
#include <iomanip>
#include <iostream>
#include <memory>
#include <cmath>
#include "CelestialBody.hpp"

namespace NB {

CelestialBody::CelestialBody() 
    : pos(0, 0), vel(0, 0), m(0), imageFile("body.gif"), texture(std::make_shared<sf::Texture>()) {}

bool CelestialBody::loadTexture(double universeRadius) {
    if (!texture->loadFromFile(imageFile)) {
        std::cerr << "Failed to load texture: " << imageFile << std::endl;
        return false;
    }
    sprite.setTexture(*texture);
    sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
    return true;
}

std::istream& operator>>(std::istream& in, CelestialBody& body) {
    in >> body.pos.x >> body.pos.y >> body.vel.x >> body.vel.y >> body.m >> body.imageFile;

    if (!body.loadTexture(1.0)) {  // Call texture loader
        std::cerr << "Failed to load texture for " << body.imageFile << std::endl;
    }

    return in;
}

void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(sprite, states);
}

}  // namespace NB
