#include "Universe.hpp"

namespace NB {

Universe::Universe() : universeRadius(0) {}

std::istream& operator>>(std::istream& in, Universe& universe) {
    return in;  // Do nothing, just allow compilation
}

std::ostream& operator<<(std::ostream& out, const Universe& universe) {
    return out;  // Do nothing
}

size_t Universe::size() const { return 0; }
double Universe::radius() const { return 0; }
const CelestialBody& Universe::operator[](size_t index) const {
    throw std::out_of_range("Index out of range"); 
}
void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    for (const auto& body : bodies) {
        window.draw(*body, states);
    }

}  // namespace NB

}  // namespace NB

/*
namespace NB {

// Default constructor
Universe::Universe() : universeRadius(0) {}

// Overloaded input operator >>
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

// Overloaded output operator <<
std::ostream& operator<<(std::ostream& out, const Universe& universe) {
    out << universe.bodies.size() << " " << universe.universeRadius << std::endl;
    for (const auto& body : universe.bodies) {
        out << *body;
    }
    return out;
}

// Get number of celestial bodies
size_t Universe::size() const { return bodies.size(); }

// Get radius of the universe
double Universe::radius() const { return universeRadius; }

// Access a specific celestial body
const CelestialBody& Universe::operator[](size_t index) const {
    return *bodies.at(index);
}

}  // namespace NB*/
