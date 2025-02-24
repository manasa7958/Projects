// Copyright 2025 Manasa Praveen
#include "Universe.hpp"

namespace NB {

Universe::Universe() : universeRadius(0) {}

std::istream& operator>>(std::istream& in, Universe& universe) {
  return in;  // need to write
}

std::ostream& operator<<(std::ostream& out, const Universe& universe) {
  return out;  // need to write
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
}

}  // namespace NB
