// Copyright 2025 Manasa Praveen and Ponita Ty
#include "triangle.hpp"
#include <cmath>


// Five colors!
const sf::Color COLORS[5] = {
    sf::Color::Magenta,  // depth % 5 == 0
    sf::Color::Blue,     // depth % 5 == 1
    sf::Color::Yellow,   // depth % 5 == 2
    sf::Color::Green,    // depth % 5 == 3
    sf::Color::Red       // depth % 5 == 3
};

Triangle::Triangle(float x, float y, float size, int depth)
    : m_x(x), m_y(y), m_size(size), m_depth(depth) {
  m_triangles.push_back(createTriangle(x, y, size, COLORS[depth % 5]));
  generateFractal(x, y, size, depth);
}

void Triangle::generateFractal(float x, float y, float size, int depth) {
  if (depth <= 0) {
    return;
  }
  float height = size * std::sqrt(3.0f) / 2.0f;
  float childSize = size / 2.0f;
  float childHeight = childSize * std::sqrt(3.0f) / 2.0f;
  float bottomX = x;
  float bottomY = y;
  float topLeftX = x - size / 2;
  float topLeftY = y - height;
  float topRightX = x + size / 2;
  float topRightY = y - height;

  m_triangles.push_back(
      createTriangle(topLeftX, topLeftY, childSize, COLORS[(depth - 1) % 5]));
  generateFractal(topLeftX, topLeftY, childSize, depth - 1);
  m_triangles.push_back(createTriangle(topRightX + childSize / 2,
                                       topRightY + childHeight, childSize,
                                       COLORS[(depth - 1) % 5]));
  generateFractal(topRightX + childSize / 2, topRightY + childHeight, childSize,
                  depth - 1);
  m_triangles.push_back(createTriangle(bottomX - childSize / 2,
                                       bottomY + childHeight, childSize,
                                       COLORS[(depth - 1) % 5]));
  generateFractal(bottomX - childSize / 2, bottomY + childHeight, childSize,
                  depth - 1);
}

sf::ConvexShape Triangle::createTriangle(float x, float y, float size,
                                         sf::Color color) const {
  sf::ConvexShape triangle;
  triangle.setPointCount(3);

  float height = size * std::sqrt(3.0f) / 2.0f;

  triangle.setPoint(0, sf::Vector2f(x, y));                      // Bottom
  triangle.setPoint(1, sf::Vector2f(x - size / 2, y - height));  // Top left
  triangle.setPoint(2, sf::Vector2f(x + size / 2, y - height));  // Top right

  triangle.setFillColor(color);
  triangle.setOutlineColor(sf::Color::Black);
  triangle.setOutlineThickness(2.0f);

  return triangle;
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& triangle : m_triangles) {
    target.draw(triangle, states);
  }
}
