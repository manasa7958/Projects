// Copyright 2025 Manasa Praveen
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"
#include "Vector2D.hpp"

namespace NB {

class Universe : public sf::Drawable {
 public:
  Universe();
  void step(double dt);
  void addBody(std::shared_ptr<CelestialBody> body);
  void clearBodies();
  size_t size() const;
  double radius() const;
  void setRadius(double r);
  const CelestialBody& operator[](size_t index) const;

  friend std::istream& operator>>(std::istream& in, Universe& universe);
  friend std::ostream& operator<<(std::ostream& out, const Universe& universe);

 protected:
  void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
  std::vector<std::shared_ptr<CelestialBody>> bodies;
  double universeRadius;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
};

}  // namespace NB

#endif
