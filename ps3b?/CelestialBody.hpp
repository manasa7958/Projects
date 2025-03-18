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

    void setPosition(const sf::Vector2f& pos);
    void setVelocity(const sf::Vector2f& vel);
    bool getSprite(sf::Sprite& outSprite) const;

 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override; // From sf::Drawable

 private:
    sf::Vector2f pos_;
    sf::Vector2f vel_;
    float m;
    std::string textureFile_;
    std::shared_ptr<sf::Texture> texture_;
    std::shared_ptr<sf::Sprite> sprite_;

    friend std::istream& operator>>(std::istream& is, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& os, const CelestialBody& body);
};
}  // namespace NB

