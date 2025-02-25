/*// Copyright 2025 Manasa Praveen
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

}  // namespace NB*/

// Copyright 2025 Manasa Praveen
#include <iomanip>
#include "CelestialBody.hpp"

namespace NB {

CelestialBody::CelestialBody() : pos(0, 0), vel(0, 0), m(0), imageFile("") {}

std::istream& operator>>(std::istream& in, CelestialBody& body) {
    in >> body.pos.x >> body.pos.y >> body.vel.x >> body.vel.y >> body.m >> body.imageFile;
    return in;
}

std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
    out << std::scientific << std::setprecision(4) << std::uppercase
        << body.pos.x << " " << body.pos.y << " "
        << body.vel.x << " " << body.vel.y << " "
        << body.m << " " << body.imageFile << std::endl;
    return out;
}

bool CelestialBody::loadTexture(double universeRadius) {
    texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(imageFile)) {
        std::cerr << "❌ Error: Could not load texture for " << imageFile << std::endl;
        return false;
    }

    sprite.setTexture(*texture);

    // ✅ Adjust scaling factor based on universe radius
    const double SCALE_FACTOR = 200.0 / universeRadius;  // Reduce if needed

    // Convert simulation coordinates to screen coordinates
    float screenX = (pos.x * SCALE_FACTOR) + 400;  // Centered in window
    float screenY = (pos.y * SCALE_FACTOR) + 400;

    sprite.setPosition(screenX, screenY);

    // ✅ Debug info
    std::cout << "🎯 Planet " << imageFile << " at (" << pos.x << ", " << pos.y << ")"
              << " → Screen (" << screenX << ", " << screenY << ")" << std::endl;

    return true;
}
void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    std::cout << "🖌️ Drawing sprite at " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
    window.draw(sprite, states);
}

}  // namespace NB


