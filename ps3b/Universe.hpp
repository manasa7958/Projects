// Copyright 2025 Manasa Praveen
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {
class Universe: public sf::Drawable {
 public:
    Universe();
    explicit Universe(const std::string& filename);
    size_t size() const;
    double radius() const;
    const CelestialBody& operator[](size_t i) const;
    void step(double timeStep);

 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
    std::vector<CelestialBody> spaceObjects_;
    double universeBoundary_;
    std::shared_ptr<sf::Texture> bgTexture_;
    std::shared_ptr<sf::Sprite> bgSprite_;
    bool antiGravityMode_ = false;

    friend std::istream& operator>>(std::istream& is, Universe& uni);
    friend std::ostream& operator<<(std::ostream& os, const Universe& uni);
};
}  // namespace NB
