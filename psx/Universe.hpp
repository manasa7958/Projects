// Copyright 2025 Ponita Ty
#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {
class Universe: public sf::Drawable {
 public:
    Universe();  // Required

    size_t size() const;  // Optional
    double radius() const;  // Optional
    const CelestialBody& operator[](size_t i) const;  // Optional

    // Extra credit: Initialize background
    bool initBackground(const std::string& filename);

    void step(double seconds);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    std::vector<CelestialBody> bodies_;  // Collection of celestial bodies
    double radius_;  // Radius of the universe

    // Background resources
    std::shared_ptr<sf::Texture> backgroundTexture_;
    std::shared_ptr<sf::Sprite> backgroundSprite_;

    friend std::istream& operator>>(std::istream& is, Universe& uni);
};

std::istream& operator>>(std::istream& is, Universe& uni);
std::ostream& operator<<(std::ostream& os, const Universe& uni);
}  // namespace NB
