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

class Universe {
 public:
  Universe();
  void step(double dt);

 private:
  std::vector<std::shared_ptr<CelestialBody>> bodies;
  double universeRadius;
};

}  // namespace NB

#endif
