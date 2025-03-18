// Universe.hpp - Customized Version
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {
class Universe: public sf::Drawable {
 public:
    Universe(); // Required
    explicit Universe(const std::string& filename);  // Optional

    size_t size() const; // Optional
    double radius() const; // Optional

    const CelestialBody& operator[](size_t i) const; // Optional

    void step(double timeStep); // Implemented in part b, behavior for part a is undefined

 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override; // From sf::Drawable

 private:
    std::vector<CelestialBody> spaceObjects_;
    double universeBoundary_;
    std::shared_ptr<sf::Texture> bgTexture_;
    std::shared_ptr<sf::Sprite> bgSprite_;

    friend std::istream& operator>>(std::istream& is, Universe& uni);
    friend std::ostream& operator<<(std::ostream& os, const Universe& uni);
};
}  // namespace NB
