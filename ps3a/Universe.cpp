// Copyright 2025 Manasa Praveen
#include "Universe.hpp"

namespace NB {

Universe::Universe() : universeRadius(0) {}

std::istream& operator>>(std::istream& in, Universe& universe) {
  size_t n;
  double radius;
  in >> n >> radius;
  universe.universeRadius = radius;
  universe.bodies.clear();

  for (size_t i = 0; i < n; i++) {
    auto body = std::make_shared<CelestialBody>();
    in >> *body;
    universe.bodies.push_back(body);
  }
  return in;
}
std::ostream& operator<<(std::ostream& out, const Universe& universe) {
  out << universe.bodies.size() << " " << universe.universeRadius << "\n";
  for (const auto &body : universe.bodies) {
    out << *body;
  }
  return out;  // need to write
}
size_t Universe::size() const { 
  return bodies.size(); 
}
double Universe::radius() const { 
  return universeRadius; 
}
const CelestialBody& Universe::operator[](size_t index) const {
  throw std::out_of_range("Index out of range");
}
void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
  for (const auto& body : bodies) {
    window.draw(*body, states);
  }
}

}  // namespace NB
