// Copyright 2025 Manasa Praveen
#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {
class Universe : public sf::Drawable {
 public:
  Universe();                                       // Required
  explicit Universe(const std::string& filename);   // Optional
  size_t size() const;                              // Optional
  double radius() const;                            // Optional
  const CelestialBody& operator[](size_t i) const;  // Optional
  void step(double dt);
  void setRadius(double r) { universeRadius = r; }
  void addBody(std::shared_ptr<CelestialBody> body) { bodies.push_back(body); }
  void clearBodies() { bodies.clear(); }

 protected:
  void draw(sf::RenderTarget& window,
            sf::RenderStates states) const override;  // From sf::Drawable
 private:
  double universeRadius;  // Radius variable
  std::vector<std::shared_ptr<CelestialBody>> bodies;  // Smart pointer 
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;

};

std::istream& operator>>(std::istream& is, Universe& uni);
std::ostream& operator<<(std::ostream& os, const Universe& uni);
}  // namespace NB
