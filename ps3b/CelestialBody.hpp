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
  CelestialBody(double x, double y, double vx, double vy, double mass, const std::string& imgFile);

  const Vector2D& position() const { return pos; }
  const Vector2D& velocity() const { return vel; }
  double mass() const { return m; }

  void setVelocity(const Vector2D& newVel) { vel = newVel; }
  void setPosition(const Vector2D& newPos) { pos = newPos; }

  void applyForce(const Vector2D& force, double dt);
  void updatePosition(double dt);

  bool loadTexture(double universeRadius);
  
  friend std::istream& operator>>(std::istream& in, CelestialBody& body);
  friend std::ostream& operator<<(std::ostream& out, const CelestialBody& body);

 protected:
  void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
  Vector2D pos;
  Vector2D vel;
  double m;
  std::string imageFile;
  std::shared_ptr<sf::Texture> texture;
  sf::Sprite sprite;
};

}  // namespace NB

#endif  // CELESTIALBODY_HPP
