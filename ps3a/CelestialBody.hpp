#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody: public sf::Drawable {
public:
    explicit CelestialBody(); 

    sf::Vector2f position() const { return pos; }
    sf::Vector2f velocity() const { return vel; }
    float mass() const { return m; }

protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
private:
    sf::Vector2f pos;  // Position variable
    sf::Vector2f vel;  // Velocity variable
    float m;  // Mass variable
    std::string imageFile;  // Store the image filename
    bool loadImage = true;

    friend std::istream& operator>>(std::istream& in, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& out, const CelestialBody& body);
};

std::istream& operator>>(std::istream& in, CelestialBody& body);
std::ostream& operator<<(std::ostream& out, const CelestialBody& body);
}  // namespace NB
