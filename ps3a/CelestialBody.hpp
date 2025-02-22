#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
public:
    explicit CelestialBody(); // Required

    sf::Vector2f getPosition() const; // ✅ FIX: Changed from position() to getPosition()
    sf::Vector2f getVelocity() const; // ✅ FIX: Changed from velocity() to getVelocity()
    float getMass() const; // ✅ FIX: Changed from mass() to getMass()

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override; // SFML Drawing

private:
    sf::Vector2f position;  // ✅ Member variable
    sf::Vector2f velocity;  // ✅ Member variable
    float mass;  // ✅ Member variable
    std::string imageFile;  // ✅ Store the planet's image filename
};

std::istream& operator>>(std::istream& is, CelestialBody& uni);
std::ostream& operator<<(std::ostream& os, const CelestialBody& uni);

}  // namespace NB
