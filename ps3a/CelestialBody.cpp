#include "CelestialBody.hpp"

namespace NB {

// Constructor with default values
CelestialBody::CelestialBody() : position(0, 0), velocity(0, 0), mass(0), imageFile("") {}

// Overloaded input operator >>
std::istream& operator>>(std::istream& in, CelestialBody& body) {
    in >> body.position.x >> body.position.y
       >> body.velocity.x >> body.velocity.y
       >> body.mass >> body.imageFile;
    return in;
}

// Overloaded output operator <<
std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
    out << body.position.x << " " << body.position.y << " "
        << body.velocity.x << " " << body.velocity.y << " "
        << body.mass << " " << body.imageFile << std::endl;
    return out;
}

// Getter methods (renamed to match header file)
sf::Vector2f CelestialBody::getPosition() const { return position; }
sf::Vector2f CelestialBody::getVelocity() const { return velocity; }
float CelestialBody::getMass() const { return mass; }

// Empty draw method (not needed for tests)
void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {}

}  // namespace NB
