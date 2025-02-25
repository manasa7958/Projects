// Copyright 2025 Manasa Praveen
#include <iomanip>
#include "CelestialBody.hpp"

namespace NB {

CelestialBody::CelestialBody() : pos(0, 0), vel(0, 0), m(0), imageFile("") {}

std::istream& operator>>(std::istream& in, CelestialBody& body) {
in >> body.pos.x >> body.pos.y >> body.vel.x >> body.vel.y >> body.m >>
    body.imageFile;
return in;
}
std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
out << std::scientific << std::setprecision(4) << std::uppercase << body.pos.x
    << " " << body.pos.y << " " << body.vel.x << " " << body.vel.y << " "
    << body.m << " " << body.imageFile << std::endl;
return out;
}

bool CelestialBody::loadTexture() {
  texture = std::make_shared<sf::Texture>();
  if (!texture->loadFromFile(imageFile)) {
    std::cerr << "Failed to load image: " << imageFile << std::endl;
    return false;
  }
  sprite.setTexture(*texture);
  sprite.setPosition(pos.x, pos.y);
  std::cout << "✅ Successfully loaded texture: " << imageFile << std::endl;
  return true;
}

void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(sprite, states);
}

}  // namespace NB
