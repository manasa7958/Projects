#include <iomanip>
#include "CelestialBody.hpp"

namespace NB {

// Constructor with default values
CelestialBody::CelestialBody() : pos(0, 0), vel(0, 0), m(0), imageFile("") {}

// Overloaded input operator >>
std::istream& operator>>(std::istream& in, CelestialBody& body) {
    in >> body.pos.x >> body.pos.y
       >> body.vel.x >> body.vel.y
       >> body.m >> body.imageFile;
    return in;
}

std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
    out << std::scientific << std::setprecision(4) << std::uppercase
        << body.pos.x << " " << body.pos.y << " "
        << body.vel.x << " " << body.vel.y << " "
        << body.m << " " << body.imageFile << "\n";  // Ensure newline!

    return out;
}

// Getter methods
sf::Vector2f CelestialBody::position() const { return pos; }
sf::Vector2f CelestialBody::velocity() const { return vel; }
float CelestialBody::mass() const { return m; }

// Empty draw method (not needed for tests)
void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {}

}  // namespace NB
