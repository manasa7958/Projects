// Copyright 2025 Manasa Praveen
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {

class Universe : public sf::Drawable {
 public:
  Universe();

  size_t size() const;
  double radius() const;
  void setRadius(double r) { universeRadius = r; }
  void clearBodies() { bodies.clear(); }
  void addBody(std::shared_ptr<CelestialBody> body) { bodies.push_back(body); }
  void step(double dt);

  const CelestialBody& operator[](size_t index) const;

 protected:
  void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
  std::vector<std::shared_ptr<CelestialBody>> bodies;
  double universeRadius;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;

  friend std::istream& operator>>(std::istream& in, Universe& universe);
  friend std::ostream& operator<<(std::ostream& out, const Universe& universe);
};

}  // namespace NB
