#include "CelestialBody.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace NB {

CelestialBody::CelestialBody() : position(0, 0), velocity(0, 0), mass(0) {}

std::istream& operator>>(std::istream& in, CelestialBody& body) {
    in >> body.position.x >> body.position.y
       >> body.velocity.x >> body.velocity.y
       >> body.mass >> body.imageFile;
    return in;
}

std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
    out << body.position.x << " " << body.position.y << " "
        << body.velocity.x << " " << body.velocity.y << " "
        << body.mass << " " << body.imageFile << std::endl;
    return out;
}

sf::Vector2f CelestialBody::getPosition() const { return position; }
sf::Vector2f CelestialBody::getVelocity() const { return velocity; }
double CelestialBody::getMass() const { return mass; }

// Required for drawing
void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Empty for now (unit tests don’t need rendering)
}

}  // namespace NB

