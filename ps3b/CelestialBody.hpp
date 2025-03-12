// Copyright 2025 Manasa Praveen
// Copyright 2025 Manasa Praveen
#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP

#include <iostream>
#include <memory>
#include <string>
#include "Vector2D.hpp"
#include <SFML/Graphics.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
 public:
  CelestialBody();
  
  void updateVelocity(const Vector2D& force, double dt);
  void updatePosition(double dt);

  friend std::istream& operator>>(std::istream& in, CelestialBody& body);
  friend std::ostream& operator<<(std::ostream& out, const CelestialBody& body);

  bool loadTexture(double universeRadius);

 protected:
  void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
  Vector2D pos, vel;
  double m;
  std::string imageFile;
  std::shared_ptr<sf::Texture> texture;
  sf::Sprite sprite;
};

}  // namespace NB

#endif
