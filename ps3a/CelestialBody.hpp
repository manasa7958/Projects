#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
public:
    explicit CelestialBody(); // Required

    sf::Vector2f getPosition() const; // ✅ Getter for position
    sf::Vector2f getVelocity() const; // ✅ Getter for velocity
    float getMass() const; // ✅ Getter for mass

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override; // SFML Drawing

private:
    sf::Vector2f position;  // ✅ Position of the celestial body
    sf::Vector2f velocity;  // ✅ Velocity of the celestial body
    float mass;  // ✅ Mass of the celestial body
    std::string imageFile;  // ✅ Store the planet's image filename

    // ✅ Friend functions to allow direct access to private members
    friend std::istream& operator>>(std::istream& is, CelestialBody& uni);
    friend std::ostream& operator<<(std::ostream& os, const CelestialBody& uni);
};

}  // namespace NB
