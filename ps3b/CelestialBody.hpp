// Copyright 2025 Manasa Praveen
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody : public sf::Drawable {
 public:
  explicit CelestialBody();

  sf::Vector2f position() const { return pos; }
  sf::Vector2f velocity() const { return vel; }
  float mass() const { return m; }
  std::string getImageFile() const { return imageFile; }

  bool loadTexture(double universeRadius);
  void setVelocity(const sf::Vector2f& newVelocity) { vel = newVelocity; }
  void setPosition(const sf::Vector2f& newPosition) { pos = newPosition; }
 protected:
  void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
  sf::Vector2f pos;
  sf::Vector2f vel;
  float m;
  std::string imageFile;
  std::shared_ptr<sf::Texture> texture;
  sf::Sprite sprite;
  friend std::istream& operator>>(std::istream& in, CelestialBody& body);
  friend std::ostream& operator<<(std::ostream& out, const CelestialBody& body);
};

}  // namespace NB
