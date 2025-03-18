// Universe.hpp - Fixed version
// Copyright 2025 Manasa Praveen
#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {
class Universe : public sf::Drawable {
 public:
    Universe();

    size_t size() const;
    double radius() const;
    const CelestialBody& operator[](size_t i) const;

    bool initBackground(const std::string& filename);

    void step(double seconds);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    std::vector<std::shared_ptr<CelestialBody>> bodies; 
    double universeRadius; 

    std::shared_ptr<sf::Texture> backgroundTexture;
    std::shared_ptr<sf::Sprite> backgroundSprite;

    friend std::istream& operator>>(std::istream& is, Universe& uni);
    friend std::ostream& operator<<(std::ostream& os, const Universe& uni);
};

std::istream& operator>>(std::istream& is, Universe& uni);
std::ostream& operator<<(std::ostream& os, const Universe& uni);
}  // namespace NB
