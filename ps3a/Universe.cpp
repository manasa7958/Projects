#include "Universe.hpp"
#include <memory>
#include <vector>
#include <iostream>

namespace NB {

Universe::Universe() : universeRadius(0) {}

std::istream& operator>>(std::istream& in, Universe& universe) {
    int n;
    in >> n >> universe.universeRadius;
    
    universe.bodies.clear();
    for (int i = 0; i < n; ++i) {
        auto body = std::make_shared<CelestialBody>();
        in >> *body;
        universe.bodies.push_back(body);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Universe& universe) {
    out << universe.bodies.size() << " " << universe.universeRadius << std::endl;
    for (const auto& body : universe.bodies) {
        out << *body;
    }
    return out;
}

size_t Universe::size() const { return bodies.size(); }
double Universe::radius() const { return universeRadius; }

const CelestialBody& Universe::operator[](size_t index) const {
    return *bodies.at(index);
}

}  // namespace NB
