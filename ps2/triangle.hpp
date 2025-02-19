// Copyright 2025 Manasa Praveen and Ponita Ty
#ifndef PS2_TRIANGLE_HPP_
#define PS2_TRIANGLE_HPP_

#include <cstdlib> 

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

class Triangle : public sf::Drawable {
 public:
  Triangle(float x, float y, float size, int depth);
  void setPosition(float x, float y);
  void setDepth(int depth);

 private:
  sf::ConvexShape createTriangle(float x, float y, float size,
                                 sf::Color color) const;
  void generateFractal(float x, float y, float size, int depth);
  void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
  std::vector<sf::ConvexShape> m_triangles;
  float m_x, m_y;
  float m_size;
  int m_depth;
};
#endif  // PS2_TRIANGLE_HPP_
