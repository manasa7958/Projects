// Copyright 2025 Manasa Praveen
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody : public sf::Drawable {
 public:
  CelestialBody();

  // Getter methods
  sf::Vector2f position() const { return pos; }
  sf::Vector2f velocity() const { return vel; }
  float mass() const { return m; }
  std::string getImageFile() const { return imageFile; }

  // Setter methods
  void setPosition(float x, float y) { pos = {x, y}; }
  void setVelocity(float vx, float vy) { vel = {vx, vy}; }
  bool loadTexture(double universeRadius);

 protected:
  void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
  sf::Vector2f pos;
  sf::Vector2f vel;
  float m;
  std::string imageFile;
  std::shared_ptr<sf::Texture> texture;
  std::shared_ptr<sf::Sprite> sprite;
  friend class Universe;
  friend std::istream& operator>>(std::istream& in, CelestialBody& body);
  friend std::ostream& operator<<(std::ostream& out, const CelestialBody& body);
};
}  // namespace NB
