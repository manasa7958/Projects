// Copyright 2025 Manasa Praveen
#include <iomanip>
#include <iostream>
#include <memory>
#include <cmath>
#include "CelestialBody.hpp"

namespace NB {

// Default Constructor
CelestialBody::CelestialBody() : pos(0, 0), vel(0, 0), m(0), imageFile("") {}

// Parameterized Constructor
CelestialBody::CelestialBody(double x, double y, double vx, double vy, double mass, const std::string& imgFile)
    : pos(x, y), vel(vx, vy), m(mass), imageFile(imgFile) {}

// Apply force to update velocity
void CelestialBody::applyForce(const Vector2D& force, double dt) {
  if (m > 0) {
    Vector2D acceleration = force / m;
    vel = vel + acceleration * dt;
  }
}

// Update position based on velocity
void CelestialBody::updatePosition(double dt) {
  pos = pos + vel * dt;
}

// Overloaded Input Operator
std::istream& operator>>(std::istream& in, CelestialBody& body) {
  in >> body.pos.x >> body.pos.y >> body.vel.x >> body.vel.y >> body.m >> body.imageFile;
  return in;
}

// Overloaded Output Operator
std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
  out << std::scientific << std::setprecision(4) << std::uppercase
      << body.pos.x << " " << body.pos.y << " " 
      << body.vel.x << " " << body.vel.y << " " 
      << body.m << " " << body.imageFile << std::endl;
  return out;
}

// Load texture for graphical representation
bool CelestialBody::loadTexture(double universeRadius) {
  texture = std::make_shared<sf::Texture>();
  if (!texture->loadFromFile(imageFile)) {
    std::cerr << "Failed to load texture " << imageFile << std::endl;
    return false;
  }
  sprite.setTexture(*texture);
  const double SCALE_FACTOR = 400.0 / universeRadius;
  float screenX = (pos.x * SCALE_FACTOR) + 400;  // Center in window
  float screenY = (pos.y * SCALE_FACTOR) + 400;
  sprite.setPosition(screenX, screenY);
  return true;
}

// Draw celestial body
void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
  window.draw(sprite, states);
}

}  // namespace NB
