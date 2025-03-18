// Copyright 2025 Manasa Praveen
#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {
class Universe : public sf::Drawable {
 public:
    Universe(); // Required

    size_t size() const { return bodies.size(); }  // Keeps track of bodies
    double radius() const { return universeRadius; }  // Gets the universe radius
    const CelestialBody& operator[](size_t i) const;  // Access celestial bodies

    void step(double dt); // Simulates movement

 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
    std::vector<std::shared_ptr<CelestialBody>> bodies;  // ✅ Now uses shared_ptr
    double universeRadius;  

    std::shared_ptr<sf::Texture> backgroundTexture;
    std::shared_ptr<sf::Sprite> backgroundSprite;
    friend std::istream& operator>>(std::istream& is, Universe& uni);
    friend std::ostream& operator<<(std::ostream& os, const Universe& uni);
};
std::istream& operator>>(std::istream& is, Universe& uni);
std::ostream& operator<<(std::ostream& os, const Universe& uni);
}  // namespace NB
