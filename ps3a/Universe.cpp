// Copyright 2025 Manasa Praveen
#include "Universe.hpp"

namespace NB {

Universe::Universe() : universeRadius(0) {}
Universe::Universe() : universeRadius(0) {
    if (!backgroundTexture.loadFromFile("background.jpg")) {
        std::cerr << "Failed to load background image" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
    }
}

std::istream& operator>>(std::istream& in, Universe& universe) {
    size_t n;
    double radius;
    in >> n >> radius;
    universe.setRadius(radius);
    universe.clearBodies();

    if (n == 0) return in;
    for (size_t i = 0; i < n; ++i) {
        auto body = std::make_shared<CelestialBody>();
        in >> *body;
        
        if (!body->loadTexture(radius)) {
          std::cerr << "Failed to load texture" << std::endl;
        }
        universe.addBody(body);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Universe& universe) {
  out << universe.size() << " " << universe.radius() << "\n";
  for (size_t i = 0; i < universe.size(); ++i) {
    out << universe[i];
  }
  return out;
}

size_t Universe::size() const {
  return bodies.size();
}

double Universe::radius() const {
  return universeRadius;
}

const CelestialBody& Universe::operator[](size_t index) const {
  if (index >= bodies.size()) {
    throw std::out_of_range("Index out of range");
  }
  return *bodies[index];
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(backgroundSprite);
    if (bodies.empty()) {
    std::cerr << "No celestial bodies found!";
    }
    for (const auto& body : bodies) {
        window.draw(*body, states);
    }
}
}  // namespace NB
