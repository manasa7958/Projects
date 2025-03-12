// Copyright 2025 Manasa Praveen
#include "CelestialBody.hpp"
#include <iomanip>
#include <iostream>
#include <memory>
#include <cmath>

namespace NB {

const double G = 6.67430e-11;  // Gravitational constant

CelestialBody::CelestialBody() : pos(0, 0), vel(0, 0), m(0), imageFile("") {}

void CelestialBody::updateVelocity(const Vector2D& force, double dt) {
  Vector2D acceleration(force.x / m, force.y / m);
  vel.x += acceleration.x * dt;
  vel.y += acceleration.y * dt;
}

void CelestialBody::updatePosition(double dt) {
  pos.x += vel.x * dt;
  pos.y += vel.y * dt;
}

std::istream& operator>>(std::istream& in, CelestialBody& body) {
  in >> body.pos.x >> body.pos.y >> body.vel.x >> body.vel.y >> body.m >> body.imageFile;
  return in;
}

std::ostream& operator<<(std::ostream& out, const CelestialBody& body) {
  out << std::scientific << std::setprecision(4) << std::uppercase << body.pos.x
      << " " << body.pos.y << " " << body.vel.x << " " << body.vel.y << " "
      << body.m << " " << body.imageFile << std::endl;
  return out;
}

bool CelestialBody::loadTexture(double universeRadius) {
  texture = std::make_shared<sf::Texture>();
  if (!texture->loadFromFile(imageFile)) {
    std::cerr << "Failed to load texture " << imageFile << std::endl;
    return false;
  }
  sprite.setTexture(*texture);
  const double SCALE_FACTOR = 400.0 / universeRadius;
  float screenX = (pos.x * SCALE_FACTOR) + 400;  
  float screenY = (pos.y * SCALE_FACTOR) + 400;
  sprite.setPosition(screenX, screenY);
  return true;
}

void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
  window.draw(sprite, states);
}

}  // namespace NB
