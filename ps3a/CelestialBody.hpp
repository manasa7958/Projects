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
    sf::Vector2f pos;  // Position of the celestial body
    sf::Vector2f vel;  // Velocity of the celestial body
    float m;  // Mass of the celestial body
    std::string imageFile;  // Store the planet's image filename

    // Friend functions to allow direct access to private members
    friend std::istream& operator>>(std::istream& is, CelestialBody& uni);
    friend std::ostream& operator<<(std::ostream& os, const CelestialBody& uni);
};

std::istream& operator>>(std::istream& is, CelestialBody& uni);
std::ostream& operator<<(std::ostream& os, const CelestialBody& uni);
}  // namespace NB
