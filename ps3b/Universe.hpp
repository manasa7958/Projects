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
  Universe();
  void step(double dt);
  void setRadius(double r) { universeRadius = r; }
  void addBody(std::shared_ptr<CelestialBody> body) { bodies.push_back(body); }
  void clearBodies() { bodies.clear(); }
  size_t size() const { return bodies.size(); }
  double radius() const { return universeRadius; }

 protected:
  void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
  double universeRadius;
  std::vector<std::shared_ptr<CelestialBody>> bodies;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
};

std::istream& operator>>(std::istream& is, Universe& uni);
}  // namespace NB
