// Copyright 2025 Manasa Praveen
#include <iostream>
#include <memory>
#include <cmath>
#include "Universe.hpp"

namespace NB {

const double G = 6.67430e-11;  // Gravitational constant

Universe::Universe() : universeRadius(0) {}

void Universe::step(double dt) {
  size_t n = bodies.size();
  std::vector<Vector2D> forces(n, Vector2D(0, 0));

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (i != j) {
        Vector2D delta = bodies[j]->pos - bodies[i]->pos;
        double distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        double forceMagnitude = (G * bodies[i]->m * bodies[j]->m) / (distance * distance);
        Vector2D force(forceMagnitude * delta.x / distance, forceMagnitude * delta.y / distance);
        forces[i] = forces[i] + force;
      }
    }
  }

  for (size_t i = 0; i < n; ++i) {
    bodies[i]->updateVelocity(forces[i], dt);
  }

  for (size_t i = 0; i < n; ++i) {
    bodies[i]->updatePosition(dt);
  }
}

}  // namespace NB
