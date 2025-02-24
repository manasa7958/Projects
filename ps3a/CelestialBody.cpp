#include <iomanip>
#include "CelestialBody.hpp"

namespace NB {

CelestialBody::CelestialBody() : pos(0, 0), vel(0, 0), m(0), imageFile("") {}

// Overloaded input operator >>
std::istream& operator>>(std::istream& in, CelestialBody& body) {
    in >> body.position().x >> body.position().y
       >> body.velocity().x >> body.velocity().y
       >> body.mass() >> body.imageFile;
    return in;
}
std::istream& operator>>(std::istream& in, CelestialBody& body) {
    in >> body.pos.x >> body.pos.y
       >> body.vel.x >> body.vel.y
       >> body.m >> body.imageFile;  // ✅ Works because `operator>>` is a friend
    return in;
}
std::istream& operator>>(std::istream& in, CelestialBody& body) {
    float x, y, vx, vy, mass;
    std::string image;
    
    // Read values from input stream
    in >> x >> y >> vx >> vy >> mass >> image;

    // Use setter functions to update private members
    body.setPosition(x, y);
    body.setVelocity(vx, vy);
    body.setMass(mass);
    body.setImageFile(image);

    return in;
}

// Overloaded output operator <<
std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
    out << std::scientific << std::setprecision(4) << std::uppercase
        << body.position().x << " " << body.position().y << " "
        << body.velocity().x << " " << body.velocity().y << " "
        << body.mass() << " " << body.imageFile << std::endl;

    return out;
}

// Getter methods
sf::Vector2f CelestialBody::position() const { return pos; }
sf::Vector2f CelestialBody::velocity() const { return vel; }
float CelestialBody::mass() const { return m; }

void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {}

}  // namespace NB
