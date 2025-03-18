// CelestialBody.hpp - Customized Version
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
    double xCoord_, yCoord_;
    double xSpeed_, ySpeed_;
    double massValue_;
    std::string imageFile_;
    std::shared_ptr<sf::Texture> textureResource_;
    std::shared_ptr<sf::Sprite> spriteInstance_;

    friend std::istream& operator>>(std::istream& is, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& os, const CelestialBody& body);
};
}  // namespace NB
