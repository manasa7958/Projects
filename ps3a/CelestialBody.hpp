#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody: public sf::Drawable {
 public:
    explicit CelestialBody(); // Required

    sf::Vector2f position() const; // Optional
    sf::Vector2f velocity() const; // Optional
    float mass() const; // Optional

 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override; // From sf::Drawable
 private:
    // Fields and helper methods go here
};

std::istream& operator>>(std::istream& is, CelestialBody& uni);
std::ostream& operator<<(std::ostream& os, const CelestialBody& uni);
}  // namespace NB
