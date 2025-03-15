#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "CelestialBody.hpp"

namespace NB {
class Universe: public sf::Drawable {
 public:
    Universe(); // Required
    explicit Universe(const std::string& filename);  // Optional

    size_t size() const; // Optional
    double radius() const; // Optional

    const CelestialBody& operator[](size_t i) const; // Optional

    void step(double dt); // Implemented in part b, behavior for part a is undefined
 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override; // From sf::Drawable
 private:
    // Fields and helper functions go here
};

std::istream& operator>>(std::istream& is, Universe& uni);
std::ostream& operator<<(std::ostream& os, const Universe& uni);
}  // namespace NB
