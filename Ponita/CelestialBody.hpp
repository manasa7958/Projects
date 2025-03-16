// Copyright 2025 Ponita Ty
#pragma once
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody: public sf::Drawable {
 public:
    explicit CelestialBody();

    sf::Vector2f position() const;
    sf::Vector2f velocity() const;
    float mass() const;

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    double xPos_, yPos_;    // Position coordinates
    double xVel_, yVel_;    // Velocity components
    double mass_;           // Mass of the body

    // Smart pointers for SFML resources
    std::shared_ptr<sf::Texture> texture_;
    std::shared_ptr<sf::Sprite> sprite_;

    friend std::istream& operator>>(std::istream& is, CelestialBody& body);
    friend class Universe;  // Allow Universe to access sprite_ directly
};

std::istream& operator>>(std::istream& is, CelestialBody& body);
std::ostream& operator<<(std::ostream& os, const CelestialBody& body);
}  // namespace NB
