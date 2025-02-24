#include <iomanip>
#include "CelestialBody.hpp"

namespace NB {
CelestialBody::CelestialBody() : pos(0, 0), vel(0, 0), m(0), imageFile("") {
    if (loadImage) {
        if (!texture.loadFromFile(imageFile)) {
            std::cerr << "Failed to load image " << imageFile;
        }
    }
}


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
        << body.m << " " << body.imageFile << std::endl;

    return out;
}

void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {}

}  // namespace NB
