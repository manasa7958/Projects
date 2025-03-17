// Copyright 2025 Manasa Praveen
#include <iomanip>
#include <iostream>
#include <memory>
#include <cmath>
#include "CelestialBody.hpp"

namespace NB {

CelestialBody::CelestialBody() 
    : pos(0, 0), vel(0, 0), m(0), imageFile("body.gif"), texture(std::make_shared<sf::Texture>()) {}

std::istream& operator>>(std::istream& in, CelestialBody& body) {
    in >> body.pos.x >> body.pos.y >> body.vel.x >> body.vel.y >> body.m >> body.imageFile;

    if (!body.texture->loadFromFile(body.imageFile)) {
        std::cerr << "Failed to load texture: " << body.imageFile << std::endl;
    } else {
        body.sprite.setTexture(*body.texture);
        body.sprite.setOrigin(body.texture->getSize().x / 2, body.texture->getSize().y / 2);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
    out << std::scientific << std::setprecision(4) << std::uppercase
        << body.pos.x << " " << body.pos.y << " "
        << body.vel.x << " " << body.vel.y << " "
        << body.m << " " << body.imageFile << std::endl;
    return out;
}

void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(sprite, states);
}

}  // namespace NB
